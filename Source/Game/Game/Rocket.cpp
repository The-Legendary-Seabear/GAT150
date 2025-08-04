#include "Rocket.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"

void Rocket::Update(float dt) {

    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle)) * speed;
   

    viper::Particle particle;
    particle.position = transform.position;
    particle.velocity = velocity;
    particle.color = (tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
    particle.lifespan = viper::random::getReal(0.15f, 0.3f);
    viper::GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other) {
    if (tag != other->tag) {
        destroyed = true;
    }
}
