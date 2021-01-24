//
// Created by hunhoekim on 2021/01/24.
//

#ifndef Result_h
#define Result_h

#include "base/Error.h"

namespace ootz {

template<typename DataType>
struct Result {
    explicit Result(DataType&& data);

    explicit Result(Error&& error);

    bool valid() const;

    DataType&& data();

    const DataType& data() const;

    Error&& error();

    const Error& error() const;

    Result(const Result&) = delete;

    Result& operator=(const Result&) = delete;

private:
    std::variant<DataType, Error> data_;
};

template<typename DataType>
Result<DataType>::Result(DataType&& data)
    : data_(std::forward<DataType>(data)) {
}

template<typename DataType>
Result<DataType>::Result(Error&& error)
    : data_(std::move(error)) {
}

template<typename DataType>
bool Result<DataType>::valid() const {
    return nullptr != std::get_if<DataType>(&data_);
}

template<typename DataType>
const DataType& Result<DataType>::data() const {
    return *std::get_if<DataType>(&data_);
}

template<typename DataType>
const Error& Result<DataType>::error() const {
    return *std::get_if<Error>(&data_);
}

template<typename DataType>
DataType&& Result<DataType>::data() {
    return std::move(*std::get_if<DataType>(&data_));
}

template<typename DataType>
Error&& Result<DataType>::error() {
    return std::move(*std::get_if<Error>(&data_));
}

} // namespace ootz

#endif // Result_h
