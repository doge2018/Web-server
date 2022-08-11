#ifndef SERVER_H_
#define SERVER_H_

#include"err.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>

class Server {
public:
	Server(int, int);
	int get_listen_fd_(void) { return listen_fd; }
private:
	int listen_fd;
	int port_num;
	struct sockaddr_in sin;
	int listen_q;
	int ret_val = -1;

	void init_socket_(void);
	void init_addr_(void);
	void bind_(void);
	void listen_(void);
};
inline void Server::init_socket_(void)
{
	if((listen_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err("socket");
}
inline void Server::init_addr_(void)
{
	bzero((void *)&sin,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port_num);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
}
inline void Server::bind_(void)
{
	if((ret_val = bind(listen_fd,(struct sockaddr *)&sin,
			sizeof(sin))) < 0)
		err("bind");
}
inline void Server::listen_(void)
{
	if((ret_val = listen(listen_fd, listen_q)) < 0)
		err("listen");
}
inline Server::Server(int portNum, int listenQ = 1):
              port_num(portNum), listen_q(listenQ)
{
	init_socket_();
	init_addr_();
	bind_();
	listen_();
}

#endif
