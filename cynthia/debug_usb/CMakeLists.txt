if (TARGET tinyusb_device)
    add_executable(debug_usb
            debug_usb.c
            )

    # pull in common dependencies
    target_link_libraries(debug_usb pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(debug_usb 1)
    pico_enable_stdio_uart(debug_usb 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(debug_usb)

    # add url via pico_set_program_url
    example_auto_set_url(debug_usb)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building debug_usb because TinyUSB submodule is not initialized in the SDK")
endif()
