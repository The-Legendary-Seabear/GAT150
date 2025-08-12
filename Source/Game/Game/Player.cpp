#include "Player.h"
#include "GameData.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "Laser.h"
#include "../GamePCH.h"



void Player::Update(float dt) {
  


    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) { 
        CreateParticle();
        rotate -= 1;
    }
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) { 
        CreateParticle();
        rotate += 1; }

    transform.rotation += (rotate * rotationRate) * dt;

    //thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) { 
        CreateParticle();
        thrust = 1;
    }
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        CreateParticle();
        thrust = -1; }
    
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        this->speed = 3000;
    }
    else { this->speed = 500;  }



    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed;
	//velocity += force * dt;
    auto* rb = GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());


    //check fire key pressed
    laserTimer -= dt;
    fireTimer -= dt;

    if (fireRateBoostActive) {
        boostCountDown -= dt;
        if (boostCountDown <= 0) {
            fireRateBoostActive = false;
            boostCountDown = boostTime; // reset for next powerup
        }
    }

    

    if (fireRateBoostActive) {
        canFire = viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE);
    }
    else {
        canFire = viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0;
    }

    if (canFire) {
        fireTimer = fireTime;

        //viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("laser.wav", viper::GetEngine().GetAudio()).get());
        
        
        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::points, viper::vec3{ 1.0f, 1.0f, 1.0f });
        //spawn rocket at player position and rotation
        viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform); // , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->tag = "player";
        rocket->name = "rocket";

        // components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/rocket.png";
        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        viper::GetEngine().GetAudio().PlaySound("laser");

        

        scene->AddActor(std::move(rocket));
    }

    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && laserTimer <= 0) {
        laserTimer = laserTime;
       
            
            //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::laser, viper::vec3{ 1.0f, 1.0f, 1.0f });
            //spawn rocket at player position and rotation
            viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
            auto laser = std::make_unique<Laser>(transform); // , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

            laser->speed = 5000.0f;
            laser->lifespan = 10.0f;
            laser->tag = "player";
            laser->name = "laser";

            // components
            auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
            spriteRenderer->textureName = "textures/laser.png";
            laser->AddComponent(std::move(spriteRenderer));

            auto rb = std::make_unique<viper::RigidBody>();
            laser->AddComponent(std::move(rb));

            auto collider = std::make_unique<viper::CircleCollider2D>();
            collider->radius = 10;
            laser->AddComponent(std::move(collider));


            viper::GetEngine().GetAudio().PlaySound("laser");



            scene->AddActor(std::move(laser));
    }
    
    Actor::Update(dt);

   
}

void Player::OnCollision(Actor* other) {
    if (tag != other->tag && other->tag != "powerup") {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}

void Player::CreateParticle() {
    viper::Particle particle;
    particle.position = transform.position;
    particle.velocity = viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
    particle.color = { 1, 1, 1 };
    particle.lifespan = 2;
    viper::GetEngine().GetPS().AddParticle(particle);
}


