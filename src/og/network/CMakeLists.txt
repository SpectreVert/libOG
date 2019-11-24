set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/network)
set(INCDIR ${PROJECT_SOURCE_DIR}/include/og/network)

set(SRC
	${SRCDIR}/Socket.cxx
	${INCDIR}/Socket.hpp
	${SRCDIR}/SocketImplementation.hpp
)

if(UNIX)
	set(SRC
		${SRC}
		${SRCDIR}/unix/SocketImplementation.cxx
		${SRCDIR}/unix/SocketImplementation.hpp
	)
elseif(WIN32)
	set(SRC
		${SRC}
		${SRCDIR}/windows/SocketImplementation.hpp
	)
endif()

add_library(og-network ${SRC})
target_link_libraries(og-network PUBLIC og-base)
if(WIN32)
	target_link_libraries(og-base PRIVATE ws2_32)
endif()
