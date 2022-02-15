#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <memory>
#include <unordered_set>

#include "math/math.h"
#include "PhysicsObject.h"

namespace slr {
    using ObjectPtr = std::shared_ptr<PhysicsObject>;

    const float DEFAULT_GRAV_CONST = 1e4f;

    class PhysicsWorld {
    public:
        explicit PhysicsWorld(float gravConst = DEFAULT_GRAV_CONST) : mObjects(), mGravConst(gravConst) {}

        void CreateObject(ObjectPtr object);

        void DeleteObject(ObjectPtr object);

        [[nodiscard]] float GetGravConst() const { return mGravConst; }

        void GetGravConst(float gravConst) { mGravConst = gravConst; }

        void Step(float dt);

        auto& GetObjects() const { return mObjects; }

    private:
        std::unordered_set<ObjectPtr> mObjects;
        float                         mGravConst;

        [[nodiscard]] Vec3f GetNetForce(ObjectPtr obj);
    };
}

#endif