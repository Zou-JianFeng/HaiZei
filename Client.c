#include "common.h"
#define MAX_LEN 100000		
#define commondsize 20		

int Connect(int port, char* ip_addr) {
	int socket_fd;
	socket_fd = socket_connect(port, ip_addr);
	if (socket_fd < 0) return -1;
	return socket_fd;
} // 连接 Maseter

char *ten_record(char commond[commondsize]) {
	int n = 10, i = 0;
	char *buff = (char *)malloc(MAX_LEN);
	while (n--) {
		char c;
		FILE *fp = popen(commond, "r");
		while (~fscanf(fp, "%c", &c)) {
			buff[i++] = c;
		}
		pclose(fp);
		sleep(5);
	}
	buff[i] = '\0';
	return buff;
}

void off_line(char commond[commondsize]) {
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/off_line/Pi_1/"; // 线下存储路径
	strcat(path, commond + 5);
	strcat(path, ".log"); 
	char *buff = ten_record(commond);
}

void Check_connect(char commond[commondsize], int socket_fd) {
	if (socket_fd == -1) off_line(commond);
	else 
}

int main(int argc, char *argv[]) {
	int socket_fd;
	char *ip_addr = argv[1];
	int port = atoi(argv[2]);

	int pid = 1, x;
	for (int i = 0; i < 6; ++i) {
		if (pid != 0) {
			x = i;
			pid = fork();
		}
	}

	while(1) {
		if (pid == 0) {
			socket_fd = Connect(port, ip_addr);
			#define temp(a) Check_connect(a, socket_fd); break;
			switch (x) {
				case 0: temp("Bash system.sh")
				case 1: temp("Bash disk.sh")
				case 2: temp("Bash test1.sh")
				case 3: temp("Bash test2.sh")
				case 4: 
					sleep(100);
					break;
				case 5: 
					sleep(100);
					break;
				default :
					printf("fork出错\n");
					break;
			}
			#undef temp
		}
	}
 	return 0;
}