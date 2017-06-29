#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

char buffer[512];

int factor(int src)
{
if ((src==0)||(src==1))
return 1;
else
return src*factor(src-1);
}

int main()
{

int socket1, listener;
struct sockaddr_in addr;
int bytes_read;


listener = socket(AF_INET, SOCK_STREAM, 0);

if (listener < 0)
{
perror("socket");
exit(1);
}

addr.sin_family = AF_INET;
addr.sin_port = htons(3425);
addr.sin_addr.s_addr = htonl(INADDR_ANY);
if(connect(socket1, (struct sockaddr *) &addr, sizeof(addr))<0)
{
perror("bind");
exit(2);
}

listen(listener,1);

while(1)
{
socket1 = accept(listener, NULL, NULL);
if (socket1 < 0)
{
perror("accept");
exit(3);
}

while(1)
{
bytes_read = recv(socket1, buffer, 512, 0);
if (bytes_read < 0) break;

int temp = atoi(buffer);
if (temp >= 0)
{
int fact = factor(temp);
char fact1[16];
sprintf(fact1," %d", fact);
send(socket1,fact1,sizeof(fact1),0);
}
else send(socket1, "Wrong input!\n", 13, 0);
}
}
return 0;
}
