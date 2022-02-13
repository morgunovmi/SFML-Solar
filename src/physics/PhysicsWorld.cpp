#include <cmath>

#include "physics/PhysicsWorld.h"

namespace slr {
    void PhysicsWorld::CreateObject(ObjectPtr object) {
        mObjects.insert(std::move(object));
    }

    void PhysicsWorld::DeleteObject(ObjectPtr object) {
        mObjects.erase(object);
    }

    Vec3f GetNBodyGravForce(float m1, float m2, const Vec3f& pos1, const Vec3f& pos2) {
        const auto gamma = 1e4f;

        return -gamma * m1 * m2 * (pos1 - pos2) / std::pow((pos1 - pos2).norm(), 3);
    }

    Vec3f PhysicsWorld::GetNetForce(const ObjectPtr& obj) {
        Vec3f netForce{};
        for (auto& obj1: mObjects) {
            if (obj != obj1) {
                netForce = netForce + GetNBodyGravForce(obj->GetMass(), obj1->GetMass(),
                                                        obj->GetPosition(), obj1->GetPosition());
            }
        }

        return netForce;
    }

    void PhysicsWorld::Step(float dt) {
        for (auto& obj: mObjects) {
            auto forceOld = GetNetForce(obj);
            obj->SetForce(forceOld);
            obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
        }

        for (auto& obj : mObjects) {
            obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);
        }
    }
}
