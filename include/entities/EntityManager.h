#ifndef SOLAR_ENTITYMANAGER_H
#define SOLAR_ENTITYMANAGER_H

#include <unordered_set>
#include <memory>

#include "Entity.h"
#include "physics/PhysicsWorld.h"

namespace slr {
    class EntityManager {
    public:
        EntityManager() : mEntities(), mPhysicsWorld() {}

        void CreateEntity(const sf::Vector2f& pos,
                          const sf::Vector2f& vel, float mass, const sf::Texture& texture);

        void DestroyEntity(std::shared_ptr<Entity> entity);

        void Update(float dt);

        void Draw(sf::RenderWindow& window) const;

    private:
        std::unordered_set<std::shared_ptr<Entity>> mEntities;
        PhysicsWorld                                mPhysicsWorld;
    };
}

#endif //SOLAR_ENTITYMANAGER_H
