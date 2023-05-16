    #
    # @file     CMakeLists.txt
    # @brief    root CMakeList.txt for sub projects
    # @author   Nico Verduin
    # @date     29-3-2023
    #

    # set optional used libraries
    #set (USE_SPILIB 1)
    #set (USE_UCGLIB 1)

    # If you want to see lots of verbose output from the compilers
    set (VERBOSE)

    # target cpu
    set(TARGET_CPU atxmega256a3u)

    # comport
    set(COMPORT usb)

    # do not change this last line below
    include(../generic.cmake)

