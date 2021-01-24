//
// Created by hunhoekim on 2021/01/24.
//

#include "FileDescriptor.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Base/Result.hpp"

FileDescriptor::FileDescriptor(int32_t fileDescriptor)
    : fileDescriptor_(fileDescriptor) {
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept
    : fileDescriptor_(undefined) {
    moveFrom_(std::move(other));
}

FileDescriptor &FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    moveFrom_(std::move(other));
    return *this;
}

FileDescriptor::~FileDescriptor() {
    clear_();
}

Result<FileDescriptor> FileDescriptor::connect(const std::string& ip, int32_t port) {
    using ReturnType = Result<FileDescriptor>;

    if (0 > port) {
        return ReturnType(MAKE_ERROR(1, "port is negative number."));
    }

    const int32_t serverFileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == serverFileDescriptor) {
        return ReturnType(GET_LAST_ERROR());
    }

    struct sockaddr_in serverInfo{};
    if (1 != inet_pton(AF_INET, ip.c_str(), &serverInfo.sin_addr)) {
        return ReturnType(GET_LAST_ERROR());
    }

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    if (-1 == ::connect(serverFileDescriptor, reinterpret_cast<struct sockaddr*>(&serverInfo), sizeof(serverInfo))) {
        return ReturnType(GET_LAST_ERROR());
    }

    return ReturnType(std::move(FileDescriptor(serverFileDescriptor)));
}

Result<BufferType> FileDescriptor::read() const {
    using ReturnType = Result<BufferType>;

    BufferType data{};
    FixedBufferType<1024 * 4> buffer{};
    while (true) {
        const int32_t numRead = ::read(fileDescriptor_, buffer.data(), buffer.size());
        std::cout << "numRead: " << numRead << std::endl;

        if (-1 == numRead) {
            return ReturnType(GET_LAST_ERROR());
        }

        const int32_t sizeBefore = data.size();
        data.resize(sizeBefore + numRead);
        std::move(buffer.begin(), buffer.end(), data.begin() + sizeBefore);
        std::cout << "data size: " << data.size() << std::endl;

        if (buffer.size() > numRead) {
            return ReturnType(std::move(data));
        }
    }
}

void FileDescriptor::moveFrom_(FileDescriptor&& other) noexcept {
    std::swap(fileDescriptor_, other.fileDescriptor_);
    other.clear_();
}

void FileDescriptor::clear_() {
    if (undefined != fileDescriptor_) {
        const int32_t result = ::close(fileDescriptor_);
        assert(-1 != result);
        fileDescriptor_ = undefined;
    }
}

Result<int32_t> FileDescriptor::write(const BufferType& buffer) {
    using ReturnType = Result<int32_t>;

    int32_t numWrite = ::write(fileDescriptor_, buffer.data(), buffer.size());
    if (-1 == numWrite) {
        return ReturnType(GET_LAST_ERROR());
    }

    return ReturnType(std::move(numWrite));
}
