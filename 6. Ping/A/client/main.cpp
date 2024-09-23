#include <iostream>
#include <arpa/inet.h>
#include <chrono>
#include <unistd.h>

using namespace std;

long long nowInMilliseconds()
{
    chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
}

long long differenceFromNow(long long old)
{
    long long now = nowInMilliseconds();
    return now - old;
}

int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        cout << "<remote IP><remote PORT><local PORT>" << endl;
        return -1;
    }

    int pid = fork();

    if (pid == 0)
    {
        // send
        int socket_res;

        sockaddr_in remote_addr;

        string buffer;

        socket_res = socket(PF_INET, SOCK_DGRAM, 0);
        if (socket_res < 0)
        {
            cout << "Errore socket() : " << socket_res;
            return -1;
        }

        remote_addr.sin_port = htons(atoi(argv[2]));
        remote_addr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));

        while (true)
        {
            buffer = "Ping=" + to_string(nowInMilliseconds());
            sendto(socket_res, buffer.c_str(), buffer.length() + 1, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
            sleep(1);
        }
    }
    else
    {
        // receive
        sockaddr_in remote_addr;
        sockaddr_in local_addr;
        socklen_t size = sizeof(sockaddr_in);

        int socket_res;
        int bind_res;

        char buffer[32];

        socket_res = socket(PF_INET, SOCK_DGRAM, 0);
        if (socket_res < 0)
        {
            cout << "Errore socket() : " << socket_res;
            return -1;
        }

        local_addr.sin_port = htons(atoi(argv[2]));
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_family = AF_INET;

        bind_res = bind(socket_res, (struct sockaddr *)&local_addr, size);
        if (bind_res < 0)
        {
            cout << "Errore bind() : " << bind_res;
            return -1;
        }

        while (true)
        {
            recvfrom(socket_res, buffer, 20, 0, (struct sockaddr *)&remote_addr, &size);

            string bufferString;
            bufferString.assign(buffer);

            cout << differenceFromNow(stoll(bufferString.substr(5))) << "ms, from:" << inet_ntoa(remote_addr.sin_addr) << endl;
        }
    }
    return 0;
}
