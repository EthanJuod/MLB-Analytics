/**
 * @file Conveyor.h
 * @author Ethan Judawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CONVEYER_H
#define CANADIANEXPERIENCE_CONVEYER_H
#include "IRotationSink.h"
#include "PhysicsPolygon.h"
#include "Shape.h"

/**
 * Converyer that moves compenents along it
 */
class Conveyor : public Component, public IRotationSink, public ContactListener
{
private:
    /// Physics Polygon for conveyor
    cse335::PhysicsPolygon mPolygon;
    /// Speed
    double mSpeed = 0;
    /// Postition
    wxPoint2DDouble mPosition;

public:

    Conveyor(std::wstring imageDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void RegisterContactListener(std::shared_ptr<ContactListener> contactListener) override;

    void Update(double elapsed) override;

    void SetPosition(double x, double y);

    wxPoint2DDouble GetShaftPosition();

    void Rotate(double rotation, double speed) override;

    /**
     * Get the Conveyer's physics body
     * @return Pointer to the Box2D body
     */
    b2Body* GetBody() { return mPolygon.GetBody(); }

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    };


#endif //CANADIANEXPERIENCE_CONVEYER_H