#include <fit/reverse_fold.hpp>
#include "test.hpp"

struct max_f
{
    template<class T, class U>
    constexpr T operator()(T x, U y) const noexcept
    {
        return x > y ? x : y;
    }
};

struct sum_f
{
    template<class T, class U>
    constexpr T operator()(T x, U y) const FIT_RETURNS_DEDUCE_NOEXCEPT(x+y)
    {
        return x + y;
    }
};

#if FIT_HAS_NOEXCEPT_DEDUCTION
FIT_TEST_CASE()
{
    static_assert(noexcept(fit::reverse_fold(max_f(), 0)(2, 3, 4, 5)), "noexcept reverse_fold");
    static_assert(noexcept(fit::reverse_fold(sum_f(), 0)(2, 3, 4, 5)), "noexcept reverse_fold");
    static_assert(!noexcept(fit::reverse_fold(sum_f(), std::string())("hello", "-", "world")), "noexcept reverse_fold");
}
#endif

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(fit::reverse_fold(max_f(), 0)(2, 3, 4, 5) == 5);
    FIT_TEST_CHECK(fit::reverse_fold(max_f(), 0)(5, 4, 3, 2) == 5);
    FIT_TEST_CHECK(fit::reverse_fold(max_f(), 0)(2, 3, 5, 4) == 5);

    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f(), 0)(2, 3, 4, 5) == 5);
    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f(), 0)(5, 4, 3, 2) == 5);
    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f(), 0)(2, 3, 5, 4) == 5);
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(fit::reverse_fold(max_f(), 0)() == 0);
    FIT_TEST_CHECK(fit::reverse_fold(max_f(), 0)(5) == 5);

    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f(), 0)() == 0);
    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f(), 0)(5) == 5);
}

template<class... Ts>
constexpr auto find_positive_max(Ts... xs) FIT_RETURNS
(
    fit::reverse_fold(max_f(), 0)(xs...)
);

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(find_positive_max() == 0);
    FIT_TEST_CHECK(find_positive_max(5) == 5);

    FIT_STATIC_TEST_CHECK(find_positive_max() == 0);
    FIT_STATIC_TEST_CHECK(find_positive_max(5) == 5);
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(fit::reverse_fold(max_f())(5) == 5);

    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f())(5) == 5);
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(fit::reverse_fold(max_f())(2, 3, 4, 5) == 5);
    FIT_TEST_CHECK(fit::reverse_fold(max_f())(5, 4, 3, 2) == 5);
    FIT_TEST_CHECK(fit::reverse_fold(max_f())(2, 3, 5, 4) == 5);

    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f())(2, 3, 4, 5) == 5);
    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f())(5, 4, 3, 2) == 5);
    FIT_STATIC_TEST_CHECK(fit::reverse_fold(max_f())(2, 3, 5, 4) == 5);
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(fit::reverse_fold(sum_f(), std::string())("hello", "-", "world") == "world-hello");
}