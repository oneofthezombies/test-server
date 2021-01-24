//
//  main.cpp
//  tcp-client
//
//  Created by hunhoekim on 2021/01/23.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Base/FileDescriptor.h"

int main(int argc, const char* argv[]) {
    std::cout << "start tcp client\n";

    const std::string ip = "127.0.0.1";
    const int32_t port = 9000;

    Result<FileDescriptor> connectionResult = FileDescriptor::connect(ip, port);
    if (!connectionResult.valid()) {
        std::cout << connectionResult.error() << std::endl;
        return 1;
    }

    const FileDescriptor& connection = connectionResult.data();
    Result<std::vector<uint8_t>> readResult = connection.read();
    if (!readResult.valid()) {
        std::cout << readResult.error() << std::endl;
        return 1;
    }

    const std::vector<uint8_t>& read = readResult.data();
    std::cout << read.size() << std::endl;
    std::string readString(read.begin(), read.end());
    readString.append("\0");
    std::cout << readString << std::endl;

    std::cout << "stop tcp client" << std::endl;
    return 0;
}
