#ifndef SOLAR_ENTITYMANAGER_H
#define SOLAR_ENTITYMANAGER_H

#include <unordered_set>
#include <memory>

#include "Entity.h"
#include "physics/PhysicsWorld.h"
#include "frontend/RendererEnums.h"
#include "misc/Log.h"

namespace slr {
    class EntityManager {
    public:
        explicit EntityManager(std::array<sf::Texture, 1>& textures, Log& appLog) : mEntities(), mTextures(textures),
                                                                                mPhysicsWorld(), mAppLog(appLog) {}

        void CreateEntity(const sf::Vector2f& pos,
                          const sf::Vector2f& vel, float mass, TextureName textureName);

        void DestroyEntity(std::shared_ptr<Entity> entity);

        void Update(float dt);

        void Draw(sf::RenderWindow& window) const;

    private:
        std::unordered_set<std::shared_ptr<Entity>> mEntities;
        std::array<sf::Texture, 1>&                 mTextures;

        PhysicsWorld                                mPhysicsWorld;

        Log&                                        mAppLog;
    };
}

#endif //SOLAR_ENTITYMANAGER_H
