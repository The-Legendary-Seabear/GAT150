#include "RocketController.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include "../GamePCH.h"

FACTORY_REGISTER(RocketController)

void RocketController::Start() {
    m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void RocketController::Update(float dt) {

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = owner->transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;

    if (m_rigidBody) {
        m_rigidBody->ApplyForce(force);
    }
}

void RocketController::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag && other->tag != "player") {
        owner->destroyed = true;
    }
}

void RocketController::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);


}
