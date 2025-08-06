
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Math/Transform.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Core/File.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"
#include "Framework/Game.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <Renderer/Renderer.h>
#include <vector>
#include <fmod.hpp>
#include <memory>



int main(int argc, char* argv[]) {
   
    viper::SetCurrentDirectory("Assets");

   //initialize engine
    viper::GetEngine().Initialize();


    //Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    //create objects

	//viper::Scene scene = viper::Scene();

    viper::Font* font = new viper::Font();
    font->Load("Archeologicaps.ttf", 20);

    //viper::Text* text = new viper::Text(font);
    //text->Create(viper::GetEngine().GetRenderer(), "Hello World", viper::vec3{ 1, 1, 1});

    viper::GetEngine().GetAudio().Inititalize();
    viper::GetEngine().GetAudio().AddSound("laser_shoot.wav", "laser");
    viper::GetEngine().GetAudio().AddBackGroundMusic("tetris.wav", "tetris");

    FMOD::Sound* sound = nullptr;
    
    std::vector<FMOD::Sound*> sounds;
   
   //Texture
    //auto texture = viper::ResourceManager::Instance().Get<viper::Texture>("creature", viper::GetEngine().GetRenderer());
    std::shared_ptr<viper::Texture> texture = std::make_shared<viper::Texture>();
    texture->Load("creature.jpg", viper::GetEngine().GetRenderer());



    //create stars
    /*std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280 });
    }*/


    SDL_Event e;
    bool quit = false;

    //std::vector<viper::vec2> points;

    //Main Loop
    while (!quit) {
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();
        //scene.Update(viper::GetEngine().GetTime().GetDeltaTime());

        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
        

        
      
        
        

        //get input 
       

        

        //draw
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor((float)color.r, (float)color.g, (float)color.b);
        viper::GetEngine().GetRenderer().Clear();

        viper::GetEngine().Draw();


        viper::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30);




		//model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10);
        
        
        //scene.Draw(viper::GetEngine().GetRenderer());

        //Draw
        //text->Draw(viper::GetEngine().GetRenderer(), 40.0f, 40.0f);
		game->Draw(viper::GetEngine().GetRenderer());


        //present
        viper::GetEngine().GetRenderer().Present();

}

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
