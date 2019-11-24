set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/base)
set(INCDIR ${PROJECT_SOURCE_DIR}/include/og/base)

set(SRC
	${SRCDIR}/SystemException.cxx
	${INCDIR}/SystemException.hpp
)

# if(UNIX)
# elseif(WIN32)
# endif()

add_library(og-base ${SRC})
