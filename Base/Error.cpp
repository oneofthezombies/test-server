//
//  error.cpp
//  test-server
//
//  Created by hunhoekim on 2021/01/23.
//

#include "Error.h"

Error::Error(int32_t number,
             std::string&& message,
             std::string&& file,
             int32_t line)
    : number(number),
    message(std::move(message)),
    file(std::move(file)),
    line(line) {
}

Error::Error(Error&& other) noexcept
    : number(0),
    line(0) {
    moveFrom_(std::move(other));
}

Error& Error::operator=(Error&& other) noexcept {
    moveFrom_(std::move(other));
    return *this;
}

void Error::clear_() {
    number = 0;
    line = 0;
    message.clear();
    file.clear();
}

void Error::moveFrom_(Error&& other) noexcept {
    std::swap(number, other.number);
    std::swap(message, other.message);
    std::swap(file, other.file);
    std::swap(line, other.line);
    other.clear_();
}

std::ostream& operator<<(std::ostream& ostream, const Error& error) {
    ostream << "Error"
            << " "
            << "number: [" << error.number << "]"
            << " "
            << "message: [" << error.message << "]"
            << " "
            << "file: [" << error.file << "]"
            << " "
            << "line: [" << error.line << "]";
    return ostream;
}
