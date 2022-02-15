#ifndef SOLAR_ENTITY_H
#define SOLAR_ENTITY_H

#include <memory>
#include <string_view>
#include <fmt/format.h>

#include <SFML/Graphics.hpp>

#include "physics/PhysicsObject.h"

namespace slr {
    class Entity : public sf::Sprite {
    public:
        Entity(const sf::Vector2f& pos, const sf::Texture& texture) : mPhysicsObject(),
                                                                        mTrail(),
                                                                        mDebug(true) {
            setTexture(texture);
            setPosition(pos);
            const auto rect = getTextureRect();
            setOrigin(static_cast<float>(rect.width) / 2,
                      static_cast<float>(rect.height) / 2);
        }

        void Simulate(float seconds);

        [[nodiscard]] std::shared_ptr<PhysicsObject> GetPhysicsObject() const { return mPhysicsObject; }
        void SetPhycicsObject(std::shared_ptr<PhysicsObject> physicsObject) { mPhysicsObject = physicsObject; }

        [[nodiscard]] std::vector<sf::Vertex> GetTrail() const { return mTrail; }

        void AddTrailPoint(const sf::Vertex& vertex) {
            mTrail.push_back(vertex);
        }

        [[nodiscard]] bool GetDebug() const { return mDebug; }
        void SetDebug(bool val) { mDebug = val; }

    private:
        std::shared_ptr<PhysicsObject> mPhysicsObject;
        std::vector<sf::Vertex> mTrail;

        bool mDebug;
    };
}

#endif //SOLAR_ENTITY_H
