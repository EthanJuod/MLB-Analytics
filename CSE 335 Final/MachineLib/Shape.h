/**
 * @file Shape.h
 * @author Ethan Juodawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "IRotationSink.h"

/**
 * Shape class to create movable shpaes
 */
class Shape : public Component, public IRotationSink
{
private:
    /// Physics polygon for shape
    cse335::PhysicsPolygon mPolygon;
    /// Rotation set to shape
    double mRotation = 0;
    /// Spped of shape
    double mSpeed = 0;

public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Rectangle(double x, double y, double width, double height);
    void Circle(double radius);
    void AddPoint(double x, double y);
    void SetImage(std::wstring filename);
    void SetInitialPosition(double x, double y);
    void SetInitialRotation(double rad);
    void SetDynamic();
    void SetKinematic();
    void SetPhysics(double density, double friction, double restitution);

    /**
     * Getter for Polygon
     * @return mPolygon
     */
    cse335::PhysicsPolygon* GetPolygon() { return &mPolygon; }

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Rotate(double rotation, double speed) override;

    void BottomCenteredRectangle(double x, double y);

};


#endif //CANADIANEXPERIENCE_SHAPE_H