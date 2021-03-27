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
    char const *hello = "This is Haolun Cheng!";
    // Create a hint structure for the server
    sockaddr_in serverHint;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(54000);
    serverHint.sin_addr.s_addr = htonl(INADDR_ANY);

    // Socket creation
    int sockClient = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockClient == -1){
        cerr << "failed to create socket" << endl;
    }

    // Write out that socket
    int sendUDP = sendto(sockClient, hello, strlen(hello), 0, (sockaddr*)&serverHint, sizeof(serverHint));

    if(sendUDP == -1){
        cout << "That did not work!" << endl;
    }

    // Close the socket
    close(sockClient);

    return 0;
}