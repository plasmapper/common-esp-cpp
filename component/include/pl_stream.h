#pragma once
#include "pl_lockable.h"
#include "pl_buffer.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Stream class
class Stream : public virtual Lockable {
public:
  /// @brief Creates a stream
  Stream() {}
  
  /// @brief Reads the data from the stream
  /// @param dest destination (can be NULL)
  /// @param size number of bytes to read
  /// @return error code
  virtual esp_err_t Read(void* dest, size_t size) = 0;

  /// @brief Reads the data from the stream to the buffer
  /// @param dest destination buffer
  /// @param offset destination buffer offset
  /// @param size number of bytes to read
  /// @return error code
  esp_err_t Read(Buffer& dest, size_t offset, size_t size);
  
  /// @brief Reads the data from the stream up to the specified termination character 
  /// @param dest destination (can be NULL)
  /// @param maxSize maximum number of bytes to read
  /// @param termChar termination character
  /// @param size number of bytes read
  /// @return error code
  esp_err_t ReadUntil(void* dest, size_t maxSize, char termChar, size_t* size);

  /// @brief Reads the data from the stream to the buffer up to the specified termination character 
  /// @param dest destination buffer
  /// @param offset destination buffer offset
  /// @param termChar termination character
  /// @param size number of bytes read
  /// @return error code
  esp_err_t ReadUntil(Buffer& dest, size_t offset, char termChar, size_t* size);
  
  /// @brief Reads the data from the stream up to the specified termination character
  /// @param termChar termination character
  /// @return error code
  esp_err_t ReadUntil(char termChar);

  /// @brief Writes the data to the stream
  /// @param src source
  /// @param size number of bytes to write
  /// @return error code
  virtual esp_err_t Write(const void* src, size_t size) = 0;
  
  /// @brief Writes the data from the buffer to the stream
  /// @param src source buffer
  /// @param offset source buffer offset
  /// @param size number of bytes to write
  /// @return error code
  esp_err_t Write(Buffer& src, size_t offset, size_t size);

  /// @brief Writes the string to the stream
  /// @param src source string
  /// @return error code
  esp_err_t Write(const std::string& src);

  /// @brief Discards the data in the read buffer until no data is received for the specified period of time
  /// @param time time 
  /// @return error code
  esp_err_t FlushReadBuffer(TickType_t time = 0);

  /// @brief Gets the number of bytes that are available for reading from the stream
  /// @return number of bytes
  virtual size_t GetReadableSize() = 0;
  
  /// @brief Gets the read operation timeout 
  /// @return timeout in FreeRTOS ticks
  virtual TickType_t GetReadTimeout() = 0;

  /// @brief Sets the read operation timeout 
  /// @param timeout timeout in FreeRTOS ticks
  /// @return error code
  virtual esp_err_t SetReadTimeout(TickType_t timeout) = 0;
};

//==============================================================================

}