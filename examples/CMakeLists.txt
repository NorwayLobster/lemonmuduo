
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