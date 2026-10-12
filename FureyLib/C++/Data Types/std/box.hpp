// .hpp
// STL Box Class
// by Kyle Furey

#pragma once
#include <utility>
#include <cstddef>
#include <stdexcept>

namespace std {
    class box final {
        struct wrapper_base {
            virtual ~wrapper_base() = default;
        };

        template<typename T>
        struct wrapper final : wrapper_base {
            T val;

            wrapper(T val) : val{move(val)} {
            }
        };

        wrapper_base *pval;

    public:
        box() : pval{nullptr} {
        }

        box(const box &) = delete;

        box(box &&moved) noexcept {
            pval = moved.pval;
            moved.pval = nullptr;
        }

        template<typename T>
        box(T val) : pval{new wrapper<T>{move(val)}} {
        }

        box(nullptr_t) : pval{nullptr} {
        }

        ~box() {
            delete pval;
            pval = nullptr;
        }

        box &operator=(const box &) = delete;

        box &operator=(box &&moved) noexcept {
            if (this == &moved) {
                return *this;
            }
            delete pval;
            pval = moved.pval;
            moved.pval = nullptr;
            return *this;
        }

        template<typename T>
        box &operator=(T val) {
            auto *p = new wrapper<T>{move(val)};
            delete pval;
            pval = p;
            return *this;
        }

        box &operator=(nullptr_t) {
            delete pval;
            pval = nullptr;
            return *this;
        }

        explicit operator bool() const {
            return pval != nullptr;
        }

        template<typename T>
        bool type() const {
            return pval && dynamic_cast<wrapper<T> *>(pval);
        }

        template<typename T>
        T &get() {
            auto *p = dynamic_cast<wrapper<T> *>(pval);
            if (p == nullptr) {
                throw runtime_error("NULL or bad std::box deref");
            }
            return p->val;
        }

        template<typename T>
        const T &get() const {
            auto *p = dynamic_cast<const wrapper<T> *>(pval);
            if (p == nullptr) {
                throw runtime_error("NULL or bad std::box deref");
            }
            return p->val;
        }
    };
}
