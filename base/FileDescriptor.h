//
// Created by hunhoekim on 2021/01/24.
//

#ifndef FileDescriptor_h
#define FileDescriptor_h

#include <netinet/in.h>

#include "base/Result.h"

namespace ootz {

using ReadSizeType = int32_t;
using WriteSizeType = int32_t;

struct FileDescriptor {
    FileDescriptor(FileDescriptor&& other) noexcept;

    FileDescriptor& operator=(FileDescriptor&& other) noexcept;

    ~FileDescriptor();

    int32_t get() const;

    Result<ReadSizeType> read(void* buffer, size_t bufferSize) const;

    Result<WriteSizeType> write(const void* buffer, size_t bufferSize) const;

    static Result<FileDescriptor> socket(int32_t domain, int32_t type, int32_t protocol);

    static Result<FileDescriptor> accept(int32_t socketfd, struct sockaddr* address, socklen_t* addressSize);

    FileDescriptor(const FileDescriptor&) = delete;

    FileDescriptor& operator=(const FileDescriptor&) = delete;

private:
    explicit FileDescriptor(int32_t fd);

    void clear();

    void moveFrom(FileDescriptor&& other) noexcept;

    static constexpr int32_t undefined = -1;

    int32_t fd_;
};

} // namespace ootz

#endif // FileDescriptor_h
