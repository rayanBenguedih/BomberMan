/*
** EPITECH PROJECT, 2022
** Bomb.hpp
** File description:
** File containing the bomb entitie and objects
*/

#ifndef BOMBS
#define BOMBS

#include "Objects.hpp"
#include "Entities.hpp"
#include <map>
#include <string>
#include <vector>

namespace Objects {
    class Bomb : public Objects {
        private:
            std::size_t _range = 2;
        public:
//-----------------------------Getter------------------------------------------
            std::size_t getRange(void) const;
//------------------------------Setter-----------------------------------------
            void setRange(int);
            void setStack(int);
            void setAvaliable(int);
    };
}

namespace Entities {
    class Bomb : public IEntities {
        private:
            clock_t _start;
            Vector3 _position;
            std::shared_ptr<Raylib::Model> _model;
            std::map<std::string, ModelAnimation> _animations;
            std::string _loadedAnimation = "";
            std::shared_ptr<Raylib::Sound> _sound;
            Objects::Bomb _bomb;

        public:
            Bomb(Vector3 pos,
                std::shared_ptr<Raylib::Model> model,
                std::map<std::string, ModelAnimation> animations,
                std::shared_ptr<Raylib::Sound> sound);

//-----------------------------Getter------------------------------------------
            Vector3 getPosition(void) const;
            std::size_t getStack(void) const;
            std::size_t getRange(void) const;
            std::size_t getAvaliable(void) const;
            BoundingBox getSize(void);
            clock_t getTiming(void) const;
//------------------------------Setter-----------------------------------------
            void setPosition(float x, float y, float z);
            void setPosition(Vector3);
            void setRange(int);
            void setStack(int);
            void setAvaliable(int);
//----------------------------Functions----------------------------------------
            void playSound(std::string);
            void animate(std::string animation, int frame);
            void draw(void);
            void setTexture(std::string);
            void animate(std::string animation, std::size_t animationNb);
    };
}

#endif
