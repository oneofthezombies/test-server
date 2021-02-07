//
// Created by hunhoekim on 2021/01/24.
//

#include "base/Precompile.h"

#include "base/Error.h"

namespace ootz {

Error::Error(int32_t number, std::string&& message, std::string&& file, int32_t line)
    : number(number), message(std::move(message)), file(std::move(file)), line(line) {
}

Error::Error(Error&& other) noexcept
    : number(0), line(0) {
    moveFrom(std::move(other));
}

Error& Error::operator=(Error&& other) noexcept {
    moveFrom(std::move(other));
    return *this;
}

void Error::clear() {
    number = 0;
    line = 0;
    message.clear();
    file.clear();
}

void Error::moveFrom(Error&& other) noexcept {
    std::swap(number, other.number);
    std::swap(message, other.message);
    std::swap(file, other.file);
    std::swap(line, other.line);
    other.clear();
}

} // namespace ootz

namespace std {

ostream& operator<<(ostream& ostream, const ootz::Error& error) {
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

} // namespace std