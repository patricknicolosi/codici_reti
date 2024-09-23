#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

	int socket_res;
	int bind_res;

	sockaddr_in remote_addr;
	sockaddr_in local_addr;

	char res_buffer[256];

	socklen_t size = sizeof(struct sockaddr);

	// init socket
	socket_res = socket(PF_INET, SOCK_DGRAM, 0);
	if (socket_res < 0)
	{
		cout << "Errore durante la creazione del socket" << endl;
		return -1;
	}

	// init remote addr
	remote_addr.sin_port = htons(atoi(argv[1]));
	remote_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));

	// init local addr
	local_addr.sin_port = htons(atoi(argv[1]));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind for listen reponse
	bind_res = bind(socket_res, (struct sockaddr *)&local_addr, size);
	if (bind_res < 0)
	{
		cout << "Errore durante il binding, errn: " << bind_res << endl;
		return -1;
	}

	while (true)
	{
		recvfrom(socket_res, res_buffer, 99, 0, (struct sockaddr *)&remote_addr, &size);
		cout << "From: " << inet_ntoa(remote_addr.sin_addr) << ":" << ntohs(remote_addr.sin_port) << ", msg: " << res_buffer << endl;
	}

	return 0;
}