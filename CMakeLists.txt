cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lcdproject)

# Add this section to include the hd44780 component
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/hd44780)

# Continue with the rest of the project configuration
