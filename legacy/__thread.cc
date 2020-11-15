 ///
 /// @file    __thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-12-08 11:38:37
 ///
 
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#include <iostream>
using std::cout;
using std::endl;

//整个进程所有
int g_number = 100;

//线程特有数据(线程局部存储TLS)
__thread int t_number = 0;


void * threadfunc0(void * arg)
{
	t_number = 10;
	printf("thread0: t_number = %d, g_number = %d\n", t_number, g_number);

	printf("thread0: &errno=%p\n", &errno);

	return NULL;
}

void * threadfunc1(void * arg)
{
	t_number = 20;
	printf("thread1: t_number = %d, g_number = %d\n", t_number, g_number);
	printf("thread1: &errno=%p\n", &errno);
	return NULL;
}

int main(void)
{
	t_number = 30;
	pthread_t pthid1, pthid2;
	pthread_create(&pthid1, NULL, threadfunc0, NULL);
	pthread_create(&pthid2, NULL, threadfunc1, NULL);
	//errno并不是全局变量，而是线程特有数据
	printf("main: &errno=%p\n", &errno);
	printf("main: t_number = %d, g_number = %d\n", t_number, g_number);

	pthread_join(pthid1, NULL);
	pthread_join(pthid2, NULL);

	return 0;
}
