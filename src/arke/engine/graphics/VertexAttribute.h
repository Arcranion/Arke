#pragma once

#include <string>
#include <utility>

namespace Arke {
	struct VertexAttribute {
		enum class Type
		{
			Float,
			UnsignedByte,
			UnsignedShort,
		};

		std::string name;
		int components;
		Type type = Type::Float;
		bool normalized = false;

		VertexAttribute(
			std::string name,
			int components,
			Type type = Type::Float,
			bool normalized = false
		) : name(std::move(name)), components(components), type(type), normalized(normalized) {};

		[[nodiscard]] int sizeInBytes() const;
	};
};