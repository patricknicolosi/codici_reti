#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    int pid = fork();
    cout << "Pid:" << pid << endl;

    return 0;
}
/*
    1. Con pid() viene creato un processo figlio di questo
    2. Il processo padre continua la sua esecuzione, il processo figlio viene eseguito da qui
 */