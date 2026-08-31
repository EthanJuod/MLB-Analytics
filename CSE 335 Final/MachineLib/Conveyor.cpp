/**
 * @file Conveyor.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "Conveyor.h"

#include "b2_contact.h"


/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Constructor for the Conveyor object.
 * Initializes the polygon shape and loads the conveyor image.
 * @param imageDir Directory where images are stored.
 */
Conveyor::Conveyor(std::wstring imageDir)
{
    mPolygon.BottomCenteredRectangle(ConveyorSize);

    mPolygon.SetImage(imageDir + ConveyorImageName);
}

/**
 * Draw the conveyor using the provided graphics context.
 * @param graphics The graphics context to draw on.
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Install conveyor physics into the given Box2D world.
 * Creates the physics body and fixtures for the conveyor.
 * @param world The Box2D physics world.
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Registers this conveyor with a contact listener so collision events
 * involving the conveyor can be detected.
 * @param contactListener The listener that handles contacts.
 */
void Conveyor::RegisterContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(GetBody(), this);
}

/**
 * Update the conveyor each frame checks for objects
 * touching the conveyor and applies linear velocity
 * @param elapsed Time elapsed since last update.
 */
void Conveyor::Update(double elapsed)
{
    auto contact = this->GetBody()->GetContactList();

    while (contact != nullptr)
    {
        if (contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(mSpeed, 0));
        }
        contact = contact->next;
    }
}

/**
 * Set the position of the conveyor in the world.
 * Updates both the logical position and the polygon's physics position.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void Conveyor::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mPolygon.SetPosition(x, y);
}

/**
 * Get the world position of the conveyor shaft.
 * @return The shaft's position as a wxPoint2DDouble.
 */
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return mPosition + ConveyorShaftOffset;
}

/**
 * Set the conveyor's rotation and movement speed.
 * @param rotation The rotation angle (unused).
 * @param speed The speed at which the conveyor moves objects.
 */
void Conveyor::Rotate(double rotation, double speed)
{
    mSpeed = speed;
}

/**
 * Used to apply conveyor tangent speed so objects slide along it.
 * @param contact The contact information.
 * @param oldManifold Previous manifold state.
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}