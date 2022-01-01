// Copyright 2021 GNDavydov

#ifndef SHAREDPTR_SHARED_PTR_HPP_
#define SHAREDPTR_SHARED_PTR_HPP_

#include <atomic>
#include <utility>

template <typename T>
class SharedPtr {
private:
    std::atomic_uint* counter_;
    T* data_;

public:
    SharedPtr() noexcept : counter_(nullptr), data_(nullptr) {}

    explicit SharedPtr(T* ptr) noexcept : counter_(nullptr), data_(ptr) {
        if (data_) {
            counter_ = new std::atomic_uint(1);
        }
    }

    SharedPtr(const SharedPtr& copy) noexcept
            : counter_(copy.counter_), data_(copy.data_) {
        if (data_ != nullptr) {
            ++(*counter_);
        }
    }

    SharedPtr(SharedPtr&& move) noexcept
            : counter_(move.counter_), data_(move.data_) {
        move.counter_ = nullptr;
        move.data_ = nullptr;
    }

    ~SharedPtr() noexcept {
        if (counter_ != nullptr) {
            --(*counter_);
            if (*counter_ == 0) {
                delete counter_;
                delete data_;
            }
        }
    }

    auto operator=(const SharedPtr& copy) noexcept -> SharedPtr& {
        if (&copy == this) {
            return *this;
        }

        if (counter_ != nullptr) {
            --(*counter_);
            if (*counter_ == 0) {
                delete counter_;
                delete data_;
            }
        }

        counter_ = copy.counter_;
        data_ = copy.data_;
        if (data_ != nullptr) {
            ++(*counter_);
        }

        return *this;
    }

    auto operator=(SharedPtr&& move) noexcept -> SharedPtr& {
        if (&move == this) {
            return *this;
        }

        if (counter_ != nullptr) {
            --(*counter_);
            if (*counter_ == 0) {
                delete counter_;
                delete data_;
            }
        }

        counter_ = move.counter_;
        data_ = move.data_;
        move.counter_ = nullptr;
        move.data_ = nullptr;

        return *this;
    }

    [[nodiscard]] explicit operator bool() const noexcept { return data_ != nullptr; }

    auto operator*() const noexcept -> T& { return *data_; }

    auto operator->() const noexcept -> T* { return data_; }

    auto get() const noexcept -> T* { return data_; }

    void reset() {
        if (counter_ != nullptr) {
            --(*counter_);
            if (*counter_ == 0) {
                delete counter_;
                delete data_;
            }
        }

        counter_ = nullptr;
        data_ = nullptr;
    }

    void reset(T* ptr) {
        if (counter_ != nullptr) {
            --(*counter_);
            if (*counter_ == 0) {
                delete counter_;
                delete data_;
            }
        }

        if (ptr != nullptr) {
            counter_ = new std::atomic_uint(1);
            data_ = ptr;
        } else {
            counter_ = nullptr;
            data_ = nullptr;
        }
    }

    void swap(SharedPtr& other) { std::swap(*this, other); }

    [[nodiscard]] std::size_t use_count() const {
        return data_ == nullptr ? 0 : static_cast<std::size_t>(*(counter_));
    }

    template <typename Y>
    friend bool operator==(const SharedPtr<Y>& left,
                           const SharedPtr<Y>& right) noexcept;

    template <typename Y>
    friend bool operator==(const SharedPtr<Y>& left, std::nullptr_t);
};

template <typename T>
bool operator==(const SharedPtr<T>& left, const SharedPtr<T>& right) noexcept {
    return left.data_ == right.data_;
}

template <typename T>
bool operator!=(const SharedPtr<T>& left, const SharedPtr<T>& right) noexcept {
    return !(left == right);
}

template <typename T>
bool operator==(const SharedPtr<T>& left, std::nullptr_t) {
    return !left.operator bool();
}

#endif //SHAREDPTR_SHARED_PTR_HPP_
