#include "physics/PhysicsWorld.h"

void PhysicsWorld::AddObject(const std::unique_ptr<Object> object) {
    mObjects.push_back(object);
}

void PhysicsWorld::DeleteObject(const std::unique_ptr<Object> object) {
    mObjects.erase(std::find(mObjects.begin(), mObjects.end(), object));
}

void PhysicsWorld::Step(float dt) {
    for (auto & obj : mObjects) {
        obj->mForce += obj->mMass * mGravity;

        obj->mVelocity += obj->mForce / obj->mMass * dt;
        obj->mPosition += obj->mVelocity * dt;

        obj->mForce = Vec3f();
    }
}
