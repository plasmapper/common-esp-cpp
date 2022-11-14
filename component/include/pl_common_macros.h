#pragma once
#include "esp_log.h"

//==============================================================================

// If the argument not ESP_OK, print the error message and return the argument.
#define PL_RETURN_ON_ERROR(f) do {esp_err_t e = (f); if (unlikely (e != ESP_OK)) {ESP_LOGE ("PL_RETURN_ON_ERROR", "0x%x (%s), file: '%s', line: %d, function: %s", e, esp_err_to_name (e), __FILE__, __LINE__, __ASSERT_FUNC); return e;}} while(0)