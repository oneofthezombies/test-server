//
// Created by hunhoekim on 2021/01/24.
//

#include "base/FileDescriptor.h"

#include <unistd.h>
#include <sys/socket.h>

#include "base/Result.h"

namespace ootz {

FileDescriptor::FileDescriptor(int32_t fd)
    : fd_(fd) {
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept
    : fd_(undefined) {
    moveFrom(std::move(other));
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    moveFrom(std::move(other));
    return *this;
}

FileDescriptor::~FileDescriptor() {
    clear();
}

void FileDescriptor::moveFrom(FileDescriptor&& other) noexcept {
    std::swap(fd_, other.fd_);
    other.clear();
}

void FileDescriptor::clear() {
    if (undefined != fd_) {
        const int32_t result = ::close(fd_);
        assert(-1 != result);
        fd_ = undefined;
    }
}

Result<FileDescriptor> FileDescriptor::socket(int32_t domain, int32_t type, int32_t protocol) {
    using ReturnType = Result<FileDescriptor>;
    const int32_t fd = ::socket(domain, type, protocol);
    return (-1 == fd) ? ReturnType(GET_LAST_ERROR()) : ReturnType(FileDescriptor(fd));
}

Result<FileDescriptor> FileDescriptor::accept(int32_t sockfd, struct sockaddr* address, socklen_t* addressSize) {
    using ReturnType = Result<FileDescriptor>;
    const int32_t fd = ::accept(sockfd, address, addressSize);
    return (-1 == fd) ? ReturnType(GET_LAST_ERROR()) : ReturnType(FileDescriptor(fd));
}

int32_t FileDescriptor::get() const {
    return fd_;
}

Result<ReadSizeType> FileDescriptor::read(void* buffer, size_t bufferSize) const {
    using ReturnType = Result<ReadSizeType>;
    const int32_t readSize = ::read(fd_, buffer, bufferSize);
    return (-1 == readSize) ? ReturnType(GET_LAST_ERROR()) : ReturnType(ReadSizeType(readSize));
}

Result<WriteSizeType> FileDescriptor::write(const void* buffer, size_t bufferSize) const {
    using ReturnType = Result<WriteSizeType>;
    const int32_t writeSize = ::write(fd_, buffer, bufferSize);
    return (-1 == writeSize) ? ReturnType(GET_LAST_ERROR()) : ReturnType(WriteSizeType(writeSize));
}

} // namnespace ootz