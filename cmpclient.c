#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

int main(int argc,char* argv[])
{
  struct sockaddr_in servaddr;
  int sockfd;
  int retval = 0;
  char buf[1024];
  const char src[] = "i love jen!";
  strncpy(buf,"i love jen",1024);
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
  {
    printf("socket error!\n");
    return 1;
  }
  bzero(&servaddr,sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(7829);
  retval = inet_pton(AF_INET,"192.168.100.128",&servaddr.sin_addr);
  if(retval <= 0)
  {
    printf("inet_pton error!\n");
  }

  retval = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  
  if(retval < 0)
  {
    printf("connect error!\n");
  }

  retval = write(sockfd,buf,strnlen(buf,1024));
  shutdown(sockfd,SHUT_RDWR); 
  return 0;
}
