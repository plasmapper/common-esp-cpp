#pragma once
#include "pl_lockable.h"
#include "pl_buffer.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Stream class
class Stream : public virtual Lockable {
public:
  /// @brief Create a stream
  Stream() {}
  
  /// @brief Read the data from the stream
  /// @param dest destination (can be NULL)
  /// @param size number of bytes to read
  /// @return error code
  virtual esp_err_t Read (void* dest, size_t size) = 0;

  /// @brief Read the data from the stream to the buffer
  /// @param dest destination buffer
  /// @param offset destination buffer offset
  /// @param size number of bytes to read
  /// @return error code
  esp_err_t Read (Buffer& dest, size_t offset, size_t size);
  
  /// @brief Read the data from the stream up to the specified termination character 
  /// @param dest destination (can be NULL)
  /// @param maxSize maximum number of bytes to read
  /// @param termChar termination character
  /// @param size number of bytes read
  /// @return error code
  esp_err_t ReadUntil (void* dest, size_t maxSize, char termChar, size_t& size);

  /// @brief Read the data from the stream to the buffer up to the specified termination character 
  /// @param dest destination buffer
  /// @param offset destination buffer offset
  /// @param termChar termination character
  /// @param size number of bytes read
  /// @return error code
  esp_err_t ReadUntil (Buffer& dest, size_t offset, char termChar, size_t& size);
  
  /// @brief Read the data from the stream up to the specified termination character
  /// @param termChar termination character
  /// @return error code
  esp_err_t ReadUntil (char termChar);

  /// @brief Write the data to the stream
  /// @param src source
  /// @param size number of bytes to write
  /// @return error code
  virtual esp_err_t Write (const void* src, size_t size) = 0;
  
  /// @brief Write the data from the buffer to the stream
  /// @param src source buffer
  /// @param offset source buffer offset
  /// @param size number of bytes to write
  /// @return error code
  esp_err_t Write (Buffer& src, size_t offset, size_t size);     

  /// @brief Get the number of bytes that are available for reading from the stream
  /// @return number of bytes
  virtual size_t GetReadableSize() = 0;
  
  /// @brief Get the read operation timeout 
  /// @return timeout in FreeRTOS ticks
  virtual TickType_t GetReadTimeout() = 0;

  /// @brief Set the read operation timeout 
  /// @param timeout timeout in FreeRTOS ticks
  /// @return error code
  virtual esp_err_t SetReadTimeout(TickType_t timeout) = 0;
};

//==============================================================================

}