    #
    # @file     CMakeLists.txt
    # @brief    root CMakeList.txt for sub projects
    # @author   Nico Verduin
    # version   1.1 added PROGRAMMER
    # @date     10-5-2023
    #

    # If you want to see lots of verbose output from the compilers
    set (VERBOSE )

    # alternative CPU
    set (TARGET_CPU attiny1627)

    add_compile_options("-D__AVR_ATtiny1627__")
    add_compile_options("-D__AVR_DEVICE_NAME__=attiny1627")
    add_compile_options("-D__AVR_DEV_LIB_NAME__=tn1627")

    # if we use PACKS (i.e. attiny1627) else comment this line
    set(PACKS "${DEV_ROOT}/Microchip.ATtiny_DFP.3.0.151" )

    # alternative COMPORT default is usb  
    # set (COMPORT com11)

    # my macbook
    #set (COMPORT "/dev/cu.usbmodemFA131") The attiny is programmed through usb

    # programmer if different than avrispmkII
    set(PROGRAMMER pkobn_updi)

    # do not change this last line below
    include(../generic.cmake)

