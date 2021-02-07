//
// Created by hunhoekim on 2021/01/24.
//

#include "base/Precompile.h"

#include <arpa/inet.h>

#include "base/FileDescriptor.h"
using namespace ootz;

int main(int argc, const char* argv[]) {
    std::cout << "start tcp client" << std::endl;

    const std::string ip = "127.0.0.1";
    const int32_t port = 9000;

    Result<FileDescriptor> socketResult = FileDescriptor::socket(AF_INET, SOCK_STREAM, 0);
    if (!socketResult.valid()) {
        std::cout << socketResult.error() << std::endl;
        return 1;
    }

    FileDescriptor serverfd = socketResult.data();

    struct sockaddr_in address{};
    if (1 != ::inet_pton(AF_INET, ip.c_str(), &address.sin_addr)) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (-1 == ::connect(serverfd.get(), reinterpret_cast<struct sockaddr*>(&address), sizeof(address))) {
        std::cout << GET_LAST_ERROR() << std::endl;
        return 1;
    }

    {
        constexpr int32_t bufferSize = 1024;
        char buffer[bufferSize]{};
        ::sprintf(buffer, "i am tcp client.");
        Result<WriteSizeType> writeResult = serverfd.write(buffer,bufferSize);
        if (!writeResult.valid()) {
            std::cout << GET_LAST_ERROR() << std::endl;
            return 1;
        }
    }

    {
        constexpr int32_t bufferSize = 1024;
        char buffer[bufferSize]{};
        Result<ReadSizeType> readResult = serverfd.read(buffer, bufferSize);
        if (!readResult.valid()) {
            std::cout << GET_LAST_ERROR() << std::endl;
            return 1;
        }

        std::cout << std::string(buffer) << std::endl;
    }

    std::cout << "stop tcp client" << std::endl;
    return 0;
}
