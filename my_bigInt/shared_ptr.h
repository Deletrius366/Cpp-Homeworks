#include <cstddef>
#include <stdint-gcc.h>

struct Shared_pointer {
    struct Shared {
        uint32_t *_ptr;
        uint32_t _cnt;

        explicit Shared(uint32_t *ptr) {
            _ptr = ptr;
            _cnt = 1;
        }

        ~Shared() {
            operator delete[](_ptr);
        }
    };

    explicit Shared_pointer(uint32_t *ptr = nullptr) {
        if (ptr == 0) {
            shared = nullptr;
        } else {
            shared = new Shared(ptr);
        }
    }

    ~Shared_pointer() {
        if (shared != nullptr) {
            dec_cnt();
        }
    }

    Shared_pointer(const Shared_pointer &a) {
        if (a.shared == nullptr) {
            shared = nullptr;
        } else {
            shared = a.shared;
            ++shared->_cnt;
        }
    }

    Shared_pointer &operator=(const Shared_pointer &a) {
        if (shared != nullptr && a.shared != nullptr && shared == a.shared) {
            return *this;
        }
        if (shared != nullptr) {
            dec_cnt();
        }
        if (a.shared == nullptr) {
            shared = nullptr;
        } else {
            shared = a.shared;
            ++shared->_cnt;
        }

        return *this;
    }

    uint32_t *get() const {
        return (shared == nullptr) ? nullptr : shared->_ptr;
    }

    void reset(uint32_t *ptr = nullptr) {
        if (shared != nullptr) {
            dec_cnt();
        }
        if (ptr == nullptr) {
            shared = nullptr;
        } else {
            shared = new Shared(ptr);
        }
    }

    uint32_t &operator*() const {
        return *(shared->_ptr);
    }

//    uint32_t *operator->() const {
//        return (shared == nullptr) ? nullptr : shared->_ptr;
//    }

    uint32_t &operator[](size_t i) {
        return shared->_ptr[i];
    }

    const uint32_t &operator[](size_t i) const {
        return shared->_ptr[i];
    }

    void dec_cnt() {
        if (--shared->_cnt == 0) {
            delete(shared);
        }
    }

    bool unique() {
        return shared->_ptr != nullptr && shared->_cnt == 1;
    }

private:
    Shared *shared;
};
