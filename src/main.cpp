#include <iostream>
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "DynamicArray.hpp"

int main() {
    UniquePtr<int> UniquePtr(new int(42));
    std::cout << "UniquePtr: " << *UniquePtr << "\n";

    SharedPtr<int> SharedPtr1(new int(10));
    SharedPtr<int> SharedPtr2 = SharedPtr1;
    std::cout << "SharedPtr UseCount: " << SharedPtr1.UseCount() << "\n";

    DynamicArray<int> a(3);
    a[0]=1; a[1]=2; a[2]=3;
    std::cout << "DynamicArray: " << a[0] << " " << a[1] << " " << a[2] << "\n";
    return 0;

}


