/*
** EPITECH PROJECT, 2022
** Wall.hpp
** File description:
** File containing the wall entitie
*/

#ifndef WALLS
#define WALLS

#include "Objects.hpp"
#include "Entities.hpp"
#include <map>
#include <string>
#include <vector>

namespace Entities {
    class Wall : public IEntities {
        private:
            Vector3 _position;
            std::shared_ptr<Raylib::Model> _model;
            std::map<std::string, ModelAnimation> _animations;
            std::shared_ptr<Raylib::Sound> _sound;
            bool _breackable;
            std::string _loadedAnimation = "";
        public:
            Wall(Vector3 pos,
                std::shared_ptr<Raylib::Model> model,
                std::map<std::string, ModelAnimation> animations,
                std::shared_ptr<Raylib::Sound> sound,
                bool breakable);

//-----------------------------Getter------------------------------------------
            Vector3 getPosition(void) const;
            BoundingBox getSize(void);
//------------------------------Setter-----------------------------------------
            void setTexture(std::string);
            void setPosition(float x, float y, float z);
            void setPosition(Vector3);
//----------------------------Functions----------------------------------------
            void playSound(std::string);
            void animate(std::string animation, std::size_t frame);
            void draw(void);
    };
}

#endif
