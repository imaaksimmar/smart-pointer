#pragma once
#include <stdexcept>
#include <utility>
#include "UniquePtr.hpp"

template <typename T>
class DynamicArray {
private:
    UniquePtr<T[]> data;
    size_t size;

public:
    DynamicArray() : data(nullptr), size(0) {}
    explicit DynamicArray(size_t size) : data(nullptr), size(size) {
        if(size>0) { data = UniquePtr<T[]>(new T[size]()); } 
    }

    DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
        if(size>0) {
            data = UniquePtr<T[]>(new T[size]);
        }
        for(size_t i=0;i<size; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if(this!=&other) {
            UniquePtr<T[]> newData(nullptr);
            if(other.size>0) {
                newData = UniquePtr<T[]>(new T[other.size]);
            }
            for(size_t i=0; i<other.size; ++i) {
                newData[i] = other.data[i];
            }
            data = std::move(newData);
            size = other.size;
        }
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept 
        : data(std::move(other.data)), size(other.size) { 
        other.size = 0;
    }
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if(this!=&other) {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        if(index>=size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    const T& operator[](size_t index) const {
        if(index>=size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t GetSize() const { return size; }

    void Resize(size_t newSize) {
        if(newSize==size) { return; }

        UniquePtr<T[]> newData(nullptr);
        if(newSize>0) {
            newData = UniquePtr<T[]>(new T[newSize]());
        }
        size_t copyCount;
        if(newSize<size) {
            copyCount = newSize;
        } 
        else { copyCount = size; }
        for(size_t i=0; i<copyCount; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        size = newSize;
    }
};