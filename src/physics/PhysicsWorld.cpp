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
        const auto gamma = 1e6f;

        return -gamma * m1 * m2 * (pos1 - pos2) / std::pow((pos1 - pos2).norm(), 3);
    }

    Vec3f PhysicsWorld::GetNetForce(const ObjectPtr& obj) {
        Vec3f netForce{};
        /*for (auto& obj1: mObjects) {
            if (obj != obj1) {
                netForce = netForce + GetNBodyGravForce(obj->GetMass(), obj1->GetMass(),
                                               obj->GetPosition(), obj1->GetPosition());
            }
        }*/
        netForce = GetGravitationalForce(10000.f, obj->GetPosition());

        return netForce;
    }

    void PhysicsWorld::Step(float dt) {
        for (auto& obj: mObjects) {
            /*
            const auto netForce = GetNetForce(obj);
            std::array<float, 4> curState = {obj->GetPosition().x, obj->GetVelocity().x, obj->GetPosition().y, obj->GetVelocity().y};

            auto dxdy = [&](float t, auto init){ return std::array<float, 4>{init[1], netForce.x / obj->GetMass(), init[3], netForce.y / obj->GetMass()};};

            const auto nextState = ExplEulerSolver<2>::Solve(0, curState, dt, dxdy);

            obj->SetVelocity(Vec3f{ nextState[1], nextState[3], 0});
            obj->SetPosition(Vec3f{ nextState[0], nextState[2], 0});

            obj->SetForce(Vec3f());
             */


            obj->SetForce(GetGravitationalForce(10000.f, obj->GetPosition()));
            //obj->SetForce(obj->GetForce() + mGravity * obj->GetMass());

            obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
            obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);

            obj->SetForce(Vec3f());
        }
    }
}