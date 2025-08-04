#pragma once
#include "Framework/Actor.h"

class Laser : public viper::Actor {
public:
	float speed = 20.0f;

public:
	Laser() = default;
	Laser(const viper::Transform transform, class std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
private:

};

