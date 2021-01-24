//
// Created by hunhoekim on 2021/01/24.
//

#ifndef TEST_SERVER_FILEDESCRIPTOR_H
#define TEST_SERVER_FILEDESCRIPTOR_H

#include <unistd.h>
#include "Base/Result.hpp"

using BufferType = std::vector<uint8_t>;
template<int32_t size>
using FixedBufferType = std::array<uint8_t, size>;

struct FileDescriptor {
    FileDescriptor(FileDescriptor&& other) noexcept;
    FileDescriptor& operator=(FileDescriptor&& other) noexcept;
    ~FileDescriptor();

    [[nodiscard]]
    Result<BufferType> read() const;

    [[nodiscard]]
    Result<int32_t> write(const BufferType& buffer);

    [[nodiscard]]
    static
    Result<FileDescriptor> connect(const std::string& ip, int32_t port);

    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

private:
    static
    constexpr
    int32_t undefined = -1;

    explicit
    FileDescriptor(int32_t fileDescriptor);

    void clear_();
    void moveFrom_(FileDescriptor&& other) noexcept;

    int32_t fileDescriptor_;
};

#endif //TEST_SERVER_FILEDESCRIPTOR_H
