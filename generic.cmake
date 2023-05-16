    #
    # @file     generic.cmake
    # @brief    Generic CMakeFile for ATXMega in VSCode and CLion
    #           Needs to be imported into the root of the individual
    #           sub projects
    # @author   Nico Verduin
    # version   1.0  original
    #           1.1  New mocro for collecting subdirectories with source files
    #           1.2  Put .map in same folder als .elf file
    #           1.3  added .hex output and a listing file output
    #           1.4  add compiling attiny1627 (and probably others as well)
    #           1.5  clean up the make file and allow default overridings for cpu and comport in local CMakelist.txt
    # @date     10-5-2023
    #

    # no need to check compilers
    set(CMAKE_C_COMPILER_WORKS 1)
    set(CMAKE_CXX_COMPILER_WORKS 1)

    # Make sure compile_commands.json is generated
    # (which is used by clangd for autocompletion and such)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # macro to get all the subdirectories from the current path
    # that contain source files
    #see also https://stackoverflow.com/questions/17653738/recursive-cmake-search-for-header-and-source-files

    MACRO(subdirlist  return_list)
        # get all files in all subdirs and put into new_list
        # filter on C source and header files
        #           C++ source and header files
        #           Assembly source and header files files
        FILE(GLOB_RECURSE  new_list  *.c *.h *.cpp *.hpp *.s *.inc)

        # create an empty list
        SET(dir_list "")

        # get the path + filename and put in into dir_path
        FOREACH(file_path ${new_list})
            # strip the file name
            GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)

            # extend our pahtname list
            SET(dir_list ${dir_list} ${dir_path})
        ENDFOREACH()

        #remove any duplicate folders
        LIST(REMOVE_DUPLICATES dir_list)

        #return a clean list
        SET(${return_list} ${dir_list})
    ENDMACRO()

    # give the project the root folder name
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)

#    include_directories(${AVR_PATH})

    string(REPLACE " " "_" ProjectId ${PROJECT_NAME})
    
    # Make sure parameters are lower case
    string(TOLOWER ${TARGET_CPU} TARGET_CPU)
    string(TOLOWER ${COMPORT} COMPORT)

    # enable usage of packs. Pack links are defined in the CMakeFile.txt of the sub project
    if(PACKS)
        include_directories(${PACKS}/include)
        add_compile_options(-B "${PACKS}/gcc/dev/${TARGET_CPU}")
        add_link_options(-B "${PACKS}/gcc/dev/${TARGET_CPU}")
    endif()

    add_compile_options("-mmcu=${TARGET_CPU}")
    add_link_options(-mmcu=${TARGET_CPU})

    # Now the project is reset to the latest state
    project(${PROJECT_NAME} C CXX NONE)

    # additional optional libraries
    # these are switched ON in the  CMakeLists.txt of a subdirectory
    if(USE_SPILIB)
        set (SPILIB         "../spi/")
        include_directories(${SPILIB})
    endif()

    if(USE_UCGLIB)
        set (UCGLIB         "../ucglib/csrc/")
        set (UCG_CALLBACK   "../ucglib/callback/")
        include_directories(${UCGLIB})
        include_directories(${UCG_CALLBACK})
    endif()

    # output a map file from the link process
    add_link_options("-Wl,--Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

    # if you want to program in C++ or assembly that option is also added
    # just the standard folders in the root
    set(PROJECT_SOURCE_DIR RECURSE "*.c" "*.h" "*.cpp" "*.hpp" "*.s" )

    # add search directories
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    SUBDIRLIST(SUBDIRS ${PROJECT_SOURCE_DIR})
    FOREACH(subdir ${SUBDIRS})
        include_directories(${subdir})
    ENDFOREACH()

    # add additional library source files. Keep in mind that it does not look in lower
    # directories
    if (USE_SPILIB)
        list( APPEND  PROJECT_SOURCE_DIR "${SPILIB}*.c" "${SPILIB}*.h")
    endif()

    if (USE_UCGLIB)
        list( APPEND PROJECT_SOURCE_DIR "${UCGLIB}*.c" "${UCGLIB}*.h" "${UCG_CALLBACK}*.c" "${UCG_CALLBACK}*.h")
    endif()

    # get all the sources. including thous from sub directories
    file(GLOB_RECURSE PROJECT_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR})

    # Set to 1 in local CmakeLists.txt and will generate lots of output
    if (VERBOSE)
        # print the memory used in the elf file. A bit useless as it contains
        # lots of info not flashed to the chip
        add_link_options(-Wl,--print-memory-usage)

        # outputs all the parts of .data and .text (mostly defined as .rodata)
        # that are remove due to --gc-sections option
        add_link_options(-Wl,--print-gc-sections)

        # show in detail every compile step
        add_compile_options("-v")

        # set verbose on during flash
        set(FLASH_VERBOSE_FLAG "-v")
    endif()

    # create our elf file
    add_executable(${PROJECT_NAME}.elf
            ${PROJECT_SRC}
    )

    # post build process
    # Clean up unused and info code y removing DEBUG info etc
    add_custom_command(
        TARGET ${PROJECT_NAME}.elf
        POST_BUILD
        # add some output formats
        COMMAND ${AVR_OBJDUMP} -h -S ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf  > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lss
        # add memory dump of data section at the end of .lss file
        COMMAND ${AVR_READELF} -x .data ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf  >>  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lss
        # remove all unneccesary labels etc
        COMMAND ${AVR_OBJCOPY} --strip-all ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
        # create an intel .hex file
        COMMAND ${AVR_OBJCOPY} -j .text -j .data  -O ihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        # memory dump after stripping als excessive info
        COMMAND ${AVR_OBJDUMP} -h -S ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf  > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_after_strip.lss
        # add memory dump of data section at the end of .lss file
        COMMAND ${AVR_READELF} -x .data ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf  >>  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_after_strip.lss
        # and show the size of our program. Change the -A to -B to get a one line size format
        # has no impact on execution
        COMMAND ${AVR_SIZE} -A ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
    )

    # For Windows avrdude needs a COMport. On a Mac it does not
    if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" OR ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        # for OSx and linux

        # avrdude PORT_COMMAND
        if (${TARGET_CPU} STREQUAL "atmega328p")
            # for the UNO we need a comport on OSx
            set(PORT_COMMAND "-P${COMPORT}")
        else()
            # for the xmega and attiny1627 we leave it out
            set(PORT_COMMAND "")
        endif()

        # the actual Avrdude command
        add_custom_target(${PROJECT_NAME}_FLASH
                ${AVR_DUDE} -p ${TARGET_CPU}  -c ${PROGRAMMER} ${PORT_COMMAND} -b115200  ${FLASH_VERBOSE_FLAG} -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf:a
                DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
        )
    else()
        # for Windows (much easier)
        # avrdude command
        add_custom_target(${PROJECT_NAME}_FLASH
            ${AVR_DUDE} -p ${TARGET_CPU} -P ${COMPORT} -c ${PROGRAMMER} -b115200  ${FLASH_VERBOSE_FLAG} -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf:a
            DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
        )
    endif()
