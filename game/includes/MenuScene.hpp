#pragma once

#include "../../engine/includes/Scenes/IScene.hpp"
#include <memory>

namespace Bomberman {
    namespace Scenes {
        class MenuScene : public Engine::IScene {
        public:
            // Ctor
            MenuScene() = default;

            // Dtor
            virtual ~MenuScene() = default;

            // Member functions
            void initialize(void) override;
            void update(void) override;
            void clear(void) override;

        private:
            // Objects

        };
    }
}