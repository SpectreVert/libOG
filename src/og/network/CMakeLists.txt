set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/network)
set(HEADIR ${PROJECT_SOURCE_DIR}/include/og/network)

set(SRC
	${SRCDIR}/Socket.cxx
	${HEADIR}/Socket.hpp
	${SRCDIR}/UdpSocket.cxx
	${HEADIR}/UdpSocket.hpp
	${SRCDIR}/SocketImplementation.hpp
	${HEADIR}/ip/Ipv4.hpp
	${SRCDIR}/ip/Ipv4.cxx
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
target_include_directories(og-network PUBLIC ${INCDIRS})

if(WIN32)
	target_link_libraries(og-base PRIVATE ws2_32)
endif()
