#ifndef HTTPCONN_H_
#define HTTPCONN_H_

#include"err.h"
#include<sys/socket.h>
#include<cstdio>
#include<cstring>

#define BUFSIZ_ 1024

class Connection {
public:
	Connection(int);
private:
	int accept_(int);
	void read_rq_(void);
	void give_rqed_(void);
	void read_til_crnl(FILE *fin);

	int conn_fd;
	char buf[BUFSIZ_];
	char rq[BUFSIZ_];
	char rq_file[BUFSIZ_];
};
Connection::Connection(int listenFd)
{	
	for(;;)
	{
		conn_fd = accept_(listenFd);
		std::cout << "got a call." << std::endl;
		read_rq_();
		give_rqed_();
	}
}
inline int Connection::accept_(int listenFd)
{
        if((conn_fd = accept(listenFd, NULL, NULL)) < 0)
                        err("accept");
	return conn_fd;
}
inline void Connection::read_rq_(void)
{
	FILE *conn_in;
	if((conn_in = fdopen(conn_fd, "r")) == NULL)
                err("fdopen");
	char request[BUFSIZ_];
	if(!fgets(request, BUFSIZ_, conn_in))
                err("fgets");
	std::cout << "request: " << request << std::endl;
	read_til_crnl(conn_in);
	if(!fclose(conn_in))
		err("fclose conn_in");
	strcpy(rq_file, ".");
	sscanf(request, "%s%s", rq, rq_file+1);
}
inline void Connection::read_til_crnl(FILE *fin)
{
	while(fgets(buf, BUFSIZ_, fin) && strcmp(buf, "\r\n"))
	      continue;
}	
void Connection::give_rqed_(void)
{
	FILE *rq_in, *conn_out;
	if(strcmp(rq, "GET"))
		if(!(rq_in = fopen(rq_file, "r")))
		{
			std::cout << "can't open file: "
				  << rq_file << std::endl;
			err("fopen rq_file");
		}
		else
		{
			if(!(conn_out = fdopen(conn_fd, "w"))) 
				err("fdopen conn_fd");
			char ch;
			while((ch = getc(rq_in)) != EOF)
				putc(ch, conn_out);
		}
	fclose(rq_in);
	fclose(conn_out);
}

#endif




