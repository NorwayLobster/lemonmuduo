# project(mynet)
add_library(${PROJECT_NAME} SHARED
    Acceptor.cc
    EpollPoller.cc
    InetAddress.cc
    Socket.cc
    SocketIO.cc
    TcpConnection.cc
    MutexLock.cc
)

add_library(sub::mynet ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
#   message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ${CMAKE_BINARY_DIR}/install")
#   set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "The path to use for make install" FORCE)
# endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
# if(cmake_install_prefix_initialized_to_default)
  message(status "set default to ${cmake_binary_dir}/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "The path to use for make install" FORCE)
  # set(cmake_install_prefix "${cmake_binary_dir}/install" CACHE STRING "The path to use for make install" FORCE)
endif()

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include)