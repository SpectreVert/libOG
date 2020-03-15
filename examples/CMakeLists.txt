add_executable(Async-Io Async-Io.cxx)

target_link_libraries(Async-Io PUBLIC og_network)
target_include_directories(Async-Io PUBLIC ${INCDIRS})
