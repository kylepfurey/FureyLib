// .hpp
// STL Function Class
// by Kyle Furey

#pragma once
#include <utility>
#include <cstddef>
#include <stdexcept>

namespace std {
    template<typename F>
    class func;

    template<typename R, typename... A>
    class func<R(A...)> {
        struct callable_base {
            virtual ~callable_base() = default;

            virtual R operator()(A... args) = 0;
        };

        template<typename T>
        struct callable final : callable_base {
            T call;

            callable(T call) : call{move(call)} {
            }

            R operator()(A... args) override {
                return call(forward<A>(args)...);
            }
        };

        union dispatch_t final {
            R (*pfunc)(A...);

            callable_base *pcall;

            dispatch_t(R (*pfunc)(A...)) : pfunc{pfunc} {
            }

            template<typename F>
            dispatch_t(const F &call) : pcall{new callable<F>{call}} {
            }

            dispatch_t(nullptr_t) : pfunc{nullptr} {
            }
        };

        dispatch_t dispatch;
        bool iscall;

    public:
        func() : dispatch{nullptr}, iscall{false} {
        }

        func(const func &) = delete;

        func(func &&moved) noexcept : dispatch{nullptr} {
            if ((iscall = moved.iscall)) {
                dispatch.pcall = moved.dispatch.pcall;
                moved.dispatch.pfunc = nullptr;
            } else {
                dispatch.pfunc = moved.dispatch.pfunc;
                moved.dispatch.pfunc = nullptr;
            }
            moved.iscall = false;
        }

        func(R (*pfunc)(A...)) : dispatch{pfunc}, iscall{false} {
        }

        template<typename F>
        func(const F &call) : dispatch{call}, iscall{true} {
        }

        func(nullptr_t) : dispatch{nullptr}, iscall{false} {
        }

        ~func() {
            if (iscall) {
                delete dispatch.pcall;
            }
            dispatch.pfunc = nullptr;
            iscall = false;
        }

        func &operator=(const func &) = delete;

        func &operator=(func &&moved) noexcept {
            if (this == &moved) {
                return *this;
            }
            if (iscall) {
                delete dispatch.pcall;
            }
            if ((iscall = moved.iscall)) {
                dispatch.pcall = moved.dispatch.pcall;
                moved.dispatch.pfunc = nullptr;
            } else {
                dispatch.pfunc = moved.dispatch.pfunc;
                moved.dispatch.pfunc = nullptr;
            }
            moved.iscall = false;
            return *this;
        }

        func &operator=(R (*pfunc)(A...)) {
            if (iscall) {
                delete dispatch.pcall;
            }
            dispatch.pfunc = pfunc;
            iscall = false;
            return *this;
        }

        template<typename F>
        func &operator=(const F &call) {
            auto *p = new callable<F>{call};
            if (iscall) {
                delete dispatch.pcall;
            }
            dispatch.pcall = p;
            iscall = true;
            return *this;
        }

        func &operator=(nullptr_t) {
            if (iscall) {
                delete dispatch.pcall;
            }
            dispatch.pfunc = nullptr;
            iscall = false;
            return *this;
        }

        explicit operator bool() const {
            return iscall ? dispatch.pcall != nullptr : dispatch.pfunc != nullptr;
        }

        R operator()(A... args) const {
            if (iscall) {
                if (dispatch.pcall == nullptr) {
                    throw runtime_error("NULL std::func call");
                }
                return (*dispatch.pcall)(forward<A>(args)...);
            }
            if (dispatch.pfunc == nullptr) {
                throw runtime_error("NULL std::func call");
            }
            return dispatch.pfunc(forward<A>(args)...);
        }
    };
}
