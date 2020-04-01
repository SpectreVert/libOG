GetVersion(${CMAKE_CURRENT_LIST_DIR}/VERSION.txt)

message(STATUS "Configuring libog_network ${MAJOR}.${MINOR}.${PATCH}")

set(SRCDIR ${PROJECT_SOURCE_DIR}/src/og/network)
set(HEADIR ${PROJECT_SOURCE_DIR}/include/og/network)

set(SRC
	${SRCDIR}/Socket.cxx
	${HEADIR}/Socket.hpp
	${SRCDIR}/UdpSocket.cxx
	${HEADIR}/UdpSocket.hpp
	${SRCDIR}/TcpStream.cxx
	${HEADIR}/TcpStream.hpp
	${SRCDIR}/Event.cxx
	${HEADIR}/Event.hpp
	${SRCDIR}/Poll.cxx
	${HEADIR}/Poll.hpp
	${HEADIR}/Registry.hpp
	${HEADIR}/Selector.hpp
	${SRCDIR}/TcpListener.cxx
	${HEADIR}/TcpListener.hpp
	${HEADIR}/SocketImplementation.hpp
	${HEADIR}/Ipv4.hpp
	${SRCDIR}/Ipv4.cxx
	${HEADIR}/HttpHeaders.hpp
	${SRCDIR}/HttpHeaders.cxx
	${HEADIR}/HttpMessage.hpp
)

if(UNIX)
	set(SRC
		${SRC}
		${SRCDIR}/unix/SocketImplementation.cxx
		${HEADIR}/unix/SocketImplementation.hpp
		${SRCDIR}/unix/Selector.cxx
		${HEADIR}/unix/Selector.hpp
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
)
install(DIRECTORY ${HEADIR}
	DESTINATION include/og
	COMPONENT Development
)
install(FILES ${HEADIR}/../network.hpp
	DESTINATION include/og
	COMPONENT Development
)
