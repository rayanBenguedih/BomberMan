/*
** EPITECH PROJECT, 2022
** Window.hpp
** File description:
** Player class
*/

#ifndef PLAYER
#define PLAYER

#include "Entities.hpp"
#include "Objects.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace Entities {
    class Player : public IEntities {
        private:
            Vector3 _position = {0.0f, 0.0f, 0.0f};
            Vector3 _size = {0.0f, 0.0f, 0.0f};
            Vector3 _rotationAxis = {1.0f, 0.0f, 0.0f};
            float _speed = 1.0f;
            std::map<std::string, ModelAnimation> _animations;
            int _animFrameCounter = 0;
            const std::map<std::string, void *(*)(Entities::Player *)> _functions;
            const std::map<std::string, std::shared_ptr<Raylib::Sound>> _sounds;
            std::map<std::string, Objects::Objects *> _objects;
            Raylib::Model *_model;
            std::string _loadedAnimation = "";
            float _direction = -90.0f;
            int _currentBomb = 0;
        public:
            // Dtor
            Player(Raylib::Model *model,
                std::map<std::string, ModelAnimation> animations,
                std::map<std::string, void *(*)(Entities::Player *)> functions,
                std::map<std::string, Objects::Objects *> objects,
                std::map<std::string, std::shared_ptr<Raylib::Sound>> sounds,
                float direction);

//--------------------------Getter---------------------------------------------
            Vector3 getPosition(void) const;
            float getSpeed(void) const;
            Vector3 getSizeMax(void);
            BoundingBox getSize(void);
            int getBomb(void) const;
            Objects::Objects *getObject(std::string);
//--------------------------Setter---------------------------------------------
            void setTexture(std::string);
            void setPosition(float x, float y, float z);
            void setPosition(Vector3);
            void setSpeed(float);
            void addingBomb(void);
            void removeBomb(void);
//-------------------------−Functions-----------------------------------------
            void moveUp(void);
            void moveDown(void);
            void mouveLeft(void);
            void moveRight(void);
            void playSound(std::string);
            void *useFunction(std::string);
            void draw(void);
            void animate(std::string animation, std::size_t animationNb);
    };
}

#endif
