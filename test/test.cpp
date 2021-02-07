//
//  test.cpp
//  test
//
//  Created by hunhoekim on 2021/01/23.
//

#include "base/Precompile.h"

#include "base/Error.h"

int main(int argc, const char * argv[]) {
    std::cout << "start test" << std::endl;
    
//    cout << sizeof(int) << '\n';
//    cout << sizeof(long) << '\n';
//    cout << sizeof(int32_t) << '\n';
//    cout << sizeof(int64_t) << '\n';
//    cout << sizeof(size_t) << '\n';
//    cout << sizeof(errno) << '\n';

    std::string a((std::stringstream("fdsa") << 1).str());
    std::cout << "stop test" << std::endl;
    return 0;
}
