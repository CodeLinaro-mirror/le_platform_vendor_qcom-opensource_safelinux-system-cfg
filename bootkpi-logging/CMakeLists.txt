# VERSIONS

cmake_minimum_required(VERSION 3.16)

project(BootKPILogging)

# Allows us to use CMAKE_INSTALL_<dir> for installation destinations.
# See available variables at https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

# Helpful 'set'

set(HEADER_FILE include/logging.h)
set(PKGCONFIG_FILE_IN bootkpi-logging.pc.in)
set(PKGCONFIG_FILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/bootkpi-logging.pc)
set(PKG_VERSION "1.0.0")

# Install Instructions

configure_file(${PKGCONFIG_FILE_IN} ${PKGCONFIG_FILE_OUT})

install(FILES ${HEADER_FILE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bootkpi)
install(FILES ${PKGCONFIG_FILE_OUT} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
