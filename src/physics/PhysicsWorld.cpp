#include <cmath>

#include "physics/PhysicsWorld.h"
#include "physics/RKSolver.h"
#include "physics/ExplEulerSolver.h"

namespace slr {
    void PhysicsWorld::CreateObject(ObjectPtr object) {
        mObjects.insert(std::move(object));
    }

    void PhysicsWorld::DeleteObject(ObjectPtr object) {
        mObjects.erase(object);
    }

    Vec3f GetGravitationalForce(float mass, const Vec3f& position) {
        const auto gamma = 1e8f;

        return -gamma * mass * position / std::pow(position.norm(), 3);
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
            const auto netForce = GetNetForce(obj);
            std::array<float, 4> init = {obj->GetPosition().x, obj->GetVelocity().x, obj->GetPosition().y, obj->GetVelocity().y};

            auto dxdy = [&](auto init){ return std::array<float, 4>{init[1], netForce.x / obj->GetMass(), init[3], netForce.y / obj->GetMass()};};

            const auto res =  RKSolver<2>::Solve(init, dt, dxdy);

            obj->SetVelocity(Vec3f{ res[1], res[3], 0});
            obj->SetPosition(Vec3f{ res[0], res[2], 0});

            obj->SetForce(Vec3f());
        }
    }
}