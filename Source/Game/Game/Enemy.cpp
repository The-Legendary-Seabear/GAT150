#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "FireratePowerup.h"


void Enemy::Update(float dt) {

    bool playerSeen = false;

    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->transform.position - transform.position;

        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation));

        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 180;

        if (playerSeen) {
        float angle = viper::vec2::SignedAngleBetween(forward, direction);
        angle = viper::math::sign(angle);
        transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        
        }



    }


    viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
    velocity += force * dt;

    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());


    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::enemyDesign, viper::vec3{ 1.0f, 1.0f, 1.0f });
        //spawn rocket at player position and rotation
        viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform);// , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->tag = "enemy";
        rocket->name = "rocket";

        scene->AddActor(std::move(rocket));

        // components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		spriteRenderer->textureName = "textures/blue_01.png";
        rocket->AddComponent(std::move(spriteRenderer));

    }
    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
    if (tag != other->tag && other->tag != "powerup") {
        destroyed = true;
        scene->GetGame()->AddPoints(100);


        int randNum = viper::random::getInt(0, 100);
        if (randNum < 5) {
            //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::boost, viper::vec3{ 1.0f, 1.0f, 1.0f });
            FireratePowerup* powerup = new FireratePowerup(viper::Transform{ transform.position, 0.0f, 15.0f }); //, viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
            // components
            auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
            spriteRenderer->textureName = "textures/blue_01.png";
            powerup->AddComponent(std::move(spriteRenderer));

            scene->AddActor(std::unique_ptr<Actor>(powerup));
        }


        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = transform.position;
            particle.velocity = viper::random::OnUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = { 1, 1, 1 };
            particle.lifespan = 2;
            viper::GetEngine().GetPS().AddParticle(particle);
        }
    }
}
