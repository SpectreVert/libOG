GetVersion(${CMAKE_CURRENT_LIST_DIR}/VERSION.txt)

message(STATUS "Configuring libog_base ${MAJOR}.${MINOR}.${PATCH}")

set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/base)
set(HEADIR ${PROJECT_SOURCE_DIR}/include/og/base)

set(SRC
	${SRCDIR}/SystemException.cxx
	${HEADIR}/SystemException.hpp
)

# if(UNIX)
# elseif(WIN32)
# endif()

add_library(og_base ${SRC})
target_include_directories(og_base PUBLIC ${INCDIRS})

install(TARGETS og_base
		ARCHIVE
			DESTINATION lib
			COMPONENT Libraries
)
install(DIRECTORY ${HEADIR}
	DESTINATION include/og
	COMPONENT Development
)
