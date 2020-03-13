add_executable(Udp-client Udp-client.cxx)
add_executable(Udp-server Udp-server.cxx)
add_executable(Tcp-client Tcp-client.cxx)
add_executable(Tcp-server Tcp-server.cxx)
add_executable(Async-Io Async-Io.cxx)

target_link_libraries(Udp-client PUBLIC og_network)
target_include_directories(Udp-client PUBLIC ${INCDIRS})

target_link_libraries(Udp-server PUBLIC og_network)
target_include_directories(Udp-server PUBLIC ${INCDIRS})

target_link_libraries(Tcp-client PUBLIC og_network)
target_include_directories(Tcp-client PUBLIC ${INCDIRS})

target_link_libraries(Tcp-server PUBLIC og_network)
target_include_directories(Tcp-server PUBLIC ${INCDIRS})

target_link_libraries(Async-Io PUBLIC og_network)
target_include_directories(Async-Io PUBLIC ${INCDIRS})
