#include "Vector2.h"

namespace Arke {
    template<class T>
    Vector2<T> Vector2<T>::operator+(Vector2<T> other) {
        return { this->x + other.x, this->y + other.y };
    }

    template<class T>
    Vector2<T> Vector2<T>::operator-(Vector2<T> other) {
        return { this->x - other.x, this->y - other.y };
    }

    template<class T>
    Vector2<T> Vector2<T>::operator*(Vector2<T> other) {
        return { this->x * other.x, this->y * other.y };
    }

    template<class T>
    Vector2<T> Vector2<T>::operator/(Vector2<T> other) {
        return { this->x / other.x, this->y / other.y };
    }

    template<class T>
    void Vector2<T>::operator+=(Vector2<T> other) {
        this->x += other.x;
        this->y += other.y;
    }

    template<class T>
    void Vector2<T>::operator-=(Vector2<T> other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    template<class T>
    void Vector2<T>::operator*=(Vector2<T> other) {
        this->x *= other.x;
        this->y *= other.y;
    }

    template<class T>
    void Vector2<T>::operator/=(Vector2<T> other) {
        this->x /= other.x;
        this->y /= other.y;
    }
}