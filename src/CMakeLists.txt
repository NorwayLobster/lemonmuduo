
add_library(${PROJECT_NAME} SHARED
    Acceptor.cc
    EpollPoller.cc
    InetAddress.cc
    Socket.cc
    SocketIO.cc
    TcpConnection.cc
)
add_library(sub::mynet ALIAS ${PROJECT_NAME}
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)