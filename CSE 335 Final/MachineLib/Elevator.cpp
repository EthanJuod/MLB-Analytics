/**
 * @file Elevator.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "Elevator.h"


/**
 * Constructor for the Elevator.
 * Sets the elevator's physics body to be kinematic
 */
Elevator::Elevator()
{
    mPolygon.SetKinematic();
}

/**
 * Draw the elevator using the provided graphics context.
 * @param graphics The graphics context to draw with.
 */
void Elevator::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Install the elevator's physics body into the Box2D world.
 * @param world The Box2D physics world.
 */
void Elevator::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Update the elevator each frame.
 * Moves the elevator vertically at its set speed.
 * @param elapsed Time elapsed since last update (unused).
 */
void Elevator::Update(double elapsed)
{
    b2Body* body = mPolygon.GetBody();
    if (body != nullptr)
    {
        body->SetLinearVelocity(b2Vec2(0, mSpeed));
    }
    if (mPolygon.GetPosition().m_y >= 370)
    {
        mPolygon.SetPosition(mPolygon.GetPosition().m_x, mStartY);
    }
}

/**
 * Create a rectangular shape for the elevator.
 * @param x X coordinate of rectangle corner.
 * @param y Y coordinate of rectangle corner.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
void Elevator::Rectangle(double x, double y, double width, double height)
{
    mPolygon.Rectangle(x, y, width, height);
}

/**
 * Set the image used when drawing the elevator.
 * @param filename Path to the image file.
 */
void Elevator::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Set the elevator's world position.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void Elevator::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mPolygon.SetPosition(x, y);

    mStartY = y;
}

/**
 * Set the elevator's movement speed.
 * @param rotation Elevator rotation (unused).
 * @param speed Vertical movement speed.
 */
void Elevator::Rotate(double rotation, double speed)
{
    mSpeed = speed;
}