#include "common.h"

void record_log(char path[100]) {
	char commond[10] = "date";
	char buff[100];
	FILE *fp = NULL;
	fp = popen(commond, "r");
	fgets(buff, 1000, fp);
	printf("时间 : %s", buff);
	printf("路径 : %s\n", path);
}

void record_commond(char commond[10], char str[10], int socketfd) {
	int a;
	char path[100] = "/Users/zou-jianfeng/HZ/8.23/on_line/";
	strcat(path, str);
	strcat(path, commond);
	strcat(path, ".log");
	printf("存储成功 PATH : %s \n", path);
	char buff[MAX_SIZE];
	FILE *fp = NULL;
	while ((a = recv(socketfd, buff, MAX_SIZE, 0)) > 0) {
   		fp = fopen(path, "a+");
   		fputs(buff, fp);
		fflush(stdout);
		memset(buff, 0, sizeof(buff));	
	}
	fclose(fp);
	//record_log(path);
}

void choose_Pi(char str[10], int ind, int socketfd) {
	switch (ind) {
		case 1 :
			record_commond("test", str, socketfd);
		case 2 :
			record_commond("a.sh", str, socketfd);
		case 3 :
			record_commond("date", str, socketfd);
	}
}

int main(int argc, char const *argv[]) {
	int server_listen, socketfd, port, pid;
	if (argc != 2) {
		printf("Usage\n");
		exit(0);
	}

	port = atoi(argv[1]);

	if ((server_listen = socket_create(port)) < 0) {
		printf("Error\n");
		exit(1);
	} 

	while(1) {
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		if((socketfd = accept(server_listen, (struct sockaddr*) &client_addr, &len)) < 0) {
			break;
		}

		struct sockaddr_in peer;
		
		socklen_t peer_len = sizeof(struct sockaddr_in);
		bzero(&peer, sizeof(struct sockaddr_in));
		getpeername(socketfd, (struct sockaddr *)&peer, &peer_len);
		char buff_peer[64] = {'\0'};
		inet_ntop(AF_INET, (void*)&peer.sin_addr, buff_peer, 63);

		if ((pid = fork()) < 0) {
			printf("Error\n");
		}
		if (pid == 0) {
			close(server_listen);
			int ind;
			int n = recv(socketfd, &ind, sizeof(n), 0);
			switch (ind) {
				case 1 :
					n = recv(socketfd, &ind, sizeof(n), 0);
					choose_Pi("Pi_1/", ind, socketfd);
					break;
				case 2 :
					n = recv(socketfd, &ind, sizeof(n), 0);
					choose_Pi("Pi_2/", ind, socketfd);
				 	break;
				case 3 :
					n = recv(socketfd, &ind, sizeof(n), 0);
					choose_Pi("Pi_3/", ind, socketfd);
					break;
			}

			close(socketfd);
		}
		close(socketfd);
	}

	return 0;
}