#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements. See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to you under the Apache License, Version
# 2.0 (the "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required (VERSION 2.8)
project (cmake_test)

IF (EXISTS "${CMAKE_SOURCE_DIR}/CMakeLists_local.txt")
  INCLUDE ("${CMAKE_SOURCE_DIR}/CMakeLists_local.txt" OPTIONAL)
ENDIF()

#====================================================================================#

# Config

SET(TARGET_OS Linux)
SET(TARGET_ARCH ARMV7L)
#====================================================================================#

ADD_DEFINITIONS(
  -DTARGET_OS=${TARGET_OS}
  -DTARGET_ARCH=${TARGET_ARCH}
  -DOS_${TARGET_OS}
  -DARCH_${TARGET_ARCH}
)

IF (TARGET_ARCH STREQUAL "ARMV7L")
SET(USE_IAP_PORT true)
SET(USE_HARDWARE_FP true)

SET(ENV{CROSSCOMPILE_PREFIX} arm-poky-linux-gnueabi)

include("toolchain/Linux_X86_32.toolchain")
ENDIF()

SET(CMAKE_BUILD_TYPE Debug)

# set etch dirs
SET(PROJECT_HOME .)
SET(PROJECT_INC_DIR inc)
SET(PROJECT_LIB_DIR libs)

# set include dirs
include_directories (${PROJECT_INC_DIR})
# set link dirs
link_directories(${PROJECT_LIB_DIR})

# set output dir
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "out/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "out/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "out/lib")

# status
message(STATUS " ")
message(STATUS "====================================================")
message(STATUS "build target:            ${CMAKE_BUILD_TYPE}")
#====================================================================================#
# SERVER
#====================================================================================#

add_executable(cmake_test
  src/main.cpp
)

IF (TARGET_OS STREQUAL "Linux")
  link_directories($ENV{TARGET_ROOT}/usr/lib)
IF (USE_IAP_PORT STREQUAL "true")  
  target_link_libraries(cmake_test pthread)
ELSE ()
  target_link_libraries(cmake_test pthread)
ENDIF ()
  IF (TARGET_ARCH STREQUAL "X86_32")
    set_target_properties(cmake_test PROPERTIES COMPILE_FLAGS "-m32 -g" LINK_FLAGS "-m32")
  ENDIF ()
ELSEIF(TARGET_OS STREQUAL "Windows")
  target_link_libraries(cmake_test pthread)
  IF (BUILD_CHECK_MEMORY)
    file (COPY ${VLD}/vld.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file (COPY ${VLD}/bin/dbghelp.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file (COPY ${VLD}/bin/vld.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    target_link_libraries (etch-cpp-appconnector-server ${VLD}/lib/vld.lib)
  ENDIF (BUILD_CHECK_MEMORY)
ELSEIF(TARGET_OS STREQUAL "QNX")
  target_link_libraries (cmake_test pthread)
ENDIF()

set_target_properties(cmake_test PROPERTIES OUTPUT_NAME "test_name")