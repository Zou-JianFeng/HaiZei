#include "common.h"

void off_line_Record(char command[10]) {
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/off-line/";
	printf("离线存储成功 PATH : %s ", path);
	strcat(path, command);
	strcat(path, ".log");
	printf("NAME : %s\n", path + 39);
	FILE *fp = NULL;
	FILE *p = NULL;
	char buff[1000];
	fp = popen(command, "r");
	if (!fp) {
		perror("popen");
		return ;
	}
	while (fgets(buff, 1000, fp) != NULL) {
		fp = fopen(path, "a+");
		fputs(buff, fp);
	}
	fclose(fp);
	pclose(fp);
	sleep(5);
	return ;
}				

void Send(int socket_fd, int n) {
	send(socket_fd, &n, sizeof(n), 0);
}	

int Connect(int port, char* ip_addr) {
	int socket_fd;
	socket_fd = socket_connect(port, ip_addr);
	if (socket_fd < 0) {
		//perror("socket_connect");
		return -1;
	}
	return socket_fd;
}
// 192.168.1.40 ~ 

void on_line_send(char command[10], int socket_fd) {
	FILE *fp = NULL;
	char buff[1000];
	fp = popen(command, "r");
	if (!fp) {
		perror("popen");
		return ;
	}
	while (fgets(buff, 1000, fp) != NULL) {
		send(socket_fd, buff, strlen(buff), 0);
		memset(buff, 0, sizeof(buff));
	}
	pclose(fp);
	close(socket_fd);
	sleep(5);
	return ;
}

int main(int argc, char *argv[]) {
	int socket_fd;
	char* ip_addr = argv[1];
	int port = atoi(argv[2]);

	int pid = 1, x;
	for (int i = 0; i < 3; ++i) {
		if (pid != 0) {
			x = i;
			pid = fork();
		}
	}

	while(1) {
		if (pid == 0) {
			Send(socket_fd, 1);
			switch (x) {
				case 0:
					socket_fd = Connect(port, ip_addr);
					if (socket_fd == -1) off_line_Record("./test");
					else on_line_send("./test", socket_fd);
					break;
				case 1:
					socket_fd = Connect(port, ip_addr);
					if (socket_fd == -1) off_line_Record("man ls");
					else on_line_send("man ls", socket_fd);
					break;
				case 2:
					socket_fd = Connect(port, ip_addr);
					if (socket_fd == -1) off_line_Record("date");
					else on_line_send("date", socket_fd);
					break;
			}
		}
	}
 	return 0;
}