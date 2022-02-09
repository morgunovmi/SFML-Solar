#include "physics/PhysicsWorld.h"

void PhysicsWorld::AddObject(std::unique_ptr<Object> object) {
    mObjects.insert(std::move(object));
}

void PhysicsWorld::DeleteObject(std::unique_ptr<Object> object) {
    mObjects.erase(object);
}

void PhysicsWorld::Step(float dt) {
    for (auto & obj : mObjects) {
        obj->SetForce(obj->GetForce() + mGravity * obj->GetMass());

        obj->SetVelocity(obj->GetVelocity() + obj->GetForce() / obj->GetMass() * dt);
        obj->SetPosition(obj->GetPosition() + obj->GetVelocity() * dt);

        obj->SetForce(Vec3f());
    }
}
