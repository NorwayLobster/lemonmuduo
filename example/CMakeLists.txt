
project(mynet_example_bin)

add_executable(mynet_example_bin
  TcpServer.cc
  main.cc
)

target_include_directories(mynet_example_bin
  PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(mynet_example_bin
  PUBLIC
    sub::mynet
)

install(TARGETS mynet_example_bin DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/TcpServer.h DESTINATION include)
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/TcpServer.h DETINATION include)