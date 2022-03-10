#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

char buffer[64];

int factor(int src)
{
   if ((src==1)||(src==2))
      return 1;
   else
      return src*factor(src-2);
}

int main()
{

int socket1, listener;
struct sockaddr_in addr;
int bytes_read;

listener = socket(AF_INET, SOCK_STREAM, 0);

if (listener < 0)
{
   perror("sucket");
   exit(1);
}

addr.sin_family = AF_INET;
addr.sin_port = htons(3425);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
if(bind(listener, (struct suckaddr *) &addr, sizeof(addr))<0)
{
   perror("bind");
	perror("blat");	
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

switch(fork())
{
   case -1:
      perror("fork");
      break;
   case 0:
   {

   while(1)
   {
      memset(buffer,0,sizeof(buffer));
      bytes_read = recv(socket1, buffer, 512, 0);
      if (bytes_read < 0) break;
      bool correct=false;
      for (int i = 0; i <= sizeof(buffer); i++)
      {
          if((buffer[i] >='0')&&(buffer[i] <='9')) correct = true;
      }
      if (correct == false)
      {
          send(socket1,"Wrong input!\n",13,0);
          continue;
      }

      int temp = strtol(buffer,NULL,10);

      if (temp >= 0)
      {
         int fact = factor(temp);
         char fact1[512];
         memset(fact1,0,sizeof(fact1));
         sprintf(fact1," %d", fact);
         send(socket1,fact1,sizeof(fact1),0);
         send(socket1,"\n",1,0);
      }
      else send(socket1, "Wrong input!\n", 13, 0);
   }
   }
   default:
   close(socket1);
}
}
return 0;
}
