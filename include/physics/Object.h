#include "math/math.h"

class Object {
    public:
        Object(const Vec3f& pos, const Vec3f& vel, float mass) :
            mPosition(pos), mVelocity(vel), mForce(Vec3f()), mMass(mass) {}

        [[nodiscard]] Vec3f GetPosition() const { return mPosition; }
        [[nodiscard]] Vec3f GetVelocity() const { return mVelocity; }
        [[nodiscard]] Vec3f GetForce() const { return mForce; }
        [[nodiscard]] float GetMass() const { return mMass; }

        void SetPosition(const Vec3f& vec) { mPosition = vec; }
        void SetVelocity(const Vec3f& vec) { mVelocity = vec; }
        void SetForce(const Vec3f& vec) { mForce = vec; }

    private:
        Vec3f mPosition;
        Vec3f mVelocity;
        Vec3f mForce;
        float mMass;
}; 
