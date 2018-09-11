#include "common.h"
#define MAX_LEN 100000
#define Path_LEN 100		
#define commondsize 20	
#define frequency 1

int Connect(int, char *);
void Write(char *, char *);
char *Read(char *);

void record(char *, char *);
char *ten_record(char *, int, int);
void off_line(char *, int);
void Check_connect(char *, int, int);
void send_record(char *, int, int);
void send_off(char *, int);
void send_on(char *, int, int);
char *Check_warning(char *, int);
char *Name(char *);

int main(int argc, char *argv[]) {
	int socket_fd;
	char *ip_addr = "192.168.1.182";
	char *Port = "2118";
	int port = atoi(Port);

	int pid = 1, x;
	for (int i = 0; i < 4; ++i) {
		if (pid != 0) {
			x = i;
			pid = fork();
		}
	}

	while(1) {
		if (pid == 0) {
			socket_fd = Connect(port, ip_addr);
			#define temp(a, b) Check_connect(a, b, socket_fd); break;
			switch (x) {
				case 0: temp("Bash system.sh", 6)
				case 1: temp("Bash disk.sh", 3)
				case 2: temp("Bash test1.sh", 10)
				case 3: temp("Bash mem.sh", 5)
				default :
					printf("fork出错\n");
					break;
			}
			#undef temp
		} else {
			sleep(1);
		}
	}
 	return 0;
}

void Check_connect(char commond[commondsize], int n, int socket_fd) {
	if (socket_fd == -1) off_line(commond, n);
	else send_record(commond, socket_fd, n);
}

char *Name(char commond[commondsize]) {
	char *name = (char *)malloc(10);
	strcpy(name, commond);
	int n = strlen(name) - 3;
	name[n] = '\0';
	return name + 5;
}

void off_line(char commond[commondsize], int n) {
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/off_line/Pi_1/";
	char *name = Name(commond);
	strcat(path, name);
	strcat(path, ".log"); 
	char *buff = ten_record(commond, n, -123321);
	Write(buff, path);
	record(": 请求连接失败 ", commond);
}

void send_record(char commond[commondsize], int socket_fd, int n) {
	send(socket_fd, Name(commond), strlen(commond), 0);
	send_off(commond, socket_fd);
	send_on(commond, socket_fd, n);
}

void record(char ans[20], char commond[commondsize]) {
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/off_line/Pi_1/pihealthd.log";
	char buff[MAX_LEN] = {0};
	strcpy(buff, Read("date"));
	int n = strlen(buff);
	buff[n - 1] = ' ';
	strcat(buff, ans);
	char *name = Name(commond);
	strcat(buff, name);
	strcat(buff, "\n");
	strcat(buff, "\n");
	Write(buff, path);
	//printf("日志存储成功 : %s\n", path);
	//printf("%s\n", buff);
}

char *Check_warning(char buff[MAX_LEN], int socket_fd) {
	int n = strlen(buff) - 2;
	if (buff[n] == '$') {
		//printf("worning\n");
		buff[n] = '\n';
		buff[n + 1] = '\0';
		if (socket_fd == -123321) {
			Write(buff, "/Users/zou-jianfeng/HZ/8.23/off_line/Pi_1/warning.log");
		} else {
			send(socket_fd, "$", 1, 0);
			send(socket_fd, buff, strlen(buff), 0);
		}
		buff[n] = ' ';
	}
	return buff;
}

char *ten_record(char commond[commondsize], int n, int socket_fd) {
	int f = frequency;
	char *buff = (char *)malloc(MAX_LEN);
	char *temp = (char *)malloc(MAX_LEN);
	while (f--) {
		temp = Check_warning(Read(commond), socket_fd);
		strcat(buff, temp);
		sleep(n);
	}
	//strcat(buff, "\n");
	strcat(buff, "\0");
	return buff;
}

void send_off(char commond[commondsize], int socket_fd) {
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/off_line/Pi_1/";
	char *name = Name(commond);
	strcat(path, name);
	strcat(path, ".log");
	FILE *fp = fopen(path, "r");
	if (!fp) return ;
	char buff[MAX_LEN];
	while (fgets(buff, 1000, (FILE*)fp) != NULL) {
		send(socket_fd, buff, strlen(buff), 0);
	}
	remove(path);
	record(": 离线发送成功 ", commond);
}

void send_on(char commond[commondsize], int socket_fd, int n) {
	char *buff = ten_record(commond, n, socket_fd);
	send(socket_fd, buff, strlen(buff), 0);
	record(": 在线发送成功 ", commond);
}

int Connect(int port, char* ip_addr) {
	int socket_fd;
	socket_fd = socket_connect(port, ip_addr);
	if (socket_fd < 0) return -1;
	return socket_fd;
} 

void Write(char buff[MAX_LEN], char path[Path_LEN]) {
	FILE *fp = fopen(path, "a+");
	if (!fp) return;
	fputs(buff, fp);
	fclose(fp);
}

char *Read(char commond[commondsize]) {
	int i = 0;
	char c;
	char *buff = (char *)malloc(MAX_LEN);
	FILE *fp = popen(commond, "r");
	while (~fscanf(fp, "%c", &c)) {
		buff[i++] = c;
	}
	pclose(fp);
	return buff;
}