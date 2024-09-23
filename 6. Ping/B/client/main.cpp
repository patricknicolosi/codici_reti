#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
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

    if (argc < 3)
    {
        cout << "<remote IP><remote PORT>" << endl;
        return -1;
    }

    sockaddr_in remote_addr;
    socklen_t size = sizeof(struct sockaddr_in);

    int socket_res;

    socket_res = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_res < 0)
    {
        cout << "Errore creazione socket: " << socket_res << endl;
        return socket_res;
    }

    int pid = fork();

    if (pid == 0)
    {
        remote_addr.sin_port = htons(atoi(argv[2]));
        remote_addr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));

        while (true)
        {
            string buffer = "Ping:";

            buffer += to_string(nowInMilliseconds());

            sendto(socket_res, buffer.c_str(), buffer.length() + 1, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
            sleep(1);
        }
    }
    else
    {
        char buffer[32];
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
