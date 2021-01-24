//
//  main.cpp
//  tcp-server
//
//  Created by hunhoekim on 2021/01/23.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Base/Error.h"

int main(int argc, const char* argv[]) {
    std::cout << "start tcp server\n";
    
    const int32_t port = 9000;
    const int32_t backlogSize = 10;
    
    const int32_t listenFileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenFileDescriptor) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }
    
    struct sockaddr_in serverInfo{};
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);
    serverInfo.sin_port = htons(port);
    if (0 != ::bind(listenFileDescriptor, reinterpret_cast<struct sockaddr*>(&serverInfo), sizeof(serverInfo))) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }
  
    if (-1 == ::listen(listenFileDescriptor, backlogSize)) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }
  
    while (true) {
        const int32_t connectFileDesciptor = ::accept(listenFileDescriptor, nullptr, nullptr);
        if (-1 == connectFileDesciptor) {
            std::cout << GET_LAST_ERROR() << std::endl;
            break;
        }

        FileDescriptor::open()
        constexpr int32_t bufferSize = 10000;
        char buffer[bufferSize]{};

        const int32_t numWrite = ::write(connectFileDesciptor, buffer, bufferSize);
        if (-1 == numWrite) {
            std::cout << GET_LAST_ERROR() << std::endl;
            break;
        }
        std::cout << "numWrite: " << numWrite << std::endl;
    }
    
    std::cout << "stop tcp server" << std::endl;
    return 0;
}
