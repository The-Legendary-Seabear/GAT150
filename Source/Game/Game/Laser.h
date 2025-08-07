#pragma once
#include "Framework/Actor.h"
#include "Renderer/Texture.h"

class Laser : public viper::Actor {
public:
	float speed = 20.0f;

public:
	Laser() = default;
	Laser(const viper::Transform transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
private:

};

