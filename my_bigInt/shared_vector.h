//
// Created by User on 31.05.2019.
//

#ifndef MY_BIGINT_SHARED_VECTOR_H
#define MY_BIGINT_SHARED_VECTOR_H

#include <algorithm>
#include <string>
#include <cstddef>
#include <cstring>
#include <vector>
#include "shared_ptr.h"

class shared_vector {
    static const uint32_t SMALL_SIZE = 3;

    size_t _size{};
    size_t cap{};

    uint32_t small_vec[SMALL_SIZE]{};
    Shared_pointer big_vec;

public:
    shared_vector() : _size(0), cap(0) {};

    explicit shared_vector(size_t size) : shared_vector(size, 0) {};

    shared_vector(size_t size, uint32_t val) : _size(size), cap(size <= SMALL_SIZE ? 0 : size * 2) {
        if (cap != 0) {
            big_vec.reset((uint32_t *) operator new[](cap * sizeof(uint32_t)));
            for (size_t i = 0; i < _size; i++) {
                big_vec[i] = val;
            }
        } else {
            for (size_t i = 0; i < size; i++) {
                small_vec[i] = val;
            }
        }
    }

    explicit shared_vector(std::vector<uint32_t> const &other) {
        shared_vector ans;
        for (unsigned int i : other) {
            ans.push_back(i);
        }
        (*this) = ans;
    }

    shared_vector(const shared_vector &other) : _size(other._size), cap(other.cap), big_vec(other.big_vec){
        if (other.cap == 0) {
            for (size_t i = 0; i <  other._size; i++) {
                small_vec[i] = other.small_vec[i];
            }
        }
    }

    ~shared_vector() = default;

    shared_vector &operator=(const shared_vector &other) {
        if (other.big_vec.get() == nullptr) {
            for (size_t i = 0; i <  other._size; i++) {
                small_vec[i] = other.small_vec[i];
            }
            big_vec.reset();
        } else {
            big_vec = other.big_vec;
        }
        _size = other._size;
        cap = other.cap;

        return *this;
    }

    uint32_t &operator[](size_t ind) {
        check();
        return (big_vec.get() == nullptr) ? small_vec[ind] : big_vec[ind];
    }

    const uint32_t &operator[](size_t ind) const {
        return (big_vec.get() == nullptr) ? small_vec[ind] : big_vec[ind];
    }

    void push_back (uint32_t elem) {
        check();
        if (big_vec.get() == nullptr && _size == SMALL_SIZE) {
            cap = _size * 2;
            big_vec.reset((uint32_t *) operator new[](cap * sizeof(uint32_t)));
            for (size_t i = 0; i < _size; i++) {
                big_vec[i] = small_vec[i];
            }
        }
        if (big_vec.get() == nullptr) {
            small_vec[_size++] = elem;
        } else {
            if (_size == cap) {
                cap *= 2;
                create_new();
            }
            big_vec[_size] = elem;
            _size++;
        }
    }

    void pop_back() {
        check();
        _size--;
    }

    uint32_t back() {
        return (*this)[_size-1];
    }

    uint32_t const  back() const {
        return (*this)[_size-1];
    }
    
    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    void create_new() {
        auto * new_big_vec = (uint32_t *)operator new[](cap * sizeof(uint32_t));
        for (size_t i = 0; i < _size; i++) {
            new_big_vec[i] = big_vec[i];
        }
        big_vec.reset(new_big_vec);
    }

    void check() {
        if (big_vec.get() != nullptr && !big_vec.unique()) {
            create_new();
        }
    }
};

#endif //MY_BIGINT_SHARED_VECTOR_H
