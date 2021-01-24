//
// Created by hunhoekim on 2021/01/24.
//

#ifndef Error_h
#define Error_h

#include <cerrno>

namespace ootz {

struct Error {
    Error(int32_t number, std::string&& message, std::string&& file, int32_t line);

    Error(Error&& other) noexcept;

    Error& operator=(Error&& other) noexcept;

    Error(const Error&) = delete;

    Error& operator=(const Error&) = delete;

    int32_t number;
    std::string message;
    std::string file;
    int32_t line;

private:
    void clear();

    void moveFrom(Error&& other) noexcept;
};

#define GET_LAST_ERROR() Error(errno, ::strerror(errno), __FILE__, __LINE__)
#define MAKE_ERROR(number, message) Error(number, message, __FILE__, __LINE__)

}

namespace std {

ostream& operator<<(ostream& ostream, const ootz::Error& error);

} // namespace std

#endif // Error_h
