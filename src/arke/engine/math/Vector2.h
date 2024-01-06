#pragma once

namespace Arke {
    template<class T>
    class Vector2 {
    public:
        T x;
        T y;

        virtual Vector2<T> operator +(Vector2<T> other);
        virtual Vector2<T> operator -(Vector2<T> other);
        virtual Vector2<T> operator *(Vector2<T> other);
        virtual Vector2<T> operator /(Vector2<T> other);

        virtual void operator +=(Vector2<T> other);
        virtual void operator -=(Vector2<T> other);
        virtual void operator *=(Vector2<T> other);
        virtual void operator /=(Vector2<T> other);
    };

    using Int2 = Vector2<int>;
    using Float2 = Vector2<float>;
    using Double2 = Vector2<double>;
}