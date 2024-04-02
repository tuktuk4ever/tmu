file(
    GLOB_RECURSE files
        *.h
        *.cpp
        *.c
)

set(dependencies
        freertos
        esp_system
        arduino-esp32
        fmt
        ArduinoJson
        espchrono
        cpputils
        espcpputils
        espconfiglib
        espwifistack
        esphttpdutils
        mdns
        mqtt
        esp_app_format
)

idf_component_register(
    SRCS
        ${files}
    INCLUDE_DIRS
        .
    REQUIRES
        ${dependencies}
)

execute_process(
    COMMAND git describe --tags --always
    WORKING_DIRECTORY ${COMPONENT_DIR}/..
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -fdiagnostics-color=always
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
        -DGIT_VERSION=\"${GIT_VERSION}\"
)
