add_executable(Async-Udp Async-Udp.cxx)
add_executable(Async-Tcp Async-Tcp.cxx)

target_link_libraries(Async-Udp PUBLIC og_network)
target_link_libraries(Async-Tcp PUBLIC og_network)
target_include_directories(Async-Udp PUBLIC ${INCDIRS})
target_include_directories(Async-Tcp PUBLIC ${INCDIRS})
