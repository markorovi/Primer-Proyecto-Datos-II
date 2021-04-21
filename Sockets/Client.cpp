//
// Created by marco on 4/20/21.
//

#include "Client.h"


void Client::Initialize() {
    this->hint.sin_family = AF_INET;
    this->hint.sin_port = htons(this->port);
    inet_pton(AF_INET, this->ipAddress.c_str(), &this->hint.sin_addr);

    int connectRes = connect(this->sock, (sockaddr*)&this->hint, sizeof(this->hint));
}


void Client::Start() {
    while (true){
        std::cout << "> ";
        getline(std::cin, this->userInput);

//		Send to server
        int sendRes = send(this->sock, this->userInput.c_str(), this->userInput.size() + 1, 0);


//		Wait for response
        memset(this->buf, 0, 4096);
        int bytesReceived = recv(this->sock, this->buf, 4096, 0);

//		Display response
        std::cout << "SERVER> " << std::string(this->buf, bytesReceived) << "\r\n";

    }
    close(this->sock);
}
