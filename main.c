#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#include <windows.h>
#include <io.h>


void main(int argc, char *argv[])
{
    int trueval = 1;

    long ii, 
	 status;

    SOCKET sockfd;

    WSADATA wsaData;

    WSAStartup(2, &wsaData);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        fprintf(stderr, "socket: %d\n", WSAGetLastError( ));
        exit(1);
    }

    SetHandleInformation((HANDLE) sockfd, HANDLE_FLAG_INHERIT, 0);

    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
			(const char *) &trueval, sizeof trueval))
    {
        fprintf(stderr, "setsockopt: %d\n", WSAGetLastError( ));
        exit(1);
    }

    ii = 0;

    while (1)
    {
        LPWSAPROTOCOL_INFO lpProtocolInfo = NULL;

        status = WSADuplicateSocket(sockfd, 
			            9898, 
				    lpProtocolInfo);
        if (status != 0)
        {
            fprintf(stderr, "WSADuplicateSocket: %d\n", WSAGetLastError( ));
            exit(1);
        }
   
        printf("%06d  Orig FD: %d\n", ii++, sockfd);
    }

    exit(0);
}
