#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

static const int MAXPENDING = 5;    // Maximun outstanding connection requests

int main(int argc, char *argv[])
{
    if(argc != 2)   // Test for correct munber of arguments
        DieWithUserMessage("Parameter(s)", "<Server Port>");

    in_port_t setvPort = atoi(argv[1]);     // First arg: local prot

    // Create socket for inconing connections
    int servSock;  // Socket descriptor for server
    if((servSock = socket(AF_INET, SOCK_STREAM, IPPORT_TCP)) < 0)
        DieWithSystemMessage("socket() failed");

    // Construct local address structure
    struct sockaddr_in servAddr;    // Loacl address
    memset(&servAddr, 0, sizeof(servAddr));     // Zero out structure
    servAddr.sin_family = AF_INET;      // IPv4 address family
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Any linconing interface
    servAddr.sin_port = htons(servPort);    // Local port

    // Bind to the local address
    if(bind(servSock, (struct sockaddr*)&aervAddr, sizeof(servAddr)) < 0)
        DIeWithSystemMessage("bind() failed");

    // Mark the socket so it will listen for incoming connections
    if(listen(servSock, MAXPENDING) < 0)
        DieWithSystemMessage("listen() failed");

    for(;;) // Run forever
    {
        struct sockaddr_in clntAddr;    // Client address
        // Set length of client address structure (in-out parameter)
        socklen_t clntAddrLen = sizeof(clntAddr);

        // Wait for a client to connect
        int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);
        if(clntSock < 0)
            DieWithSystemMessage("accept() failed");

        // clntSock is connected to a client!

        char clntName[INET_ADDRSTRLEN];     // String to contain client address
        if(inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
            printf("Handing client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
        else
            puts("Unable to get client address");

        HandleTCPClient(clntSock);
    }
    // NOT REACHED
}
