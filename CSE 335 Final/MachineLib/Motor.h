/**
 * @file Motor.h
 * @author Ethan Juodawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MOTOR_H
#define CANADIANEXPERIENCE_MOTOR_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"

/**
 * Motor class for creating motion
 */
class Motor : public Component , public b2ContactListener
{
private:
    /// Physics Polygon for motor box
    cse335::PhysicsPolygon mBox;
    /// Polygon for wheel of motor
    cse335::Polygon mWheel;
    /// vector of Polygons for motor
    cse335::Polygon mMotors[5];
    /// String of Image directory
    std::wstring mImagesDir;
    /// Is the motor active now
    bool mIsActive = false;
    /// If the motor is active to start
    bool mInitiallyActive = false;
    /// Motor Speed
    double mSpeed = 1.0;
    /// Position of motor box
    wxPoint2DDouble mPosition;
    /// amount of rotation
    double mRotation = 0.0;
    /// Rotation source for this component
    RotationSource mSource;
    /// Is this motor oscillating?
    bool mOscillating = false;
    /// Maximum oscillation spread
    double mSpread = 0.1;
    /// Windup to launch speed ratio
    double mWindupToReleaseRatio = 5.0;
    /// direction of oscillation
    bool mOscillationWindup = true;
    /// phase of windup or forward
    double mOscillationPhase = mSpread;



public:
    /// Constructor
    Motor(std::wstring imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetPosition(double x, double y);

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Update(double elapsed) override;
    /**
     * Set if the motor is initially active
     * @param active True if initially active
     */
    void SetInitiallyActive(bool active) { mInitiallyActive = active; mIsActive = active; }
    /**
     * Set the motor speed
     * @param speed Speed value (rotations per second, negative for counter-clockwise)
     */
    void SetSpeed(double speed) { mSpeed = speed; }

    void BeginContact(b2Contact *contact) override;

    /**
     * Get the motor's physics body
     * @return Pointer to the Box2D body
     */
    b2Body* GetBody() { return mBox.GetBody(); }

    void RegisterContactListener(std::shared_ptr<ContactListener> contactListener) override;

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    wxPoint2DDouble GetShaftPosition();

    /**
     * Set if the motor should oscillate
     * @param oscillating True if motor should oscillate
     */
    void SetOscillating(bool oscillating) { mOscillating = oscillating; }

    /**
     * Set the maximum oscillation spread
     * @param spread Maximum spread (in rotations)
     */
    void SetSpread(double spread) { mSpread = spread; }

    /**
     * Set the windup to release speed ratio
     * @param ratio Ratio (higher = slower windup, faster release)
     */
    void SetWindupToReleaseRatio(double ratio) { mWindupToReleaseRatio = ratio; }

    void Reset() override;

};


#endif //CANADIANEXPERIENCE_MOTOR_H