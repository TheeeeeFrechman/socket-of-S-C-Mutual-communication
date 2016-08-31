#include "Comme.h"
int main()
{
	int Init_server;
	int RecvSend_server;
	Init_server = init_server_socket();
	if(Init_server < 0)
	{
		printf("Init server is fail\n");
		return -1;
	}
	RecvSend_server = server_RecvSend(Init_server);
	if(RecvSend_server < 0)
	{
		printf("recv or send is wrong\n");
		return -1;
	}
	return 0;
}
int init_server_socket(void)
{
	int sockfd;
    	struct sockaddr_in s_addr;
    	unsigned int listnum;

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        return -1;
    }else
        printf("socket create success!\n");
    memset(&s_addr,0,sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);
if((bind(sockfd, (struct sockaddr*) &s_addr,sizeof(struct sockaddr))) == -1)
	{
        	perror("bind");
        	return -1;
    	}else
        	printf("bind success!\n");
    if(listen(sockfd,listnum) == -1)
	{
        	perror("listen");
        	return -1;
    	}else
        	printf("the server is listening!\n");
	return sockfd;

}
int server_RecvSend(int sockfd)
{
	int newfd;
	struct sockaddr_in c_addr;
	while(1){
        printf("*****************run the server***************\n");
        len = sizeof(struct sockaddr);
        if((newfd = accept(sockfd,(struct sockaddr*) &c_addr, &len)) == -1)
		{
            		perror("accept");
            		exit(errno);
        	}else
            printf("the client is ：%s: %d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
	 while(1){
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            maxfd = 0;
            FD_SET(newfd, &rfds);
            if(maxfd < newfd)
                maxfd = newfd;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
            if(retval == -1){
                printf("select is wrong!\n");
                break;
            }else if(retval == 0){
                printf("waiting...\n");
                continue;
		}else{
                if(FD_ISSET(0, &rfds)){

                    memset(buf,0,sizeof(buf));
                    fgets(buf,BUFLEN,stdin);
                    if(!strncasecmp(buf,"quit",4)){
                        printf("server is wrong\n");
                        break;
                    }
                        //len = send(newfd,buf,strlen(buf),0);
                        len = send_fun(newfd,buf,strlen(buf),0);
                    if(len > 0)
			{
                        printf("\tthe message：%s\n",buf);
			}
                    else{
                        printf("message is wrong!\n");
                        break;
                    }
                }
		 if(FD_ISSET(newfd, &rfds))
			{
                    		memset(buf,0,sizeof(buf));
                    		//len = recv(newfd,buf,BUFLEN,0);
                    		len = recv_fun(newfd,buf,BUFLEN,0);
                    		if(len > 0)
                        	printf("client message：%s\n",buf);
                    else
			{
                        if(len < 0 )
                            printf("message is wrong！\n");
                        else
                            printf("client is quit！\n");
                        break;
                    }
                }
            }
                }
        close(newfd);
        printf("do you want quit：y；n? ");
        bzero(buf, BUFLEN);
        fgets(buf,BUFLEN, stdin);
        if(!strncasecmp(buf,"y",1))
		{
            		printf("server quit!\n");
            		break;
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
