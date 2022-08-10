
#ifndef QuadBox_hpp
#define QuadBox_hpp

#include "Vector2D.hpp"

template<typename T>
class QuadBox {
    
    public:
    T left;
    T top;
    T width; // Must be positive
    T height; // Must be positive



    constexpr QuadBox(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept :
        left(Left), top(Top), width(Width), height(Height)
    {

    }

    constexpr QuadBox(const Vector2D<T>& position, const Vector2D<T>& size) noexcept :
        left(position.x), top(position.y), width(size.x), height(size.y)
    {

    }

    constexpr T getRight() const noexcept
    {
        return left + width;
    }

    constexpr T getBottom() const noexcept
    {
        return top + height;
    }

    constexpr Vector2D<T> getTopLeft() const noexcept
    {
        return Vector2D<T>(left, top);
    }

    constexpr Vector2D<T> getCenter() const noexcept
    {
        return Vector2D<T>(left + width / 2, top + height / 2);
    }

    constexpr Vector2D<T> getSize() const noexcept
    {
        return Vector2D<T>(width, height);
    }

    constexpr bool contains(const QuadBox<T>& box) const noexcept
    {
        return left <= box.left && box.getRight() <= getRight() &&
            top <= box.top && box.getBottom() <= getBottom();
    }

    constexpr bool intersects(const QuadBox<T>& box) const noexcept
    {
        return !(left >= box.getRight() || getRight() <= box.left ||
            top >= box.getBottom() || getBottom() <= box.top);
    }

};


#endif