
#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {

    viper::file::SetCurrentDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    viper::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::json::Load("json.txt", document);

    // read the age data from the json
    int age;
    viper::json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;

    // read/show the data from the json file
    std::string name;
    float speed;
    bool isAwake;
    viper::vec2 position;
    viper::vec3 color;

    // read the json data
    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;


    /*
    //command line arguments
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        viper::Logger::Debug("arg {}: {}", i, argv[i]);
    }

    //file streams
    std::fstream stream("test.txt");
    if (!stream) {
		std::cout << "could not open file\n";
    }
    std::cout << stream.rdbuf();
    std::string line;
    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
    }

    //user data type streams
    viper::vec3 v{ 34.5f, 65.6f, 54.0f };
    std::cout << v << std::endl;

    std::string vstr("{ 23.4, 76.3 }");
    std::stringstream sstream(vstr);

    viper::vec2 v2;
    sstream >> v2;

    std::cout << v2 << std::endl;
    */


   //initialize engine
    viper::GetEngine().Initialize();

    viper::Logger::Info("Initialize engine...");

    //Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    //create objects


    viper::Font* font = new viper::Font();
    font->Load("Archeologicaps.ttf", 20);

    //viper::GetEngine().GetAudio().AddSound("laser_shoot.wav", "laser");
    /*
    viper::GetEngine().GetAudio().Inititalize();
    viper::GetEngine().GetAudio().AddBackGroundMusic("tetris.wav", "tetris");
    viper::GetEngine().GetAudio().AddBackGroundMusic("main_menu.wav", "main_menu");
    viper::GetEngine().GetAudio().AddBackGroundMusic("game_over.wav", "game_over");
    */

    FMOD::Sound* sound = nullptr;
    
    std::vector<FMOD::Sound*> sounds;
   
   //Texture
    //auto texture = viper::Resources().Get<viper::Texture>("Textures/creature.png", viper::GetEngine().GetRenderer());


    SDL_Event e;
    bool quit = false;
    float rotate = 0;


    //Main Loop
    while (!quit) {
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();

        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //draw
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor((float)color.r, (float)color.g, (float)color.b);
        viper::GetEngine().GetRenderer().Clear();

        viper::GetEngine().Draw();


        //Draw Texture ---------
        //rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
        //viper::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, rotate , 4);

        //Draw
		game->Draw(viper::GetEngine().GetRenderer());

        
        //present
        viper::GetEngine().GetRenderer().Present();

}

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
