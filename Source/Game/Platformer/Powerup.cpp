#include "Powerup.h"
#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Powerup)

void Powerup::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Powerup::Update(float dt) {
	//
}


void Powerup::OnCollision(viper::Actor* other) {
	if (viper::equalsIgnoreCase(other->tag, "player")) {
		owner->destroyed = true;
		EVENT_NOTIFY_DATA(add_points, 100);
	}
}

void Powerup::Read(const viper::json::value_t& value) {
	Object::Read(value);

}