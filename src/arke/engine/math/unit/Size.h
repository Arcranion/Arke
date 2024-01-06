#pragma once

namespace Arke {
    template<class T>
    class BaseSize {
    public:
        T width;
        T height;
    };

    class IntSize: public BaseSize<int> {};
    class FloatSize: public BaseSize<float> {};
    class DoubleSize: public BaseSize<double> {};

    using Size = FloatSize;
}