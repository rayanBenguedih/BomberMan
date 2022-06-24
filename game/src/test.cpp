/*
** EPITECH PROJECT, 2022
** test.c
** File description:
** test.c
*/

#ifdef _WIN32
#include <windows.h>
#include "..\\..\\gamecore\\includes\\core.hpp"
#include "..\\..\\gamecore\\includes\\Daedalus.hpp"
#include "..\\..\\engine\\includes\\Engine.hpp"
#include "..\\..\\engine\\includes\\Entities\\Player.hpp"
#include "..\\..\\engine\\includes\\Entities\\Wall.hpp"
#include "..\\..\\engine\\includes\\Entities\\Bomb.hpp"
#include "..\\..\\engine\\includes\\Audio\\Audio.hpp"
#include "..\\..\\engine\\libs\\Raylib\\includes\\Camera3D.hpp"
#include "..\\..\\engine\\libs\\Raylib\\includes\\Keyboard.hpp"
#include "..\\..\\engine\\libs\\Raylib\\includes\\Raylib.hpp"
#include <thread>
#else
#include "../../gamecore/includes/core.hpp"
#include "../../gamecore/includes/Daedalus.hpp"
#include "../../engine/includes/Engine.hpp"
#include "../../engine/includes/Entities/Player.hpp"
#include "../../engine/includes/Entities/Wall.hpp"
#include "../../engine/includes/Entities/Bomb.hpp"
#include "../../engine/includes/Audio/Audio.hpp"
//#include "engine/includes/raylib.h"
#include "../../engine/libs/Raylib/includes/Camera3D.hpp"
#include "../../engine/libs/Raylib/includes/Keyboard.hpp"
#include "../../engine/libs/Raylib/includes/Raylib.hpp"
#include "../../gamecore/includes/core.hpp"
#include "../../engine/includes/Engine.hpp"
#include "../../engine/includes/Entities/Player.hpp"
#include "../../engine/includes/raylib.h"
#include "../../engine/libs/Raylib/includes/Camera3D.hpp"
#include "../../engine/libs/Raylib/includes/Collision.hpp"
#include "../../engine/libs/Raylib/includes/Keyboard.hpp"
#include "../../engine/libs/Raylib/includes/Raylib.hpp"
#include <thread>
#endif


std::vector<std::thread> myThreads;

bool collision(std::vector<Vector3> wallsPos, std::vector<Vector3> boxesPos,
               std::vector<Vector3> bombsPos, Entities::Player player,
               float x, float z, bool troughWall)
{
    Raylib::Collision checkCollision = Raylib::Collision();
    Vector3 wallSize = { 2.0f, 2.0f, 2.0f };
    Vector3 boxSize = { 1.7f, 1.7f, 1.7f };
    Vector3 playerSize = { 1.7f, 1.5f, 1.7f };
    Vector3 player1 = {player.getPosition().x + 0.25f + x*2 - playerSize.x / 2,
                       player.getPosition().y - playerSize.y / 2,
                       player.getPosition().z + z*2 - playerSize.z / 2};
    Vector3 player2 = {player.getPosition().x + 0.25f + x*2 + playerSize.x / 2,
                       player.getPosition().y + playerSize.y / 2,
                       player.getPosition().z + z*2 + playerSize.z / 2};
    BoundingBox playerAfterMove = {player1, player2};
    Vector3 player3 = {player.getPosition().x + 0.25f - playerSize.x / 2,
                       player.getPosition().y - playerSize.y / 2,
                       player.getPosition().z - playerSize.z / 2};
    Vector3 player4 = {player.getPosition().x + 0.25f + playerSize.x / 2,
                       player.getPosition().y + playerSize.y / 2,
                       player.getPosition().z + playerSize.z / 2};
    BoundingBox playerBeforeMove = {player3, player4};
    for (std::size_t i = 0; i < wallsPos.size(); i++) {
        Vector3 wall1 = {wallsPos[i].x - wallSize.x / 2,
                         wallsPos[i].y - wallSize.y / 2,
                         wallsPos[i].z - wallSize.z / 2};
        Vector3 wall2 = {wallsPos[i].x + wallSize.x / 2,
                         wallsPos[i].y + wallSize.y / 2,
                         wallsPos[i].z + wallSize.z / 2};
        BoundingBox wallBox = {wall1, wall2};
        if (checkCollision.checkCollisionBoxes(playerAfterMove, wallBox))
            return true;
    }
    for (std::size_t i = 0; i < bombsPos.size(); i++) {
        if (checkCollision.checkCollisionBoxSphere(playerBeforeMove, bombsPos[i], 0.8f)) {
            continue;
        }
        if (checkCollision.checkCollisionBoxSphere(playerAfterMove, bombsPos[i], 0.8f)) {
            return true;
        }
    }
    if (troughWall)
        return false;
    for (std::size_t i = 0; i < boxesPos.size(); i++) {
        Vector3 box1 = {boxesPos[i].x - boxSize.x / 2,
                        boxesPos[i].y - boxSize.y / 2,
                        boxesPos[i].z - boxSize.z / 2};
        Vector3 box2 = {boxesPos[i].x + boxSize.x / 2,
                        boxesPos[i].y + boxSize.y / 2,
                        boxesPos[i].z + boxSize.z / 2};
        BoundingBox boxBox = {box1, box2};
        if (checkCollision.checkCollisionBoxes(playerAfterMove, boxBox))
            return true;
    }
    return false;
}

