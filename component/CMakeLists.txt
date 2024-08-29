cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "pl_mutex.cpp" "pl_lock_guard.cpp" "pl_buffer.cpp" "pl_stream.cpp" "pl_hardware_interface.cpp" "pl_server.cpp" "pl_stream_server.cpp"
                       INCLUDE_DIRS "include")