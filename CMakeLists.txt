cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

#-------------------------------------------------------------------------------
# User configuration
#-------------------------------------------------------------------------------
# Project name
set(PROJECT_NAME    ArduinoLibraryNRF24L01Iface)

# Configure Library directory
set(LIBRARY_DIR     C:/Users/User/Documents/Arduino/libraries)

# Configure board, default Arduino UNO
set(BOARD           uno)

# Configure sketch
set(SKETCH examples/RegisterAccess/RegisterAccess.ino)

# Configure serial port, such as:
#     Windows: COM1
#     Linux:   /dev/ttyUSB0
set(SERIAL_PORT     COM1)

#-------------------------------------------------------------------------------
# Project configuation
#-------------------------------------------------------------------------------
# Configure project
project(${PROJECT_NAME})

set(NRF24L01Iface_LIBRARY_DIR    ${LIBRARY_DIR}/ArduinoLibraryNRF24L01Iface/src)

include_directories(${NRF24L01Iface_LIBRARY_DIR})

generate_arduino_library(
        nRF24L01IfaceLib
        SRCS
            ${NRF24L01Iface_LIBRARY_DIR}/NRF24L01Iface.cpp
        HDRS
            ${NRF24L01Iface_LIBRARY_DIR}/NRF24L01Iface.h
            ${NRF24L01Iface_LIBRARY_DIR}/nRF24L01_regs.h
)

set(${CMAKE_PROJECT_NAME}_SKETCH    ${SKETCH})
set(${CMAKE_PROJECT_NAME}_LIBS      nRF24L01IfaceLib)
set(${CMAKE_PROJECT_NAME}_BOARD     ${BOARD})
set(${CMAKE_PROJECT_NAME}_PORT      ${SERIAL_PORT})

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
