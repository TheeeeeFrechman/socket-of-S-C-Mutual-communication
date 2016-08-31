#include "Comme.h"
int main(int argc, char **argv)
{
	int Init_client;
	int RecvSend_client;
	int sockfd;
	Init_client = init_client_socket(sockfd,argc,argv);
	if(Init_client < 0)
	{
		printf("Init client is fail\n");
		return -1;
	}
	RecvSend_client = client_RecvSend(Init_client);
	if(RecvSend_client < 0)
	{
		printf("recv or send is fail\n");
		return -1;
	}
	return 0;
		
}
int init_client_socket(int sockfd,int argc, char **argv)
{
    	struct sockaddr_in s_addr;

    	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        	{
                	perror("socket");
                	return -1;
        	}else
        	printf("socket create success!\n");

    		memset(&s_addr,0,sizeof(s_addr));
    		s_addr.sin_family = AF_INET;
     		s_addr.sin_port = htons(PORT);
    		if (inet_aton(argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr) == 0)
	 		{
               	 		perror(argv[1]);
                		return -1;
        		}
    		if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) == -1)
        		{
                		perror("connect");
                		return -1;
        		}else
        			printf("conncet success!\n");
				return sockfd;	
}
int client_RecvSend(int sockfd)
{
	while(1)
        {
                FD_ZERO(&rfds);
                FD_SET(0, &rfds);
                maxfd = 0;
                FD_SET(sockfd, &rfds);
                if(maxfd < sockfd)
                maxfd = sockfd;
                tv.tv_sec = 10;
                tv.tv_usec = 0;
                retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
                if(retval == -1)
        {
            printf("select wrong,client quit.\n");
            break;
        }else if(retval == 0)
                {
                printf("waiting...\n");
                continue;
                }else
                        {
		if(FD_ISSET(sockfd,&rfds))
                        {
                        bzero(buf,BUFLEN);
                        //len = recv(sockfd,buf,BUFLEN,0);
                        len = recv_fun(sockfd,buf,BUFLEN,0);
                if(len > 0)
                        {
                    printf("server message：%s\n",buf);
                        }
                else{
                    if(len < 0 )
                        printf("message fail to recv！\n");
                    else
                        printf("server quit！\n");
                break;
                }
            }
            if(FD_ISSET(0, &rfds))
                {
                        bzero(buf,BUFLEN);
                        fgets(buf,BUFLEN,stdin);
		 if(!strncasecmp(buf,"quit",4))
                        {
                                printf("client quit!\n");
                                break;
                        }
                    //len = send(sockfd,buf,strlen(buf),0);
                    len = send_fun(sockfd,buf,strlen(buf),0);
                if(len > 0)
                    printf("\tmessage：%s\n",buf);
                else{
                    printf("message!\n");
                    break;
                }
            }
        }

    }
	close(sockfd);
	return 0;
}
int recv_fun(int connfd,char *buffer,int bufferLength, int option)
{
        int value_max = 1;
        int ReBytes = 0;
        do
                {       
                        if ((value_max= recv(connfd, (buffer + ReBytes), bufferLength, option)) == 0)
                        {
                                printf("client closed.\n");
                                close(connfd);
                                return -1;
                        }
                        else
                        {
                                if (value_max != ReBytes)
                                {
                                        ReBytes += value_max;
                                        continue;
                                }
                        }
                }while (value_max != ReBytes);
                
                buffer[value_max] = '\0';
        return value_max;
}
int send_fun(int connfd,char *buffer,int bufferLength,int option)
{
        int returnvalus = 0;
        int The_max = 0;
        while(bufferLength > The_max)
        {
        returnvalus = send(connfd, buffer, bufferLength, option);
        The_max += returnvalus;
        if(returnvalus < 0)
                {
                printf("server send fail! \n");
                return -1;
                }
        }
        return 1;
}

