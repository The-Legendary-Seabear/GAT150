#include "RigidBody.h"

namespace viper {

	void viper::RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt)); // ( < 1) = slow down, 1/1.1 = < 1
	}

}