void *botThread(void *args)
{
    Daedalus::Neron *bot = (Daedalus::Neron *)args;
    bot->set_difficulty(100);
    bot->play_game();
    // pthread_exit(NULL);
    return (NULL);
}

int inputPad(Raylib::Gamepad pad)
{
    if (pad.getAxisMovement(0) > abs(pad.getAxisMovement(1)) || pad.isButtonDown(2)) {
        return 1;
    } else if (pad.getAxisMovement(0) < -abs(pad.getAxisMovement(1)) || pad.isButtonDown(4)) {
        return 2;
    } else if (pad.getAxisMovement(1) > abs(pad.getAxisMovement(0)) || pad.isButtonDown(3)) {
        return 3;
    } else if (pad.getAxisMovement(1) < -abs(pad.getAxisMovement(0)) || pad.isButtonDown(1)) {
        return 4;
    }
    if (pad.isButtonDown(7)) {
        return 5;
    }
    return 0;
}
void *getBomb(Entities::Player *player)
{
    Objects::Objects *obj = player->getObject("Bomb");
    Objects::Bomb *bomb = dynamic_cast<Objects::Bomb *>(obj);
    return (bomb);
}
void execute_bot(Daedalus::Neron *bot)
{
    bot->play_game();
}
int bomberman(int nbPlayers, int keyOrPad)
{
    Core *core = new Core(nbPlayers);
    std::vector<Daedalus::Neron *> bots;
    for (int i = 0; i < 4 - nbPlayers; i++)
        bots.push_back(new Daedalus::Neron(core, core->_players[i + nbPlayers]._coord, i + nbPlayers));
    for (std::size_t i = 0; i < bots.size(); i++) {
        usleep(50000);
        std::thread thread_o(execute_bot, new Daedalus::Neron(core, core->_players[i + nbPlayers]._coord, i+ nbPlayers));
        myThreads.push_back(move(thread_o));
    }
    Raylib::Window window = Raylib::Window(1920, 1080, "Sac Abandonnée");
    InitAudioDevice();
    Raylib::Music music = Raylib::Music("game/assets/Game_music.mp3");
    Raylib::Keyboard keyboard = Raylib::Keyboard();
    Raylib::Gamepad gamepadJ1(-1);
    Raylib::Gamepad gamepadJ2(-1);
    Raylib::Gamepad gamepadJ3(-1);
    Raylib::Gamepad gamepadJ4(-1);
    Raylib::Camera3D camera3D = Raylib::Camera3D({ 0.0f, 35.0f, 22.5f },
                                                 { 0.0f, 0.0f, 2.5f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0);
    std::vector<Entities::Player> players;
    std::vector<Entities::Wall> boxes;
    std::vector<Entities::Wall> walls;
    std::shared_ptr<Raylib::Sound> boom = std::make_shared<Raylib::Sound>("game/assets/Boom.ogg");
    std::vector<int> toDelete;
    int bombRange;
    std::vector<Vector3> wallsPos;
    std::vector<Vector3> boxesPos;
    std::vector<Vector3> bombsPos;
    std::vector<Vector3> bombs2Pos;
    std::vector<Vector3> bombs3Pos;
    std::vector<Vector3> playersPos;
    std::vector<Raylib::Color> playersColor = { Raylib::Color(230, 41, 55, 255),
                                                Raylib::Color(0, 228, 48, 255),
                                                Raylib::Color(0, 121, 241, 255),
                                                Raylib::Color(253, 249, 0, 255) };
    //Vector3 wallSize = { 2.0f, 2.0f, 2.0f };
    Vector3 boxSize = { 1.7f, 1.7f, 1.7f };
    // Vector3 playerSize = { 1.5f, 2.25f, 1.5f };
    unsigned int animsCount = 0;
    std::map<std::string, ModelAnimation> animations = {
            std::make_pair("walk", *LoadModelAnimations("game/assets/Player1.iqm", &animsCount))
    };
    std::map<std::string, void *(*)(Entities::Player *)> functions = {{"getBomb", getBomb}};
    std::map<std::string, Objects::Objects *> objects = {{"Bomb", new Objects::Bomb()}};
    std::map<std::string, std::shared_ptr<Raylib::Sound>> sounds = {
            std::make_pair("footstep", std::make_shared<Raylib::Sound>("game/assets/footStepRobot.ogg")),
            std::make_pair("bomb_plant", std::make_shared<Raylib::Sound>("game/assets/Bomb_plant.ogg"))
    };
    std::vector<Entities::Bomb> bombs;
    std::shared_ptr<Raylib::Model> bombMod = std::make_shared<Raylib::Model>("game/assets/textures/3d/Bomb.obj", "game/assets/textures/3d/Normal.png");
    Raylib::Model *mecha1 = new Raylib::Model("game/assets/Player1.iqm", "game/assets/textures/3d/redTexture.png");
    players.push_back(Entities::Player(mecha1, animations, functions, objects, sounds, 0));
    players[0].setPosition({core->_players[0]._coord[0] * 2 - float(core->_map[0].size()) + 1.0f, 1.0f, core->_players[0]._coord[1] * 2 - float(core->_map.size()) + 1.0f});
    players[0].setSpeed(core->_players[0]._speed);
    Raylib::Model *mecha2 = new Raylib::Model("game/assets/Player1.iqm",
                                              "game/assets/textures/3d/cyanTexture.png");
    players.push_back(Entities::Player(mecha2, animations, functions, objects, sounds, 0));
    players[1].setPosition({core->_players[1]._coord[0] * 2 - float(core->_map[0].size()) + 0.75f, 1.0f, core->_players[1]._coord[1] * 2 - float(core->_map.size()) + 1.25f});
    players[1].setSpeed(core->_players[1]._speed);
    Raylib::Model *mecha3 = new Raylib::Model("game/assets/Player1.iqm",
                                              "game/assets/textures/3d/greenTexture.png");
    players.push_back(Entities::Player(mecha3, animations, functions, objects, sounds, 0));
    players[2].setPosition({core->_players[2]._coord[0] * 2 - float(core->_map[0].size()) + 1.0f, 1.0f, core->_players[2]._coord[1] * 2 - float(core->_map.size()) + 1.0f});
    players[2].setSpeed(core->_players[2]._speed);
    Raylib::Model *mecha4 = new Raylib::Model("game/assets/Player1.iqm",
                                              "game/assets/textures/3d/purpleTexture.png");
    players.push_back(Entities::Player(mecha4, animations, functions, objects, sounds, 0));
    players[3].setPosition({core->_players[3]._coord[0] * 2 - float(core->_map[0].size()) + 0.75f, 1.0f, core->_players[3]._coord[1] * 2 - float(core->_map.size()) + 0.75f});
    players[3].setSpeed(core->_players[3]._speed);
    if (keyOrPad == 0) {
        gamepadJ1 = Raylib::Gamepad(-1);
        gamepadJ2 = Raylib::Gamepad(0);
        gamepadJ3 = Raylib::Gamepad(1);
        gamepadJ4 = Raylib::Gamepad(2);
    } else {
        gamepadJ1 = Raylib::Gamepad(0);
        gamepadJ2 = Raylib::Gamepad(1);
        gamepadJ3 = Raylib::Gamepad(2);
        gamepadJ4 = Raylib::Gamepad(3);
    }
    SetTargetFPS(60);
    music.play();
    for (std::size_t i = 0; i < core->_map.size(); i++) {
        for (std::size_t j = 0; j < core->_map[i].size(); j++) {
            if (core->_map[i][j] == '#') {
                wallsPos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1});
            }
            if (core->_map[i][j] == 'M') {
                boxesPos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1});
            }
        }
    }
    players[0].moveRight();
    // Boxes entities creation
    // TODO: These lines segfault when it initialise in for loop
    std::map<std::string, ModelAnimation> animationsBox;
    std::shared_ptr<Raylib::Model> modelBox = std::make_shared<Raylib::Model>
            ("game/assets/textures/3d/Box.obj",
             "game/assets/textures/3d/boxTexture3.png");
    for (std::size_t i = 0; i < boxesPos.size(); i++) {
        boxes.push_back(Entities::Wall(boxesPos[i], modelBox, animationsBox, boom, false));
    }
    std::shared_ptr<Raylib::Model> wallModel = std::make_shared<Raylib::Model>
            ("game/assets/textures/3d/Box.obj",
             "game/assets/textures/3d/boxTexture5.png");
    for (std::size_t i = 0; i < wallsPos.size(); i++) {
        walls.push_back(Entities::Wall(wallsPos[i], wallModel, animationsBox,
                                       boom, false));
    }
    int lively = 4;
    while (!window.shouldClose()) {
        music.update();
        for (size_t i = 0; i < players.size(); i++) {
            if (core->_players[i]._alive == false) {
                lively -= 1;
            }
            if (lively <= 1) {
                music.stop();
                window.close();
                std::cout << "GAME OVER!" << std::endl;// \nPlay Again?\nYES\t|\tNO\n";
                /*std::cin >> str;
                if (strcmp(str.c_str(), "YES") == 0) {
                    return (1);
                }*/
                return (0);
            }
        }
        lively = 4;
        camera3D.update();
        // Move player
        if (core->_players[0]._alive && nbPlayers > 0 && keyOrPad == 0) {
            if (players[0].getSpeed() != core->_players[0]._speed)
                players[0].setSpeed(core->_players[0]._speed);
            if (keyboard.isKeyDown(KEY_RIGHT)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], core->_players[0]._speed, 0, core->_players[0]._throughWalls)) {
                    players[0].moveRight();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("RIGHT", 1);
                }
            } else if (keyboard.isKeyDown(KEY_LEFT)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], -core->_players[0]._speed, 0, core->_players[0]._throughWalls)) {
                    players[0].mouveLeft(); // C'est volontaire
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("LEFT", 1);
                }
            } else if (keyboard.isKeyDown(KEY_DOWN)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], 0, core->_players[0]._speed, core->_players[0]._throughWalls)) {
                    players[0].moveDown();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("DOWN", 1);
                }
            } else if (keyboard.isKeyDown(KEY_UP)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], 0, -core->_players[0]._speed, core->_players[0]._throughWalls)) {
                    players[0].moveUp();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("UP", 1);
                }
            }
            if (keyboard.isKeyDown(KEY_SPACE)) {
                if (core->inputInterpretation("BOMB", 1) == 0) {
                    players[0].playSound("bomb_plant");
                    Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[0].useFunction("getBomb"));
                    if (bomb) {
                        bomb->setAvaliable(-1);
                        //bombs.push_back(Entities::Bomb(players[0].getPosition(), bombMod, animations, boom));
                    }
                }
            }
        } else if (core->_players[0]._alive && nbPlayers > 0 && keyOrPad == 1) {
            if (players[0].getSpeed() != core->_players[0]._speed)
                players[0].setSpeed(core->_players[0]._speed);
            if (gamepadJ1.getAxisMovement(0) > abs(gamepadJ1.getAxisMovement(1)) || gamepadJ1.isButtonDown(2)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], core->_players[0]._speed, 0, core->_players[0]._throughWalls)) {
                    players[0].moveRight();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("RIGHT", 1);
                }
            } else if (gamepadJ1.getAxisMovement(0) < -abs(gamepadJ1.getAxisMovement(1)) || gamepadJ1.isButtonDown(4)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], -core->_players[0]._speed, 0, core->_players[0]._throughWalls)) {
                    players[0].mouveLeft(); // C'est volontaire
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("LEFT", 1);
                }
            } else if (gamepadJ1.getAxisMovement(1) > abs(gamepadJ1.getAxisMovement(0)) || gamepadJ1.isButtonDown(3)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], 0, core->_players[0]._speed, core->_players[0]._throughWalls)) {
                    players[0].moveDown();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("DOWN", 1);
                }
            } else if (gamepadJ1.getAxisMovement(1) < -abs(gamepadJ1.getAxisMovement(0)) || gamepadJ1.isButtonDown(1)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[0], 0, -core->_players[0]._speed, core->_players[0]._throughWalls)) {
                    players[0].moveUp();
                    players[0].playSound("footstep");
                    players[0].animate("walk", 0);
                    core->inputInterpretation("UP", 1);
                }
            }
            if (gamepadJ1.isButtonDown(7)) {
                if (core->inputInterpretation("BOMB", 1) == 0) {
                    players[0].playSound("bomb_plant");
                    Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[0].useFunction("getBomb"));
                    if (bomb) {
                        bomb->setAvaliable(-1);
                        //.push_back(Entities::Bomb(players[0].getPosition(), bombMod, animations, boom));
                    }
                }
            }
        }
        if (core->_players[1]._alive && nbPlayers > 1) {
            if (players[1].getSpeed() != core->_players[1]._speed)
                players[1].setSpeed(core->_players[1]._speed);
            if (gamepadJ2.getAxisMovement(0) > abs(gamepadJ2.getAxisMovement(1)) || gamepadJ2.isButtonDown(2)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[1], core->_players[1]._speed, 0, core->_players[1]._throughWalls)) {
                    players[1].moveRight();
                    players[1].playSound("footstep");
                    players[1].animate("walk", 0);
                    core->inputInterpretation("RIGHT", 2);
                }
            } else if (gamepadJ2.getAxisMovement(0) < -abs(gamepadJ2.getAxisMovement(1)) || gamepadJ2.isButtonDown(4)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[1], -core->_players[1]._speed, 0, core->_players[1]._throughWalls)) {
                    players[1].mouveLeft(); // C'est volontaire
                    players[1].playSound("footstep");
                    players[1].animate("walk", 0);
                    core->inputInterpretation("LEFT", 2);
                }
            } else if (gamepadJ2.getAxisMovement(1) > abs(gamepadJ2.getAxisMovement(0)) || gamepadJ2.isButtonDown(3)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[1], 0, core->_players[1]._speed, core->_players[1]._throughWalls)) {
                    players[1].moveDown();
                    players[1].playSound("footstep");
                    players[1].animate("walk", 0);
                    core->inputInterpretation("DOWN", 2);
                }
            } else if (gamepadJ2.getAxisMovement(1) < -abs(gamepadJ2.getAxisMovement(0)) || gamepadJ2.isButtonDown(1)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[1], 0, -core->_players[1]._speed, core->_players[1]._throughWalls)) {
                    players[1].moveUp();
                    players[1].playSound("footstep");
                    players[1].animate("walk", 0);
                    core->inputInterpretation("UP", 2);
                }
            }
            if (gamepadJ2.isButtonDown(7)) {
                if (core->inputInterpretation("BOMB", 2) == 0) {
                    players[1].playSound("bomb_plant");
                    Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[1].useFunction("getBomb"));
                    if (bomb) {
                        bomb->setAvaliable(-1);
                        //bombs.push_back(Entities::Bomb(players[1].getPosition(), bombMod, animations, boom));
                    }
                }
            }
        }
        if (core->_players[2]._alive && nbPlayers > 2) {
            if (players[2].getSpeed() != core->_players[2]._speed)
                players[2].setSpeed(core->_players[2]._speed);
            if (gamepadJ3.getAxisMovement(0) > abs(gamepadJ3.getAxisMovement(1)) || gamepadJ3.isButtonDown(2)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[2], core->_players[2]._speed, 0, core->_players[2]._throughWalls)) {
                    players[2].moveRight();
                    players[2].playSound("footstep");
                    players[2].animate("walk", 0);
                    core->inputInterpretation("RIGHT", 3);
                }
            } else if (gamepadJ3.getAxisMovement(0) < -abs(gamepadJ3.getAxisMovement(1)) || gamepadJ3.isButtonDown(4)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[2], -core->_players[2]._speed, 0, core->_players[2]._throughWalls)) {
                    players[2].mouveLeft(); // C'est volontaire
                    players[2].playSound("footstep");
                    players[2].animate("walk", 0);
                    core->inputInterpretation("LEFT", 3);
                }
            } else if (gamepadJ3.getAxisMovement(1) > abs(gamepadJ3.getAxisMovement(0)) || gamepadJ3.isButtonDown(3)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[2], 0, core->_players[2]._speed, core->_players[2]._throughWalls)) {
                    players[2].moveDown();
                    players[2].playSound("footstep");
                    players[2].animate("walk", 0);
                    core->inputInterpretation("DOWN", 3);
                }
            } else if (gamepadJ3.getAxisMovement(1) < -abs(gamepadJ3.getAxisMovement(0)) || gamepadJ3.isButtonDown(1)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[2], 0, -core->_players[2]._speed, core->_players[2]._throughWalls)) {
                    players[2].moveUp();
                    players[2].playSound("footstep");
                    players[2].animate("walk", 0);
                    core->inputInterpretation("UP", 3);
                }
            }
            if (gamepadJ3.isButtonDown(7)) {
                if (core->inputInterpretation("BOMB", 3) == 0) {
                    players[2].playSound("bomb_plant");
                    Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[2].useFunction("getBomb"));
                    if (bomb) {
                        bomb->setAvaliable(-1);
                        //bombs.push_back(Entities::Bomb(players[2].getPosition(), bombMod, animations, boom));
                    }
                }
            }
        }
        if (core->_players[3]._alive && nbPlayers > 3) {
            if (players[3].getSpeed() != core->_players[3]._speed)
                players[3].setSpeed(core->_players[3]._speed);
            if (gamepadJ4.getAxisMovement(0) > abs(gamepadJ4.getAxisMovement(1)) || gamepadJ4.isButtonDown(2)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[3], core->_players[3]._speed, 0, core->_players[3]._throughWalls)) {
                    players[3].moveRight();
                    players[3].playSound("footstep");
                    players[3].animate("walk", 0);
                    core->inputInterpretation("RIGHT", 4);
                }
            } else if (gamepadJ4.getAxisMovement(0) < -abs(gamepadJ4.getAxisMovement(1)) || gamepadJ4.isButtonDown(4)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[3], -core->_players[1]._speed, 0, core->_players[3]._throughWalls)) {
                    players[3].mouveLeft(); // C'est volontaire
                    players[3].playSound("footstep");
                    players[3].animate("walk", 0);
                    core->inputInterpretation("LEFT", 4);
                }
            } else if (gamepadJ4.getAxisMovement(1) > abs(gamepadJ4.getAxisMovement(0)) || gamepadJ4.isButtonDown(3)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[3], 0, core->_players[3]._speed, core->_players[3]._throughWalls)) {
                    players[3].moveDown();
                    players[3].playSound("footstep");
                    players[3].animate("walk", 0);
                    core->inputInterpretation("DOWN", 4);
                }
            } else if (gamepadJ4.getAxisMovement(1) < -abs(gamepadJ4.getAxisMovement(0)) || gamepadJ4.isButtonDown(1)) {
                if (!collision(wallsPos, boxesPos, bombsPos, players[3], 0, -core->_players[3]._speed, core->_players[3]._throughWalls)) {
                    players[3].moveUp();
                    players[3].playSound("footstep");
                    players[3].animate("walk", 0);
                    core->inputInterpretation("UP", 4);
                }
            }
            if (gamepadJ4.isButtonDown(7)) {
                if (core->inputInterpretation("BOMB", 4) == 0) {
                    players[3].playSound("bomb_plant");
                    Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[3].useFunction("getBomb"));
                    if (bomb) {
                        bomb->setAvaliable(-1);
                        //bombs.push_back(Entities::Bomb(players[3].getPosition(), bombMod, animations, boom));
                    }
                }
            }
        }
        for (std::size_t i = nbPlayers; i < players.size(); i++) {
            if (players[i].getSpeed() != core->_players[i]._speed)
                players[i].setSpeed(core->_players[i]._speed);
            if (core->inputs[i].compare("RIGHT") == 0) {
                players[i].moveRight();
                players[i].playSound("footstep");
                players[i].animate("walk", 0);
            }
            if (core->inputs[i].compare("LEFT") == 0) {
                players[i].mouveLeft(); // C'est volontaire
                players[i].playSound("footstep");
                players[i].animate("walk", 0);
            }
            if (core->inputs[i].compare("DOWN") == 0) {
                players[i].moveDown();
                players[i].playSound("footstep");
                players[i].animate("walk", 0);
            }
            if (core->inputs[i].compare("UP") == 0) {
                players[i].moveUp();
                players[i].playSound("footstep");
                players[i].animate("walk", 0);
            }
            if (core->inputs[i].compare("BOMB") == 0) {
                Objects::Bomb *bomb = static_cast<Objects::Bomb *>(players[i].useFunction("getBomb"));
                if (bomb) {
                    bomb->setAvaliable(-1);
                    //bombs.push_back(Entities::Bomb(players[i].getPosition(), bombMod, animations, boom));
                }
                players[i].addingBomb();
                players[i].playSound("bomb_plant");
            }
            if (players[i].getBomb() > core->_players[i]._currentOfBombs) {
                players[i].removeBomb();
            }
        }
        core->getLoop();
        window.beginDraw();
        window.clearBackground(Raylib::Color(255, 255, 255, 255));
        camera3D.beginMode();
        boxes.clear();
        walls.clear();
        bombsPos.clear();
        bombs2Pos.clear();
        bombs3Pos.clear();
        wallsPos.clear();
        boxesPos.clear();
        for (std::size_t i = 0; i < core->_map.size(); i++) {
            for (std::size_t j = 0; j < core->_map[i].size(); j++) {
                if (core->_map[i][j] == 'B') {
                    bombsPos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1});
                    bombs2Pos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.5f, i * 2 - float(core->_map.size()) + 1});
                    bombs3Pos.push_back({j * 2 - float(core->_map[i].size()) + 1, 2.5f, i * 2 - float(core->_map.size()) + 1});
                }
                if (core->_map[i][j] == '#') {
                    wallsPos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1});
                }
                if (core->_map[i][j] == 'M') {
                    boxesPos.push_back({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1});
                }
                if (core->_map[i][j] == 'F') {
                    DrawSphere({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1}, 0.8f, Raylib::Color(230, 41, 55, 255));
                }
                if (core->_map[i][j] == 'N') {
                    DrawSphere({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1}, 0.8f, Raylib::Color(253, 249, 0, 255));
                }
                if (core->_map[i][j] == 'S') {
                    DrawSphere({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1}, 0.8f, Raylib::Color(0, 121, 241, 255));
                }
                if (core->_map[i][j] == 'W') {
                    DrawSphere({j * 2 - float(core->_map[i].size()) + 1, 1.0f, i * 2 - float(core->_map.size()) + 1}, 0.8f, Raylib::Color(200, 122, 255, 255));
                }
            }
        }
        for (std::size_t i = 0; i < boxesPos.size(); i++) {
            boxes.push_back(Entities::Wall(boxesPos[i], modelBox, animationsBox, boom, false));
        }
        playersPos.clear();
        if (!core->_players[0]._alive)
            playersPos.push_back({0, 0, 0});
        else
            playersPos.push_back({core->_players[0]._coord[0] * 2 - float(core->_map[0].size()) + 1, 1.0f, core->_players[0]._coord[1] * 2 - float(core->_map.size()) + 1});
        if (!core->_players[1]._alive)
            playersPos.push_back({0, 0, 0});
        else
            playersPos.push_back({core->_players[1]._coord[0] * 2 - float(core->_map[0].size()) + 1, 0.75f, core->_players[1]._coord[1] * 2 - float(core->_map.size()) + 1.25});
        if (!core->_players[2]._alive)
            playersPos.push_back({0, 0, 0});
        else
            playersPos.push_back({core->_players[2]._coord[0] * 2 - float(core->_map[0].size()) + 1, 1.0f, core->_players[2]._coord[1] * 2 - float(core->_map.size()) + 1});
        if (!core->_players[3]._alive)
            playersPos.push_back({0, 0, 0});
        else
            playersPos.push_back({core->_players[3]._coord[0] * 2 - float(core->_map[0].size()) + 1, 0.75f, core->_players[3]._coord[1] * 2 - float(core->_map.size()) + 0.75});
        for (std::size_t i = 0; i < wallsPos.size(); i++) {
            walls.push_back(Entities::Wall(wallsPos[i], wallModel,
                                           animationsBox, boom, false));
            //DrawCubeV(wallsPos[i], wallSize, Raylib::Color(130, 130, 130,
            //                                                255));
            //DrawCubeWiresV(wallsPos[i], wallSize, Raylib::Color(80, 80, 80,
            //                                                     255));
        }
        //boxes.draw();
        for (std::size_t i = 0; i < boxesPos.size(); i++) {
            boxes[i].draw();
            // DrawCubeV(boxesPos[i], boxSize, Raylib::Color(139, 69, 19, 255));
            // DrawCubeWiresV(boxesPos[i], boxSize, Raylib::Color(80, 80, 80,255));
        }
        for (std::size_t i = 0; i < wallsPos.size(); i++) {
            walls[i].draw();
        }
        for (std::size_t i = 0; i < bombsPos.size(); i++) {
            //bombs[i].draw();
            DrawSphere(bombsPos[i], 0.8f, Raylib::Color(80, 80, 80, 255));
            DrawCube(bombs2Pos[i], 0.1f, 1.95f, 0.1f, Raylib::Color(127, 106, 79, 255));
            DrawCube(bombs3Pos[i], 0.1f, 0.1f, 0.1f, Raylib::Color(230, 41, 55, 255));
            for (size_t j = 0; j < core->_currentBomb.size(); j++) {
                if (bombsPos[i].x == core->_currentBomb[j]._x * 2 - float(core->_map[0].size()) + 1 &&
                    bombsPos[i].z == core->_currentBomb[j]._y * 2 - float(core->_map.size()) + 1) {
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = end - core->_currentBomb[j]._start;
                    if (diff.count() > 2.95) {
                        bombRange = core->_currentBomb[j]._power;
                        //bombs[i].playSound("");
                        boom->play();
                        toDelete.push_back(i);
                        for (int k = 1; k < bombRange + 1; k++) {
                            if (core->_map[core->_currentBomb[j]._y][core->_currentBomb[j]._x + k] == '#' ||
                                core->_map[core->_currentBomb[j]._y][core->_currentBomb[j]._x + k] == 'M')
                                break;
                            DrawCubeV({bombsPos[i].x + k*2, bombsPos[i].y, bombsPos[i].z}, boxSize, Raylib::Color(230, 41, 55, 255));
                        }
                        for (int k = 1; k < bombRange + 1; k++) {
                            if (core->_map[core->_currentBomb[j]._y][core->_currentBomb[j]._x - k] == '#' ||
                                core->_map[core->_currentBomb[j]._y][core->_currentBomb[j]._x - k] == 'M')
                                break;
                            DrawCubeV({bombsPos[i].x - k*2, bombsPos[i].y, bombsPos[i].z}, boxSize, Raylib::Color(230, 41, 55, 255));
                        }
                        for (int k = 1; k < bombRange + 1; k++) {
                            if (core->_map[core->_currentBomb[j]._y + k][core->_currentBomb[j]._x] == '#' ||
                                core->_map[core->_currentBomb[j]._y + k][core->_currentBomb[j]._x] == 'M')
                                break;
                            DrawCubeV({bombsPos[i].x, bombsPos[i].y, bombsPos[i].z + k*2}, boxSize, Raylib::Color(230, 41, 55, 255));
                        }
                        for (int k = 1; k < bombRange + 1; k++) {
                            if (core->_map[core->_currentBomb[j]._y - k][core->_currentBomb[j]._x] == '#' ||
                                core->_map[core->_currentBomb[j]._y - k][core->_currentBomb[j]._x] == 'M')
                                break;
                            DrawCubeV({bombsPos[i].x, bombsPos[i].y, bombsPos[i].z - k*2}, boxSize, Raylib::Color(230, 41, 55, 255));
                        }
                    }
                }
            }
        }
        /*while (!toDelete.empty()) {
            bombs.erase(bombs.begin() + toDelete[0]);
            toDelete.pop_back();
        }*/
        for (std::size_t i = 0; i < playersPos.size(); i++) {
            if (core->_players[i]._alive) {
                players[i].draw();
                // DrawCubeV(players[i].getPosition(), playerSize, playersColor[i]);
                // DrawCubeWiresV(players[i].getPosition(), playerSize, Raylib::Color(80, 80, 80, 255));
            }
        }
        camera3D.endMode();
        window.drawFPSOnScreen(10, 10);
        window.endDraw();
    }
    // if (bombs.size() > 0) {
    //     std::cout << "Salut" << std::endl;
    //     bombs[0].playSound("");
    // }
    music.stop();
    sleep(2);
    window.close();
    return (0);
}

int main(void)
{
    while (bomberman(1, 0) == 1);
    for (size_t i = 0; i < myThreads.size(); i++) {
        myThreads[i].join();
    }
    return 0;
}
