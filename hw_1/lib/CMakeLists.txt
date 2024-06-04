project(Lab_1_lib)

set(HEADER_FILES
        CB.h
)

set(SOURCE_FILES
        CB.cpp
)

add_library(Lab_1_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})