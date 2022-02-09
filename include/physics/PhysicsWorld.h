#include <memory>
#include <unordered_set>

#include "math/math.h"
#include "Object.h"

class PhysicsWorld {
    public:
        PhysicsWorld(const Vec3f& gravity) : mObjects(), mGravity(gravity) { } 

        ~PhysicsWorld() noexcept = default;

        void AddObject(std::unique_ptr<Object> object);
        void DeleteObject(std::unique_ptr<Object> object);

        Vec3f GetGravity() const { return mGravity; }
        void SetGravity(const Vec3f& vec) { mGravity = vec; }

        void Step(float dt);

        auto &GetObjects() const { return mObjects; }

    private:
        std::unordered_set<std::unique_ptr<Object>> mObjects;
        Vec3f mGravity;
};
