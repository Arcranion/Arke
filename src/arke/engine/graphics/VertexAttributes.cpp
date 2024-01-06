#include "VertexAttributes.h"

namespace Arke {
	int VertexAttributes::totalSizeInBytes() {
		int sum = 0;
		for (const auto& attr : this->list)
		{
			sum += attr.sizeInBytes();
		}
		return sum;
	}

	int* VertexAttributes::offsets() const {
		auto arr = new int[this->list.size()+1];
		int bytes = 0;
		int index = 0;
		for (const VertexAttribute& attr : this->list)
		{
			arr[index++] = bytes;
			bytes += attr.sizeInBytes();
		}

		return arr;
	}
};