#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fds[2];
	
	if (pipe(fds) < 0) {
		perror("pipe");
		return 1;
	}

	char buf[1024];

	printf("Please enter:");
	fflush(stdout);	//对标准输出流的清理，但不是丢掉数据，而是及时打印数据到屏幕上
	ssize_t s = read(0, buf, sizeof(buf) - 1);	//0对应文件描述符

	if (s > 0) {	//判断读取的字节数
		buf[s] = 0;
	}
	
	pid_t pid = fork();

	if (pid == 0) {	//child process logic
		close(fds[0]);	//close the read function
		while(1) {
			sleep(1);
			write(fds[1], buf, strlen(buf));	//write the buf to pipe
		}
	}
	else {	//father process logic
		close(fds[1]);	//close the write function
		char buf1[1024];
		while(1) {
			ssize_t s = read(fds[0], buf1, sizeof(buf1) - 1);	//read the data from pipe and put into buf1
			if (s > 0) {
				buf1[s - 1] = 0;
				printf("client->farther: %s\n", buf1);
			}
		}
	}
}

