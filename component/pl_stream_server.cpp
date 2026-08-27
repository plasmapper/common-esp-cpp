#include "pl_stream_server.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_stream_server";

//==============================================================================

namespace PL {

//==============================================================================

const TaskParameters StreamServer::defaultTaskParameters = {4096, tskIDLE_PRIORITY + 5, 0};

//==============================================================================

StreamServer::StreamServer(std::shared_ptr<Stream> stream) : stream(stream) {}

//==============================================================================

StreamServer::~StreamServer() {
  if (taskHandle) {
    ESP_LOGE(TAG, "StopTask was not called by the derived class destructor");
    abort();
  }
}

//==============================================================================

esp_err_t StreamServer::Lock(TickType_t timeout) {
  esp_err_t error = mutex.Lock(timeout);
  if (error != ESP_OK && (error != ESP_ERR_TIMEOUT || timeout != 0))
    ESP_LOGE(TAG, "mutex lock failed");
  return error;
}

//==============================================================================

esp_err_t StreamServer::Unlock() {
  ESP_RETURN_ON_ERROR(mutex.Unlock(), TAG, "mutex unlock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServer::Enable() {
  LockGuard lg(*this);
  if (taskHandle == xTaskGetCurrentTaskHandle()) {
    enableFromRequest = true;
    return ESP_OK;
  }
  if (taskHandle)
    return ESP_OK;
  
  disable = false;
  TaskHandle_t handle = NULL;
  if (xTaskCreatePinnedToCore(TaskCode, GetName().c_str(), taskParameters.stackDepth, this, taskParameters.priority, &handle, taskParameters.coreId) != pdPASS) {
    taskHandle = NULL;
    ESP_RETURN_ON_ERROR(ESP_FAIL, TAG, "task create failed");
  }
  taskHandle = handle;
  enabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServer::Disable() {
  LockGuard lg(*this);
  if (taskHandle == xTaskGetCurrentTaskHandle()) {
    enableFromRequest = false;
    disableFromRequest = true;
    return ESP_OK;
  }
  if (!taskHandle)
    return ESP_OK;

  ESP_RETURN_ON_ERROR(StopTask(), TAG, "stop task failed");
  return ESP_OK;
}

//==============================================================================

bool StreamServer::IsEnabled() {
  LockGuard lg(*this);
  return taskHandle;
}

//==============================================================================

std::shared_ptr<Stream> StreamServer::GetStream() {
  LockGuard lg(*this);
  return stream;
}

//==============================================================================

esp_err_t StreamServer::SetStream(std::shared_ptr<Stream> stream) {
  LockGuard lg(*this);
  if (this->stream == stream)
    return ESP_OK;
  this->stream = stream;
  ESP_RETURN_ON_ERROR(RestartIfEnabled(), TAG, "restart failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServer::SetTaskParameters(const TaskParameters& taskParameters) {
  LockGuard lg(*this);
  if (this->taskParameters == taskParameters)
    return ESP_OK;
  this->taskParameters = taskParameters;
  ESP_RETURN_ON_ERROR(RestartIfEnabled(), TAG, "restart failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServer::StopTask() {
  if (taskHandle == xTaskGetCurrentTaskHandle()) {
    ESP_LOGE(TAG, "stop task called from the server task itself");
    abort();
  }
  LockGuard lg(*this);
  if (!taskHandle)
    return ESP_OK;
  while (taskHandle) {
    disable = true;
    vTaskDelay(1);
  }
  disabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

void StreamServer::TaskCode(void* parameters) {
  StreamServer& server = *(StreamServer*)parameters;
  bool firstRun = true;

  while (!server.disable) {
    if (server.Lock(0) == ESP_OK) {
      std::shared_ptr<Stream> streamPtr = server.GetStream();
      Stream& stream = *streamPtr;

      if (firstRun) {
        LockGuard lg(stream);
        firstRun = false;
        stream.Read(NULL, stream.GetReadableSize());
      }
      else {
        LockGuard lg(stream);
        if (stream.GetReadableSize())
          server.HandleRequest(stream);
      }

      if (server.enableFromRequest)
        server.disableFromRequest = false;
      server.enableFromRequest = false;

      if (server.disableFromRequest) {
        server.disableFromRequest = false;
        server.disabledEvent.Generate();
        server.taskHandle = NULL;
        server.Unlock();
        vTaskDelete(NULL);
        return;
      }

      server.Unlock();
    }
    vTaskDelay(1);
  }

  server.taskHandle = NULL;
  vTaskDelete(NULL);
}

//==============================================================================

esp_err_t StreamServer::RestartIfEnabled() {
  if (!taskHandle || disableFromRequest)
    return ESP_OK;
  ESP_RETURN_ON_ERROR(Disable(), TAG, "disable failed");
  ESP_RETURN_ON_ERROR(Enable(), TAG, "enable failed");
  return ESP_OK;
}

//==============================================================================

}