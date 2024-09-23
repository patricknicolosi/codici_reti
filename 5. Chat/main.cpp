#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int send(char **argv)
{
    int socket_res;
    sockaddr_in remote_addr;
    char data[100];

    socket_res = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_res < 0)
    {
        cout << "Errore durante apertura socket invio";
        return socket_res;
    }

    inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(atoi(argv[2]));

    while (fgets(data, sizeof(data), stdin) != NULL)
    {
        sendto(socket_res, data, sizeof(data) + 1, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
    }

    return 0;
}

int receive(char **argv)
{
    int socket_res;
    int bind_res;
    sockaddr_in remote_addr;
    sockaddr_in local_addr;
    char data[256];

    socklen_t size = sizeof(struct sockaddr);

    socket_res = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_res < 0)
    {
        cout << "Errore durante apertura socket invio";
        return socket_res;
    }

    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(atoi(argv[3])); // TODO: Check!

    bind_res = bind(socket_res, (struct sockaddr *)&local_addr, size);
    if (bind_res < 0)
    {
        cout << "Errore durante il binding";
        return bind_res;
    }

    while (true)
    {
        recvfrom(socket_res, data, 20, 0, (struct sockaddr *)&remote_addr, &size);
        cout << "		Msg: " << data << ", From:" << inet_ntoa(remote_addr.sin_addr) << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int pid = fork();

    if (pid == 0)
    {
        int res = send(argv);
        if (res < 0)
        {
            cout << "Errore " << res;
            return res;
        }
    }
    else
    {
        int res = receive(argv);
        if (res < 0)
        {
            cout << "Errore " << res;
            return res;
        }
    }

    return 0;
}