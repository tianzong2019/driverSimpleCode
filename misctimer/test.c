#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int fd;
//信号处理函数  
void my_signal_fun(int signum)  
{  
    unsigned char key_val;  
    read(fd, &key_val, 1);  
    printf("key_val: 0x%x\n", key_val);  
}

int main(int argc, char **argv)
{
	int val = 1;
	int Oflags;

	signal(SIGIO, my_signal_fun); 

	fd = open("/dev/arm.mali.c71", O_RDWR);
	if (fd < 0)
		printf("can't open!\n");

	//将当前进程PID设置为fd文件所对应驱动程序将要发送SIGIO,SIGUSR信号进程PID  
    fcntl(fd, F_SETOWN, getpid());
    //获取fd的打开方式  
    Oflags = fcntl(fd, F_GETFL);
    //将fd的打开方式设置为FASYNC --- 即支持异步通知
    fcntl(fd, F_SETFL, Oflags | FASYNC);

	while(1){}
    close(fd);

	return 0;
}