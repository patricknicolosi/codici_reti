#include <iostream>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)	
	{
		cout << "Indicare indirizzo e porta" << endl;
		return -1;	
	}

	int socket_res;
	sockaddr_in remote_addr;
	char data[256];
	

	socket_res = socket(PF_INET, SOCK_DGRAM, 0);
	if(socket_res < 0)
	{
		cout << "errore durante apertura socket" << endl;
		return -1;
	}

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));

	
	strcpy(data, "Ciao");
	sendto(socket_res, data, sizeof(data) + 1, 0, (struct sockaddr*)&remote_addr, sizeof(remote_addr));
	return 0;
	
}
