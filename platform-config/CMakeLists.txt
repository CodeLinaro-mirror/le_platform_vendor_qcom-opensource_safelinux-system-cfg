cmake_minimum_required(VERSION 3.16)

project(QcomPlatformConfig)

include(GNUInstallDirs)

find_package(PkgConfig)
# Get systemd unitdir from systemd's pkg config file
pkg_check_modules(SYSTEMD REQUIRED "systemd")
pkg_get_variable(SYSTEMD_SYSTEM_UNIT_DIR systemd "systemdsystemunitdir")

add_subdirectory(slices)
