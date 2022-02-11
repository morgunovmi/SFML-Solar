#include <cmath>

#include "physics/PhysicsWorld.h"

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

void PhysicsWorld::Step(float dt) {
    for (auto & obj : mObjects) {
        for (auto & obj1 : mObjects) {
            if (obj != obj1) {
                obj->SetForce(obj->GetForce() + GetNBodyGravForce(obj->GetMass(), obj1->GetMass(),
                            obj->GetPosition(), obj1->GetPosition()));
            }
        }
        //obj->SetForce(obj->GetForce() + mGravity * obj->GetMass());

        obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
        obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);

        obj->SetForce(Vec3f());
    }
}
