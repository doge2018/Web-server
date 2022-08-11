#include"server.h"
#include"httpconn2.h"

int main(void)
{
        const int portNum = 13000;
        Server serv(portNum);
        Connection(serv.get_listen_fd_());
        return 0;
}

