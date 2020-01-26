GetVersion(${CMAKE_CURRENT_LIST_DIR}/VERSION.txt)

message(STATUS "Configuring libog_network ${MAJOR}.${MINOR}.${PATCH}")

set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/network)
set(HEADIR ${PROJECT_SOURCE_DIR}/include/og/network)

set(SRC
	${SRCDIR}/Socket.cxx
	${HEADIR}/Socket.hpp
	${SRCDIR}/UdpSocket.cxx
	${HEADIR}/UdpSocket.hpp
	${SRCDIR}/TcpSocket.cxx
	${HEADIR}/TcpSocket.hpp
	${SRCDIR}/TcpListener.cxx
	${HEADIR}/TcpListener.hpp
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

add_library(og_network ${SRC})
target_link_libraries(og_network PUBLIC og_base)
target_include_directories(og_network PUBLIC ${INCDIRS})

if(WIN32)
	target_link_libraries(og_base PRIVATE ws2_32)
endif()

install(TARGETS og_network
				ARCHIVE
					DESTINATION lib
					COMPONENT Libraries
				PUBLIC_HEADER
					DESTINATION include
					COMPONENT Development
)
