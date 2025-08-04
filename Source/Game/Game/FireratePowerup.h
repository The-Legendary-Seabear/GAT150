#pragma once
#include "Framework/Actor.h"


class FireratePowerup : public viper::Actor {
public:
	FireratePowerup(const viper::Transform& transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
		tag = "powerup";
		name = "fireRatePowerUp";
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};

