#include <memory>
#include <unordered_set>

#include "math/math.h"
#include "Object.h"

using ObjectPtr = std::unique_ptr<Object>;

class PhysicsWorld {
    public:
        explicit PhysicsWorld(const Vec3f& gravity) : mObjects(), mGravity(gravity) { }

        void CreateObject(ObjectPtr object);
        void DeleteObject(ObjectPtr object);

        [[nodiscard]] Vec3f GetGravity() const { return mGravity; }
        void SetGravity(const Vec3f& vec) { mGravity = vec; }

        void Step(float dt);

        auto &GetObjects() const { return mObjects; }

    private:
        std::unordered_set<ObjectPtr> mObjects;
        Vec3f mGravity;
};
