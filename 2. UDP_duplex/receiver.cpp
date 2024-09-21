#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[])
{
	socklen_t size = sizeof(struct sockaddr);
	sockaddr_in local_addr, remote_addr;
	char buffer[256];

	int bind_res;
	int socket_res;

	socket_res = socket(PF_INET, SOCK_DGRAM, 0);
	if(socket_res < 0)
	{
		cout << "Errore durante apertura del socket" << endl;
		return -1;
	}

	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(atoi(argv[1]));
  	local_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

	bind_res = bind(socket_res, (struct sockaddr*) &local_addr, size);
	if(bind_res < 0)
	{
		cout << "Errore durante la creazione del socket, errn:" << socket_res << endl;
		return -1;
	}

	string response = "world!";
	while(true)
	{
		recvfrom(socket_res, buffer, 99, 0, (struct sockaddr*) &remote_addr, &size);
		cout << "From: " << inet_ntoa(remote_addr.sin_addr);
		cout << ": " << ntohs(remote_addr.sin_port);
		cout << ", msg: " << buffer << endl;

		// Send response
		sendto(socket_res, response.c_str(), response.length() + 1, 0, (struct sockaddr*) &remote_addr, size);
	}

}