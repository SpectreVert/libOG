cmake_minimum_required(VERSION 2.6)
# cmake_policy(set cmp0048 new)

project( libOG )

# Define location for cmake acess to headers
set(INCDIRS
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)

# Add all libraries to build
# TODO: add a method to chose what to build
add_subdirectory(src/og)

# Add examples to build
add_subdirectory(examples)
