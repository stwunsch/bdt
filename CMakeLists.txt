# Set minimum cmake version
cmake_minimum_required(VERSION 3.1)

# Enable test cases
enable_testing()

# Setup project
project(bdt CXX)

# Add include dir
include_directories(inc)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)
