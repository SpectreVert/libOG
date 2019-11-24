project( libOG )

cmake_minimum_required(VERSION 2.6)
# cmake_policy(set cmp0048 new)

# Define location for cmake acess to headers
set(INCDIRS
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(src/og)
