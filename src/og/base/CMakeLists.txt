set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/base)
set(HEADIR ${PROJECT_SOURCE_DIR}/include/og/base)

set(SRC
	${SRCDIR}/SystemException.cxx
	${HEADIR}/SystemException.hpp
)

# if(UNIX)
# elseif(WIN32)
# endif()

add_library(og-base ${SRC})
target_include_directories(og-base PUBLIC ${INCDIRS})
