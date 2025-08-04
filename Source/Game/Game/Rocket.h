#pragma once
#include "Framework/Actor.h"

class Rocket : public viper::Actor {
public:
	float speed = 20.0f;

public:
	Rocket() = default;
	Rocket(const viper::Transform transform, class std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
private:

};