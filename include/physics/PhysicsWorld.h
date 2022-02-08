#include <memory>
#include <vector>

#include "math/math.h"
#include "Object.h"

class PhysicsWorld {
    public:
        PhysicsWorld(const Vec3f& gravity) : mGravity(gravity) { } 

        ~PhysicsWorld() noexcept = default;

        void AddObject(const std::unique_ptr<Object> object);
        void DeleteObject(const std::unique_ptr<Object> object);

        Vec3f GetGravity() const { return mGravity; }
        void SetGravity(const Vec3f& vec) { mGravity = vec; }

        void Step(float dt);

    private:
        std::vector<std::unique_ptr<Object>> mObjects;
        const Vec3f mGravity;
};
