//
//  main.cpp
//  test
//
//  Created by hunhoekim on 2021/01/23.
//

#include <iostream>
using namespace std;

#include "Base/Error.h"

int main(int argc, const char * argv[]) {
    cout << "start test\n";
    
//    cout << sizeof(int) << '\n';
//    cout << sizeof(long) << '\n';
//    cout << sizeof(int32_t) << '\n';
//    cout << sizeof(int64_t) << '\n';
//    cout << sizeof(size_t) << '\n';
//    cout << sizeof(errno) << '\n';

    std::string a((std::stringstream("fdsa") << 1).str());
    cout << "stop test" << endl;
    return 0;
}
