//
//  main.cpp
//  tcp-server
//
//  Created by hunhoekim on 2021/01/23.
//

#include "base/FileDescriptor.h"
using namespace ootz;

int main(int argc, const char* argv[]) {
    std::cout << "start tcp server\n";
    
    const int32_t port = 9000;
    const int32_t backlogSize = 10;

    Result<FileDescriptor> socketResult = FileDescriptor::socket(AF_INET, SOCK_STREAM, 0);
    if (!socketResult.valid()) {
        std::cout << socketResult.error() << std::endl;
        return 1;
    }

    FileDescriptor serverfd = socketResult.data();

    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    if (0 != ::bind(serverfd.get(), reinterpret_cast<struct sockaddr*>(&address), sizeof(address))) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }
  
    if (-1 == ::listen(serverfd.get(), backlogSize)) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }

    for (int32_t i = 0; i < 10; ++i) {
        Result<FileDescriptor> acceptResult = FileDescriptor::accept(serverfd.get(), nullptr, nullptr);
        if (!acceptResult.valid()) {
            continue;
        }

        FileDescriptor clientfd = acceptResult.data();
    }
    
    std::cout << "stop tcp server" << std::endl;
    return 0;
}
