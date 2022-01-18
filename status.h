#ifndef _STATUS_H_
#define _STATUS_H_

#pragma once
#include <atomic>
#include <memory>
#include <ostream>
#include <iterator>
#include <type_traits>

namespace sts
{
    template <typename Otp, typename Stp>
    class status_base;

    template <typename Otp, typename Stp>
    inline std::ostream &
    operator<<(std::ostream &os, const status_base<Otp, Stp> &status)
    {
        os << status.get();
        return os;
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator==(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1.get() == s2.get();
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator==(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1 == s2.get();
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator==(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return s1.get() == s2;
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator!=(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1.get() == s2.get());
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator!=(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1 == s2.get());
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator!=(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return !(s1.get() == s2);
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator>(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1.get() > s2.get();
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator>(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1 > s2.get();
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator>(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return s1.get() > s2;
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator<(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1.get() < s2.get();
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator<(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return s1 < s2.get();
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator<(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return s1.get() < s2;
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator<=(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1.get() > s2.get());
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator<=(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1 > s2.get());
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator<=(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return !(s1.get() > s2);
    }

    template <typename Otp1, typename Stp1, typename Otp2, typename Stp2>
    inline bool
    operator>=(const status_base<Otp1, Stp1> &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1.get() < s2.get());
    }

    template <typename Otp1, typename Otp2, typename Stp2>
    inline bool
    operator>=(const Otp1 &s1, const status_base<Otp2, Stp2> &s2) noexcept
    {
        return !(s1 < s2.get());
    }

    template <typename Otp1, typename Stp1, typename Otp2>
    inline bool
    operator>=(const status_base<Otp1, Stp1> &s1, const Otp2 &s2) noexcept
    {
        return !(s1.get() < s2);
    }

    template <typename Otp, typename Stp = Otp>
    inline status_base<Otp, Stp> make_status(const Otp &value)
    {
        return status_base<Otp, Stp>(value);
    }

    template <typename Iter, typename Otp>
    static bool
    any(const Iter &begin, const Iter &end, const Otp &value)
    {
        for (Iter iter = begin; iter != end; iter = std::next(iter))
        {
            if ((*iter) == value)
                return true;
        }
        return false;
    }

    template <typename Iter, typename Otp>
    static bool
    all(const Iter &begin, const Iter &end, const Otp &value)
    {
        for (Iter iter = begin; iter != end; iter = std::next(iter))
        {
            if ((*iter) != value)
                return false;
        }
        return true;
    }

    template <typename Iter, typename Otp>
    inline bool
    any(const Iter &iter, const Otp &value)
    {
        return any(std::begin(iter), std::end(iter), value);
    }

    template <typename Iter, typename Otp>
    inline bool
    all(const Iter &iter, const Otp &value)
    {
        return all(std::begin(iter), std::end(iter), value);
    }

    template <typename Iter, typename Otp>
    inline bool
    any(const std::initializer_list<Iter> &iter, const Otp &value)
    {
        return any(std::begin(iter), std::end(iter), value);
    }

    template <typename Iter, typename Otp>
    inline bool
    all(const std::initializer_list<Iter> &iter, const Otp &value)
    {
        return all(std::begin(iter), std::end(iter), value);
    }

    template <typename Otp, typename Stp>
    class status_base
    {
    public:
        using ST = status_base<Otp, Stp>;

        status_base() noexcept {}

        status_base(const Otp &value) noexcept
            : m_status(std::make_shared<Stp>(value)) {}

        status_base(const ST &instance) noexcept
            : m_status(instance.m_status) {}

        status_base(ST &&instance) noexcept
            : m_status(instance.m_status) {}

        template <typename Stpn>
        status_base(const status_base<Otp, Stpn> &instance) noexcept
            : m_status(std::make_shared<Stp>(instance.get())) {}

        template <typename Stpn>
        status_base(status_base<Otp, Stpn> &&instance) noexcept
            : m_status(std::make_shared<Stp>(instance.get())) {}

        ~status_base() = default;

        ST &
        operator=(const ST &instance)
        {
            m_status = instance.m_status;
            return *this;
        }

        ST &
        operator=(ST &&instance)
        {
            m_status = instance.m_status;
            return *this;
        }

        ST &
        operator=(const Otp &value)
        {
            set(value);
            return *this;
        }

        ST &
        operator=(Otp &&value)
        {
            set(value);
            return *this;
        }

        const Otp
        get() const
        {
            Otp value = *m_status;
            return value;
        }

        void
        set(const Otp &status)
        {
            *m_status = status;
        }

    private:
        std::shared_ptr<Stp> m_status;
    };

    template <typename Otp>
    using safe_status = status_base<Otp, std::atomic<Otp>>;
    template <typename Otp>
    using fast_status = status_base<Otp, Otp>;
} // namespace status

#endif //_STATUS_H_