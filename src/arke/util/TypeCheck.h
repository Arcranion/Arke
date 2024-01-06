#pragma once

#include <concepts>

template<class Type, class Base>
concept TypeExtends = std::is_base_of<Base, Type>::value;