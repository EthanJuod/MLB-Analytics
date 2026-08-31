/**
 * @file Elevator.h
 * @author Ethan Juodawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ELEVATOR_H
#define CANADIANEXPERIENCE_ELEVATOR_H
#include "Component.h"
#include "IRotationSink.h"
#include "PhysicsPolygon.h"

/**
 * Elevator that raises or lowers components
 */
class Elevator : public Component, public IRotationSink
{
private:
    /// Physics Polygon for Elevator
    cse335::PhysicsPolygon mPolygon;
    /// Position of elevator
    wxPoint2DDouble mPosition;
    /// Speed of elevator
    double mSpeed = 0.0;
    /// starting Y position
    double mStartY = 0.0;
public:

    Elevator();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Update(double elapsed) override;

    void Rectangle(double x, double y, double width, double height);

    void SetImage(std::wstring filename);

    void SetPosition(double x, double y);

    /**
     * Get the position of the elevator
     * @return Position of the elevator
     */
    wxPoint2DDouble GetPosition() const { return mPosition; }

    void Rotate(double rotation, double speed) override;

    /**
     * Get the elevator's physics body
     * @return Pointer to the Box2D body
     */
    b2Body* GetBody() { return mPolygon.GetBody(); }

};


#endif //CANADIANEXPERIENCE_ELEVATOR_H