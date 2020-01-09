add_executable(Udp-client Udp-client.cxx)
add_executable(Udp-server Udp-server.cxx)

target_link_libraries(Udp-client PUBLIC og_network)
target_include_directories(Udp-client PUBLIC ${INCDIRS})

target_link_libraries(Udp-server PUBLIC og_network)
target_include_directories(Udp-server PUBLIC ${INCDIRS})
