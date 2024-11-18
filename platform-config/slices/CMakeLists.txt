file(GLOB SLICES "${CMAKE_CURRENT_SOURCE_DIR}/*.slice")
install(FILES ${SLICES} DESTINATION ${SYSTEMD_SYSTEM_UNIT_DIR})


# If PVM_CPUS string is set by build system, add the string to the PVM's AllowedCPUs
set(PVM_CPUS "" CACHE STRING "PVM's AllowedCPUs")
if (PVM_CPUS)
    set(ALLOWED_CPUS ${PVM_CPUS})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pvm.slice.d)
    configure_file(allowed-cpus.conf.in pvm.slice.d/allowed-cpus.conf)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pvm.slice.d DESTINATION ${SYSTEMD_SYSTEM_UNIT_DIR})
endif()


# If GVM_CPUS string is set by build system, add the string to the GVM's AllowedCPUs
set(GVM_CPUS "" CACHE STRING "GVM's AllowedCPUs")
if (GVM_CPUS)
    set(ALLOWED_CPUS ${GVM_CPUS})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gvm.slice.d)
    configure_file(allowed-cpus.conf.in gvm.slice.d/allowed-cpus.conf)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gvm.slice.d DESTINATION ${SYSTEMD_SYSTEM_UNIT_DIR})
endif()
