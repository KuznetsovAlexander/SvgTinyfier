cmake_minimum_required(VERSION 3.2.0)

# set the project name
project(SvgTinyfier)
set( TARGET SvgTinyfier )

set( HEADERS
  SvgTinyfier.h
)

set( SOURCE
  main.cpp
  SvgTinyfier.cpp
)

# add the executable
add_executable( ${TARGET} ${SOURCE} ${HEADERS} ) 