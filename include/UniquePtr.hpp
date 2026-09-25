#pragma once 
#include <cstddef>

template <typename T>
class UniquePtr {
    private:
        T* ptr;
        
    public:
        UniquePtr() : ptr(nullptr) {} 
        explicit UniquePtr(T* ptr) : ptr(ptr) {}
    
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other) = delete;

        UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }
        UniquePtr& operator=(UniquePtr&& other) noexcept {
            if(this!=&other) {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        ~UniquePtr() { delete ptr; }

        T& operator*() { return *ptr; }
        T* operator->() { return ptr; }
        T* Get() { return ptr; }

        const T& operator*() const { return *ptr; }
        const T* operator->() const { return ptr; }
        const T* Get() const { return ptr; }

};


template <typename T>
class UniquePtr<T[]> {
    private:
        T* ptr;

    public:
        UniquePtr() : ptr(nullptr) {}
        explicit UniquePtr(T* ptr) : ptr(ptr) {}
    
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other) = delete;

        UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }
        UniquePtr& operator=(UniquePtr&& other) noexcept {
            if (this != &other) {
                delete[] ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        ~UniquePtr() { delete[] ptr; }

        T& operator[](size_t index) { return ptr[index]; }
        T Get(size_t index) { return ptr[index]; }

        const T& operator[](size_t index) const { return ptr[index]; }
        const T Get(size_t index) const { return ptr[index]; }
};

