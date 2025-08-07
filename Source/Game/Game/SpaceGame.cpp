#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "GameData.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"
#include "Core/File.h"
#include "Resources/ResourceManager.h"

#include <vector>
#include <iostream>


bool SpaceGame::Initialize() {
    m_scene = std::make_unique<viper::Scene>(this);

	
    /*
    m_titleFont = std::make_shared<viper::Font>();
    m_titleFont->Load("Archeologicaps.ttf", 128);

    m_uiFont = std::make_shared<viper::Font>();
    m_uiFont->Load("Archeologicaps.ttf", 48);
    */
    //it only loads the first font size
    m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "Archeologicaps.ttf", 128.0f));
    m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Archeologicaps.ttf", 48.0f));
    m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Archeologicaps.ttf", 48.0f));

    
	


    return true;
}

void SpaceGame::Update(float dt) {
    switch (m_gameState) {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound: {
        m_scene->RemoveAllActors();


        if (!m_backgroundMusicStarted) {
            viper::GetEngine().GetAudio().PlaySound("tetris");
            m_backgroundMusicStarted = true;
        }


        //std::shared_ptr<viper::Model> model = std::make_shared <viper::Model>(GameData::points, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 3 };
        auto player = std::make_unique<Player>(transform, viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));

        player->speed = 500.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->tag = "player";
        player->name = "player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 1;
            SpawnEnemy();
        

        }

        break;
    case SpaceGame::GameState::PlayerDead:
        
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
        m_lives--;
        if (m_lives == 0) { 
            m_gameState = GameState::GameOver; 
			m_stateTimer = 3;
        }
        else m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        viper::GetEngine().GetAudio().StopSound();
        if (m_stateTimer <= 0) {
        m_gameState = GameState::Title;
        m_stateTimer = 3;
        }
        break;
    default:
        break;
    }

    //if (viper::GetEngine().GetInput())

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown() {
    //
}

void SpaceGame::Draw(viper::Renderer& renderer) {
    
    if (m_gameState == GameState::Title) {
    
	m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0, 0 }); //exception thrown when this line of code trys to create
    m_titleText->Draw(renderer, 200, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 150, 400);
    }

    m_scoreText->Create(renderer, std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, renderer.GetWidth() - 250, 20);
    
    m_scene->Draw(renderer);

    viper::GetEngine().GetPS().Draw(renderer);
    
    

}

void SpaceGame::OnPlayerDeath() {
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {

    viper::Actor* player = m_scene->GetActorByName<viper::Actor>("player");
    if (player) {
        //std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::enemyDesign, viper::vec3{ 1, 1, 1 });


        viper::vec2 position = player->transform.position + viper::random::OnUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, 0, 10 };


        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
        enemy->damping = 0.5f;
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->speed = (viper::random::getReal() * 200) + 100;
        enemy->tag = "enemy";
        m_scene->AddActor(std::move(enemy));
    }
}

