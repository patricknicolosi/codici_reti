#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "<local PORT>" << endl;
        return -1;
    }

    sockaddr_in local_addr, remote_addr;
    socklen_t size = sizeof(struct sockaddr_in);

    int socket_res;

    int bind_res;

    char buffer[256];

    socket_res = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_res < 0)
    {
        cout << "Errore creazione socket: " << socket_res << endl;
        return socket_res;
    }

    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    bind_res = bind(socket_res, (struct sockaddr *)&local_addr, size);
    if (bind_res < 0)
    {
        cout << "Errore bind: " << bind_res << endl;
        return bind_res;
    }

    while (true)
    {
        recvfrom(socket_res, buffer, 99, 0, (struct sockaddr *)&remote_addr, &size);
        cout << buffer << endl;
        sendto(socket_res, buffer, sizeof(buffer) + 1, 0, (struct sockaddr *)&remote_addr, size);
    }
}
