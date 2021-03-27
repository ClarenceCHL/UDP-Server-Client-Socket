// Author: Haolun Cheng

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
using namespace std;

int main(){
    // Create a socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        cerr << "Cannot create a socket" << endl;
        return 0;
    }

    // Identify the socket
    struct sockaddr_in serverHint;
    struct sockaddr_in client;
    socklen_t addrlen = sizeof(client);
    int recvLen;
    char buf[2048];

    memset((char*)&serverHint, 0, sizeof(serverHint));
    serverHint.sin_family = AF_INET;
    serverHint.sin_addr.s_addr = htonl(INADDR_ANY);
    serverHint.sin_port = htons(54000);

    if(bind(sock, (sockaddr*)&serverHint, sizeof(serverHint)) == -1){
        cerr << "Cannot bind" << endl;
        return 0;
    }

    // Receive messages on the server
    while(true){
        printf("Waiting on port 54000\n");
        recvLen = recvfrom(sock, buf, 2048, 0, (sockaddr*)&client, &addrlen);
        printf("Received %d bytes\n", recvLen);
        if(recvLen > 0){
            buf[recvLen] = 0;
            printf("received message: \"%s\"\n", buf);
        }
    }

    // Send a response back to the client
    sendto(sock, buf, 2048, 0, (sockaddr*)&client, addrlen);

    // Close the socket
    close(sock);
}