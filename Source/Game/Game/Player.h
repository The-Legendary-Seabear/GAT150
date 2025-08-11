#pragma once

#include "Framework/Actor.h"

class Player : public viper::Actor {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.5f;
	float fireTimer = 0.0f;
	float laserTime = 30.0f;
	float laserTimer = 0.0f;

	bool fireRateBoostActive = false;
	float boostTime = 5.0f;
	float boostTimer = 0.0f;
	float boostCountDown = 5.0f;
	float canFire = false;

public:
	Player() = default;
	Player(const viper::Transform transform) :
		Actor{ transform} {}
		
	void Update(float dt) override;

	void OnCollision(Actor* other) override;
private:
	void CreateParticle();

};
