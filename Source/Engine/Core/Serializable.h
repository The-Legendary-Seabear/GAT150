#pragma once
#include "Json.h"

namespace viper {
	class Serializeable {
	public:
		virtual ~Serializeable() = default;

		virtual void Read(const json::value_t& value) = 0;
	};
}
