export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../build/install/lib
export PATH=$PATH:../build/install/bin

#see it as a command
##Q: does it need header files when we run it, based on dynamic library??
#Q: 运行可执行文件时，需要链接动态库，链接动态库不需要头文件吗？？
mynet_example_bin ../build/install/etc/conf.dat
