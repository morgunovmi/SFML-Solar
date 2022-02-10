#include <cmath>

#include "physics/PhysicsWorld.h"

void PhysicsWorld::AddObject(std::unique_ptr<Object> object) {
    mObjects.insert(std::move(object));
}

void PhysicsWorld::DeleteObject(std::unique_ptr<Object> object) {
    mObjects.erase(object);
}

Vec3f GetGravitationalForce(float mass, Vec3f position) {
    const auto gamma = 1e8f; 

    return -gamma * mass * position / std::pow(position.norm(), 3); 
}

void PhysicsWorld::Step(float dt) {
    for (auto & obj : mObjects) {
        obj->SetForce(GetGravitationalForce(obj->GetMass(), obj->GetPosition()));
        //obj->SetForce(obj->GetForce() + mGravity * obj->GetMass());

        obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
        obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);

        obj->SetForce(Vec3f());
    }
}
