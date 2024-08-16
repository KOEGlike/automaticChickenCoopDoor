# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Register the component
idf_component_register(
    SRCS "TM1637Display.cpp"  # Add all source files here
    INCLUDE_DIRS "include" 
    REQUIRES  "arduino" # Add include directories here
)

project(TM1637)