if (Node_FOUND)
    return()
endif()

find_program (NODEJS_EXECUTABLE NAMES node nodejs
    HINTS
    ${NODE_DIR} $ENV{NODE_DIR}
    PATH_SUFFIXES bin
    DOC "Node.js interpreter")

include (FindPackageHandleStandardArgs)

if (NODEJS_EXECUTABLE)
    execute_process(COMMAND ${NODEJS_EXECUTABLE} --version
        OUTPUT_VARIABLE _VERSION
        RESULT_VARIABLE _NODE_VERSION_RESULT)
    if (NOT _NODE_VERSION_RESULT)
        string (REPLACE "v" "" NODE_VERSION_STRING "${_VERSION}")
        string (REPLACE "." ";" _VERSION_LIST "${NODE_VERSION_STRING}")
        list (GET _VERSION_LIST 0 NODE_VERSION_MAJOR)
        list (GET _VERSION_LIST 1 NODE_VERSION_MINOR)
        list (GET _VERSION_LIST 2 NODE_VERSION_PATCH)
    else ()
        set (NODE_VERSION_STRING "0.10.30")
        set (NODE_VERSION_MAJOR "0")
        set (NODE_VERSION_MINOR "10")
        set (NODE_VERSION_PATCH "30")
        message (STATUS "defaulted to node 0.10.30")
    endif ()
    string (REGEX REPLACE "\n" "" NODE_VERSION_STRING ${NODE_VERSION_STRING})

    mark_as_advanced (NODEJS_EXECUTABLE)
endif ()

find_package_handle_standard_args (Node
    REQUIRED_VARS NODEJS_EXECUTABLE
    VERSION_VAR NODE_VERSION_STRING)
