#include "VertexAttribute.h"

namespace Arke {
	int VertexAttribute::sizeInBytes() const {
		switch (this->type) {
			case Type::Float:
				return 4 * components;
			case Type::UnsignedByte:
				return components;
			case Type::UnsignedShort:
				return 2 * components;
		}
	}
}