if (TARGET tinyusb_device)
    add_executable(timing
            timing.c
            )

    # pull in common dependencies
    target_link_libraries(timing pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(timing 1)
    pico_enable_stdio_uart(timing 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(timing)

    # add url via pico_set_program_url
    example_auto_set_url(timing)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building timing because TinyUSB submodule is not initialized in the SDK")
endif()
