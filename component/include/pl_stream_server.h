#pragma once
#include "pl_common_types.h"
#include "pl_stream.h"
#include "pl_server.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Stream server class
class StreamServer : public Server {
public:
  /// @brief Default server task parameters
  static const TaskParameters defaultTaskParameters;

  /// @brief Creates a stream server
  /// @param stream stream
  StreamServer(std::shared_ptr<Stream> stream);
  ~StreamServer();
  StreamServer(const StreamServer&) = delete;
  StreamServer& operator=(const StreamServer&) = delete;

  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

  esp_err_t Enable() override;
  esp_err_t Disable() override;

  bool IsEnabled() override;

  /// @brief Gets the stream
  /// @return stream
  std::shared_ptr<Stream> GetStream();
  
  /// @brief Sets the stream
  /// @param stream stream
  /// @return error code
  esp_err_t SetStream(std::shared_ptr<Stream> stream);

  /// @brief Sets the server task parameters
  /// @param taskParameters task parameters
  /// @return error code
  esp_err_t SetTaskParameters(const TaskParameters& taskParameters);

protected:
  /// @brief Handles the stream client request
  /// @param stream stream
  /// @return error code
  virtual esp_err_t HandleRequest(Stream& stream) = 0;

private:
  Mutex mutex;
  std::shared_ptr<Stream> stream;
  TaskParameters taskParameters = defaultTaskParameters;
  TaskHandle_t taskHandle = NULL;
  bool disable = false;
  bool disableFromRequest = false;
  bool enableFromRequest = false;

  static void TaskCode(void* parameters);
  esp_err_t RestartIfEnabled(); 
};

//==============================================================================

}