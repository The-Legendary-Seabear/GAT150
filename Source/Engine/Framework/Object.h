#pragma once

namespace viper {
	class Object {
	public:
		std::string name;
		bool active{ true };

		Object() = default;
		virtual ~Object() = default;
	};
}
