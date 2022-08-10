

#ifndef Vector2D_hpp
#define Vector2D_hpp

template<typename T>
class Vector2D
{
public:
    T x;
    T y;

    constexpr Vector2D<T>(T X = 0, T Y = 0) noexcept : x(X), y(Y)
    {

    }

    constexpr Vector2D<T>& operator+=(const Vector2D<T>& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector2D<T>& operator/=(T t) noexcept
    {
        x /= t;
        y /= t;
        return *this;
    }
};

template<typename T>
constexpr Vector2D<T> operator+(Vector2D<T> lhs, const Vector2D<T>& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

template<typename T>
constexpr Vector2D<T> operator/(Vector2D<T> vec, T t) noexcept
{
    vec /= t;
    return vec;
}

#endif