#pragma once

namespace Arke::UI {
    class Dp {
    public:
        float value;

        Dp(float value): value(value) {};
        Dp(int value): value(static_cast<float>(value)) {};
        Dp(double value): value(static_cast<float>(value)) {};

        inline Dp operator +(Dp other) const;
        inline Dp operator -(Dp other) const;
        inline Dp operator *(Dp other) const;
        inline Dp operator /(Dp other) const;

        void operator +=(Dp other);
        void operator -=(Dp other);
        void operator *=(Dp other);
        void operator /=(Dp other);

        bool operator ==(Dp other) const;
        bool operator <(Dp other) const;
        bool operator >(Dp other) const;
        bool operator <=(Dp other) const;
        bool operator >=(Dp other) const;
    };
}