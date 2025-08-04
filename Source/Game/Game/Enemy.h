#pragma once
#include "Framework/Actor.h"

class Enemy : public viper::Actor {
public:
	float speed = 100.0f;
	float fireTimer = 0;
	float fireTime = 0;

public:
	Enemy() = default;
	Enemy(const viper::Transform transform, class std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:


};

