#pragma once
#include "Core/Serializable.h"
#include <string>

namespace viper {
	class Object : public Serializeable {
	public:
		std::string name;
		bool active{ true };

		Object() = default;
		virtual ~Object() = default;

		// Inherited via Serializeable
		void Read(const json::value_t& value) override;
	};
}
