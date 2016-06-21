# Add sources in this folder to project
file(GLOB SOURCES "*.cc")

# Generate the shared library from the sources
add_library(bdt SHARED ${SOURCES})
