#pragma once

#include <vector>

#include "VertexAttribute.h"

namespace Arke {
	struct VertexAttributes {
		std::vector<VertexAttribute> list;

		VertexAttributes(std::initializer_list<VertexAttribute> attributes) {
            list = std::vector(attributes.begin(), attributes.end());
        };

		int totalSizeInBytes();
		[[nodiscard]] int* offsets() const;
	};
};