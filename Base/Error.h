//
//  error.h
//  test-server
//
//  Created by hunhoekim on 2021/01/23.
//

#ifndef error_h
#define error_h
#include <cerrno>

struct Error {
    Error(int32_t number,
          std::string&& message,
          std::string&& file,
          int32_t line);
    Error(Error&& other) noexcept;
    Error& operator=(Error&& other) noexcept;

    int32_t number;
    std::string message;
    std::string file;
    int32_t line;

    Error(const Error&) = delete;
    Error& operator=(const Error&) = delete;

private:
    void clear_();
    void moveFrom_(Error&& other) noexcept;
};

#define GET_LAST_ERROR() Error(errno, ::strerror(errno), __FILE__, __LINE__)
#define MAKE_ERROR(number, message) Error(number, message, __FILE__, __LINE__)

std::ostream& operator<<(std::ostream& ostream, const Error& error);

#endif /* error_h */
