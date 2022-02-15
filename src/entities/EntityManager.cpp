#include "entities/EntityManager.h"

#include <fmt/format.h>

namespace slr {
    void EntityManager::CreateEntity(const sf::Vector2f& pos,
                                     const sf::Vector2f& vel, float mass, const sf::Texture& texture) {

        auto entity = std::make_shared<Entity>(pos, texture);
        auto physicsObject = std::make_shared<PhysicsObject>(Vec3f{pos.x, pos.y, 0},
                                                                   Vec3f{vel.x, vel.y, 0}, mass);

        entity->SetPhycicsObject(physicsObject);
        mPhysicsWorld.CreateObject(physicsObject);
        mEntities.insert(entity);
    }

    void EntityManager::DestroyEntity(std::shared_ptr<Entity> entity) {
        mPhysicsWorld.DeleteObject(entity->GetPhysicsObject());
        mEntities.erase(entity);
    }

    void EntityManager::Update(float dt) {
        mPhysicsWorld.Step(dt);
        for (auto& ent : mEntities) {
            const auto newPos = ent->GetPhysicsObject()->GetPosition();
            ent->setPosition(newPos.x, newPos.y);

            ent->AddTrailPoint(sf::Vertex{sf::Vector2f{newPos.x, newPos.y}});
        }
    }

    void EntityManager::Draw(sf::RenderWindow& window) const {
        for (auto& ent : mEntities) {
            window.draw(*ent);
            auto trail = ent->GetTrail();
            window.draw(&trail[0], trail.size(), sf::Points);
        }
    }
}
