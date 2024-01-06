#include <arke/util/Error.h>
#include "Dp.h"

using namespace util;

namespace Arke::UI {

    Dp Dp::operator +(Dp other) const {
        return { this->value + other.value };
    }

    Dp Dp::operator -(Dp other) const {
        return { this->value - other.value };
    }

    Dp Dp::operator *(Dp other) const {
        return { this->value * other.value };
    }

    Dp Dp::operator /(Dp other) const {
        return { this->value / other.value };
    }

    void Dp::operator +=(Dp other) {
        this->value += other.value;
    }

    void Dp::operator -=(Dp other) {
        this->value -= other.value;
    }

    void Dp::operator *=(Dp other) {
        this->value *= other.value;
    }

    void Dp::operator /=(Dp other) {
        this->value /= other.value;
    }

    bool Dp::operator==(Dp other) const {
        return this->value == other.value;
    }

    bool Dp::operator<(Dp other) const {
        return this->value < other.value;
    }

    bool Dp::operator>(Dp other) const {
        return this->value > other.value;
    }

    bool Dp::operator<=(Dp other) const {
        return this->value <= other.value;
    }

    bool Dp::operator>=(Dp other) const {
        return this->value >= other.value;
    }
}