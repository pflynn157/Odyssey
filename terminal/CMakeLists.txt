cmake_minimum_required(VERSION 3.0.0)
project(odyssey_terminal)

include_directories(
    "/usr/X11R6/include"
    "/usr/include/freetype2"
    "/usr/include/libpng16"
)

set(SRC
    st.c
    x.c
)

add_executable(odyt ${SRC})

target_link_libraries(odyt
    m rt X11 util Xft
    fontconfig freetype
)