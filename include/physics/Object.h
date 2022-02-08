#include "math/math.h"

class Object {
    public:
        Object(Vec3f pos, Vec3f vel, float mass) :
            mPosition(pos), mVelocity(vel), mForce(Vec3f()), mMass(mass) {}

        Vec3f GetPosition() const { return mPosition; } 
        Vec3f GetVelocity() const { return mVelocity; } 
        Vec3f GetForce() const { return mForce; } 
        float GetMass() const { return mMass; }

        void SetPosition(const Vec3f& vec) { mPosition = vec; }
        void SetVelocity(const Vec3f& vec) { mVelocity = vec; }
        void SetForce(const Vec3f& vec) { mForce = vec; }

        ~Object() noexcept = default;

    private:
        Vec3f mPosition;
        Vec3f mVelocity;
        Vec3f mForce;
        float mMass;
}; 
