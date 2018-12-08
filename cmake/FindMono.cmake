include(LibFindMacros)

libfind_pkg_detect(MONO mono-2.0
        FIND_PATH mono/jit/jit.h
        PATH_SUFFIXES mono-2.0
        FIND_LIBRARY NAMES mono-2.0
        )

libfind_process(MONO)
