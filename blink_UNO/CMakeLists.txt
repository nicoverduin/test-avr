    #
    # @file     CMakeLists.txt
    # @brief    root CMakeList.txt for sub projects
    # @author   Nico Verduin
    # @date     29-3-2023
    #

    # If you want to see lots of verbose output from the compilers
    set (VERBOSE)

    # alternative CPU
    set (TARGET_CPU atmega328p)

    # alternative COMPORT
    set (COMPORT com11)

    # programmer
    set(PROGRAMMER arduino)

    # mijn macbook
    #set (COMPORT "/dev/cu.usbmodemFA131")

    # do not change this last line below
    include(../generic.cmake)

