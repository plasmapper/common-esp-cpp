cmake_minimum_required(VERSION 3.22)

idf_component_register(SRCS "pl_mutex.cpp" "pl_lock_guard.cpp" "pl_buffer.cpp" "pl_stream.cpp" "pl_hardware_interface.cpp" "pl_server.cpp" "pl_stream_server.cpp" "pl_common_types.cpp"
                       INCLUDE_DIRS "include")