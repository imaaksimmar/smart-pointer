#pragma once 
#include <cstddef>

template <typename T>
class SharedPtr {
    private:
        T* ptr;
        size_t* count;

    public:
        SharedPtr() : ptr(nullptr), count(nullptr) {}

        explicit SharedPtr(T* ptr) : ptr(ptr) {
            if(ptr!=nullptr) {
                count = new size_t(1);
            } 
            else { count = nullptr; }
        }

        ~SharedPtr() {
            if(count!=nullptr) {
                size_t c = --(*count);
                if(c==0) {
                    delete ptr;
                    delete count;
                }
            }
        }

        SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
            if(count!=nullptr) {
                ++(*count);
            }
        }

        SharedPtr& operator=(const SharedPtr& other) {
           if(this!=&other) {
                if(count!=nullptr) {
                    size_t c = --(*count);
                    if(c==0) {
                        delete ptr;
                        delete count;
                    }
                }
                ptr = other.ptr;
                count = other.count;
                if(count!=nullptr) {
                    ++(*count);
                }
            }
            return *this;
        } 

        SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
            other.ptr = nullptr;
            other.count = nullptr;
        }
        SharedPtr& operator=(SharedPtr&& other) noexcept {
            if(this!=&other) {
                if(count!=nullptr) {
                    size_t c = --(*count);
                    if(c==0) {
                        delete ptr;
                        delete count;
                    }
                }
                ptr = other.ptr;
                count = other.count;
                other.ptr = nullptr;
                other.count = nullptr;
            }
            return *this;
        }

        T& operator*() { return *ptr; }
        T* operator->() { return ptr; }

        const T& operator*() const { return *ptr; }
        const T* operator->() const { return ptr; }

        size_t UseCount() const { 
            if(count!=nullptr) { return *count; }
            else { return 0; }
        }     
};



template <typename T>
class SharedPtr<T[]> {
    private:
        T* ptr;
        size_t* count;

    public:
        SharedPtr() : ptr(nullptr), count(nullptr) {}
        explicit SharedPtr(T* p) : ptr(p) {
            if(p!=nullptr) {
                count = new size_t(1);
            } 
            else { count = nullptr; }
        }

        ~SharedPtr() {
            if(count!=nullptr) {
                size_t c = --(*count);
                if(c==0) {
                    delete[] ptr; 
                    delete count; 
                }
            }
        }

        SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
            if(count!=nullptr) {
                ++(*count);
            }
        }
        SharedPtr& operator=(const SharedPtr& other) {
           if(this!=&other) {
                if(count!=nullptr) {
                    size_t c = --(*count);
                    if(c==0) {
                        delete[] ptr; 
                        delete count;
                    }
                }
                ptr = other.ptr;
                count = other.count;
                if(count!=nullptr) {
                    ++(*count);
                }
            }
            return *this;
        } 

        SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
            other.ptr = nullptr;
            other.count = nullptr;
        }
        SharedPtr& operator=(SharedPtr&& other) noexcept {
            if(this!=&other) {
                if(count!=nullptr) {
                    size_t c = --(*count);
                    if(c==0) {
                        delete[] ptr;
                        delete count;
                    }
                }
                ptr = other.ptr;
                count = other.count;
                other.ptr = nullptr;
                other.count = nullptr;
            }
            return *this;
        }

        T& operator[](size_t index) { 
            return ptr[index]; 
        }
        
        const T& operator[](size_t index) const { 
            return ptr[index]; 
        }

};
