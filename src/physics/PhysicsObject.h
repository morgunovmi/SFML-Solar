#ifndef OBJECT_H
#define OBJECT_H

#include "math/math.h"

namespace slr {
    class PhysicsObject {
    public:
        PhysicsObject(const Vec3f& pos, const Vec3f& vel, float mass) :
                mPosition(pos), mVelocity(vel), mForce(Vec3f()), mMass(mass) {}

        [[nodiscard]] Vec3f GetPosition() const { return mPosition; }

        [[nodiscard]] Vec3f GetVelocity() const { return mVelocity; }

        [[nodiscard]] Vec3f GetForce() const { return mForce; }

        [[nodiscard]] float GetMass() const { return mMass; }

        void SetPosition(const Vec3f& vec) { mPosition = vec; }

        void SetVelocity(const Vec3f& vec) { mVelocity = vec; }

        void SetForce(const Vec3f& vec) { mForce = vec; }

        [[nodiscard]] std::vector<Vec3f>& GetSimulatedPos() { return mSimulatedPos; }
        [[nodiscard]] std::vector<Vec3f>& GetSimulatedVel() { return mSimulatedVel; }

    private:
        Vec3f               mPosition;
        Vec3f               mVelocity;
        Vec3f               mForce;
        float               mMass;

    private:
        std::vector<Vec3f>  mSimulatedPos;
        std::vector<Vec3f>  mSimulatedVel;
    };
}

#endif