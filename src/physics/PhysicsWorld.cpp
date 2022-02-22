#include <cmath>

#include "physics/PhysicsWorld.h"

namespace slr {
    void PhysicsWorld::CreateObject(ObjectPtr object) {
        mObjects.insert(object);
    }

    void PhysicsWorld::DeleteObject(ObjectPtr object) {
        mObjects.erase(object);
    }

    Vec3f PhysicsWorld::GetNBodyGravForce(float m1, float m2, const Vec3f& pos1, const Vec3f& pos2) {
        const auto gamma = 1e4f;

        return -gamma * m1 * m2 * (pos1 - pos2) / std::pow((pos1 - pos2).norm(), 3);
    }

    Vec3f PhysicsWorld::GetNetForce(ObjectPtr obj) {
        Vec3f netForce{};
        for (auto& obj1: mObjects) {
            if (obj != obj1) {
                netForce = netForce + GetNBodyGravForce(obj->GetMass(), obj1->GetMass(),
                                                        obj->GetPosition(), obj1->GetPosition());
            }
        }
        return netForce;
    }

    Vec3f PhysicsWorld::GetNetForce(ObjectPtr obj, std::size_t i) {
        Vec3f netForce{};
        for (auto& obj1: mObjects) {
            if (obj != obj1) {
                netForce = netForce + GetNBodyGravForce(obj->GetMass(), obj1->GetMass(),
                                                        obj->GetSimulatedPos()[i], obj1->GetSimulatedPos()[i]);
            }
        }
        return netForce;
    }

    void PhysicsWorld::Step(float dt) {
        for (auto& obj: mObjects) {
            obj->SetForce(GetNetForce(obj));
            obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
        }

        for (auto& obj : mObjects) {
            obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);
        }
    }

    void PhysicsWorld::SimulateNSeconds(float seconds, float dt) {
        auto N = static_cast<uint64_t>(seconds / dt);
        for (auto& obj : mObjects) {
            obj->GetSimulatedPos().resize(N);
            obj->GetSimulatedPos()[0] = obj->GetPosition();

            obj->GetSimulatedVel().resize(N);
            obj->GetSimulatedVel()[0] = obj->GetVelocity();
        }

        for (std::size_t i = 0; i < N - 1; ++i) {
            for (auto& obj: mObjects) {
                obj->SetForce(GetNetForce(obj, i));
                obj->GetSimulatedVel()[i + 1] = obj->GetSimulatedVel()[i] + obj->GetForce() / obj->GetMass() * dt;
            }

            for (auto& obj: mObjects) {
                obj->GetSimulatedPos()[i + 1] = obj->GetSimulatedPos()[i] + obj->GetSimulatedVel()[i + 1] * dt;
            }
        }
    }
}
