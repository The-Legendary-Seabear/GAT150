#pragma once
#include "Framework/Actor.h"

class Enemy : public viper::Actor {
public:
	float speed = 100.0f;
	float fireTimer = 0;
	float fireTime = 0;

public:
	Enemy() = default;
	Enemy(const viper::Transform transform) :
		Actor{ transform} {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:


};

