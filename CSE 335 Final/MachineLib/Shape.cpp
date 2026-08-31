/**
 * @file Shape.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "Shape.h"

/**
 * Draw the shape by drawing its underlying PhysicsPolygon.
 * @param graphics The graphics context used for drawing.
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Create a rectangular polygon shape.
 * @param x X position of rectangle corner.
 * @param y Y position of rectangle corner.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
void Shape::Rectangle(double x, double y, double width, double height)
{
    mPolygon.Rectangle(x, y, width, height);
}

/**
 * Create a circular polygon shape.
 * @param radius Circle radius.
 */
void Shape::Circle(double radius)
{
    mPolygon.Circle(radius);
}

/**
 * Adds a vertex point to the polygon.
 * @param x X coordinate of point.
 * @param y Y coordinate of point.
 */
void Shape::AddPoint(double x, double y)
{
    mPolygon.AddPoint(x, y);
}

/**
 * Sets the image used to render this shape.
 * @param filename Path to image file.
 */
void Shape::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Sets the initial position of the shape in the physics world.
 * @param x Initial X coordinate.
 * @param y Initial Y coordinate.
 */
void Shape::SetInitialPosition(double x, double y)
{
    mPolygon.SetInitialPosition(x, y);
}

/**
 * Sets the initial rotation of the shape.
 * @param rad Rotation in radians.
 */
void Shape::SetInitialRotation(double rad)
{
    mPolygon.SetInitialRotation(rad);
}

/**
 * Makes the shape dynamic.
 */
void Shape::SetDynamic()
{
    mPolygon.SetDynamic();
}

/**
 * Makes the shape kinematic.
 */
void Shape::SetKinematic()
{
    mPolygon.SetKinematic();
}


/**
 * Set the physics properties of the shape.
 * @param density Shape density.
 * @param friction Surface friction.
 * @param restitution Bounciness.
 */
void Shape::SetPhysics(double density, double friction, double restitution)
{
    mPolygon.SetPhysics(density, friction, restitution);
}

/**
 * Install this shape into the physics system
 * @param world Physics system world
 */
void Shape::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Rotate the shape by setting angular velocity.
 * @param rotation Desired rotation angle (unused).
 * @param speed Angular velocity to apply.
 */
void Shape::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity( -speed );
}

/**
 * Create a rectangle centered at the bottom coordinates given.
 * @param x Width of rectangle.
 * @param y Height of rectangle.
 */
void Shape::BottomCenteredRectangle(double x, double y)
{
    mPolygon.BottomCenteredRectangle(x, y);
}