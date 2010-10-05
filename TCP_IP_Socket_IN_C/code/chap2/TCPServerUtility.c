void HanfleTCPClient(int clntSocket)
{
    char buffer[BUFSIZE];   // Buffer for echo string

    // Receive message from client
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if(numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed");

    // Send received steing and receive again until end of stream
    while(numBytesRcvd > 0) // 0 indicates end of stream
    {
        // Echo message back to client
        ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
        if(numBytesSent < 0)
            DieWithSystemMessage("send() failed");
        else if(numBytesSent != numBytesRcvd)
            DieWithUserMessage("send()", "send unexpected number of bytes");

        // See if there is more data to rective
        numBytesRcvd = recv(clntSocket, buffer, BUFZIE, 0);
        if(numBytesRcvd < 0)
            DieWithSystemMessage("recv() failed");
    }

    close(clntSocket);  // Close client socket
}
