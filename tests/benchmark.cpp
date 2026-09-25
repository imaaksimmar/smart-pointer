#include <chrono>
#include <iostream>
#include "../include/UniquePtr.hpp"
#include "../include/SharedPtr.hpp"

using namespace std::chrono;
long long sink = 0;

int main() {
    const size_t n = 1000000;
    long long sum = 0;
   
    auto t0 = high_resolution_clock::now(); 
    int** raw = new int*[n];
    for(size_t i=0; i<n; i++) raw[i] = new int(static_cast<int>(i));
    
    auto t1 = high_resolution_clock::now(); 
    for(size_t i=0; i<n; i++) sum += *raw[i];
    
    auto t2 = high_resolution_clock::now(); 
    for(size_t i=0; i<n; i++) delete raw[i]; 
    delete[] raw;
    auto t3 = high_resolution_clock::now();
    
    std::cout << "Raw:    " 
              << duration<double, std::milli>(t1-t0).count() << " ms (создание) | "
              << duration<double, std::milli>(t2-t1).count() << " ms (чтение) | "
              << duration<double, std::milli>(t3-t2).count() << " ms (удаление)\n";


    t0 = high_resolution_clock::now();
    UniquePtr<int>* uniq = new UniquePtr<int>[n];
    for(size_t i=0; i<n; i++) uniq[i] = UniquePtr<int>(new int(static_cast<int>(i)));
    
    t1 = high_resolution_clock::now();
    for(size_t i=0; i<n; i++) sum += *uniq[i];
    
    t2 = high_resolution_clock::now();
    delete[] uniq; 
    t3 = high_resolution_clock::now();
    
    std::cout << "Unique: " 
              << duration<double, std::milli>(t1-t0).count() << " ms (создание) | "
              << duration<double, std::milli>(t2-t1).count() << " ms (чтение) | "
              << duration<double, std::milli>(t3-t2).count() << " ms (удаление)\n";


    t0 = high_resolution_clock::now();
    SharedPtr<int>* shrd = new SharedPtr<int>[n];
    for(size_t i=0; i<n; i++) shrd[i] = SharedPtr<int>(new int(static_cast<int>(i)));
    
    t1 = high_resolution_clock::now();
    for(size_t i=0; i<n; i++) sum += *shrd[i];
    
    t2 = high_resolution_clock::now();
    delete[] shrd; 
    t3 = high_resolution_clock::now();
    
    std::cout << "Shared: " 
              << duration<double, std::milli>(t1-t0).count() << " ms (создание) | "
              << duration<double, std::milli>(t2-t1).count() << " ms (чтение) | "
              << duration<double, std::milli>(t3-t2).count() << " ms (удаление)\n";

    sink = sum;
    return 0;
}
