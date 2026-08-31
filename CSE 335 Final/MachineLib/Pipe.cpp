/**
 * @file Pipe.cpp
 * @author ejuod
 */

#include "pch.h"
#include "Pipe.h"

#include "b2_body.h"
#include "b2_contact.h"

/// The size of the pipe in centimeters
const double PipeSize = 40;

/// Delay between when the ball falls in the pipe, and when it is shot out
const double PipeDelay = 1.0;

/// The direction the ball is shot out of the pipe
const wxPoint2DDouble PipeShot = wxPoint2DDouble(1, 7);

/// Wall thickness
const double WallThickness = 5;

/**
 * Constructor
 * @param imagesDir Directory containing images
 */
Pipe::Pipe(std::wstring imagesDir) : mImagesDir(imagesDir), mShotDirection(PipeShot)
{
    // Create the visual pipe image
    mPipeImage.CenteredSquare(PipeSize);
    mPipeImage.SetImage(mImagesDir + L"/pipe.png");

    // Create left wall (static)
    mLeftWall.Rectangle(-WallThickness/2, -PipeSize/2, WallThickness, PipeSize/2);

    // Create right wall (static)
    mRightWall.Rectangle(-WallThickness/2, -PipeSize/2, WallThickness, PipeSize/2);

    // Create bottom (static) - this is what detects contact
    mBottom.Rectangle(-PipeSize/2, -WallThickness/2, PipeSize, WallThickness);
}

/**
 * Set the position of the pipe
 * @param x X position in centimeters
 * @param y Y position in centimeters
 */
void Pipe::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);

    // Position the walls
    mLeftWall.SetInitialPosition(x - PipeSize/2, y);
    mRightWall.SetInitialPosition(x + PipeSize/2, y);
    mBottom.SetInitialPosition(x, y - PipeSize/2);
}

/**
 * Draw the pipe
 * @param graphics Graphics context to draw on
 */
void Pipe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the pipe image
    graphics->PushState();
    graphics->Translate(mPosition.m_x, mPosition.m_y);
    mPipeImage.DrawPolygon(graphics, 0, 0, 0);
    graphics->PopState();
}

/**
 * Install this pipe into the physics system
 * @param world Physics system world
 */
void Pipe::InstallPhysics(std::shared_ptr<b2World> world)
{
    mLeftWall.InstallPhysics(world);
    mRightWall.InstallPhysics(world);
    mBottom.InstallPhysics(world);
}

/**
 * Register as contact listener
 * @param contactListener Contact listener to register with
 */
void Pipe::RegisterContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(GetBody(), this);
}

/**
 * Update the pipe
 * @param elapsed Elapsed time in seconds
 */
void Pipe::Update(double elapsed)
{
    mCurrentTime += elapsed;

    // Check if we should shoot the ball
    if (mHasCapturedBall && mCapturedBall != nullptr)
    {
        // Hold the ball in place
        mCapturedBall->SetLinearVelocity(b2Vec2(0, 0));
        mCapturedBall->SetAngularVelocity(0);

        // Check if delay has elapsed
        if (mCurrentTime - mCaptureTime >= PipeDelay)
        {

            b2Vec2 velocity(-10,10);

            mCapturedBall->SetLinearVelocity(velocity);

            // Release the ball
            mCapturedBall = nullptr;
            mHasCapturedBall = false;
        }
    }
}

/**
 * Handle begin contact
 * @param contact Contact object
 */
void Pipe::BeginContact(b2Contact *contact)
{
    // Capture the ball if we don't already have one
    if (!mHasCapturedBall)
    {
        // Get the other body in the contact
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        b2Body* otherBody = (bodyA == mBottom.GetBody()) ? bodyB : bodyA;

        mCapturedBall = otherBody;
        mCaptureTime = mCurrentTime;
        mHasCapturedBall = true;
    }
}

/**
 * Reset the pipe
 */
void Pipe::Reset()
{
    mCapturedBall = nullptr;
    mHasCapturedBall = false;
    mCurrentTime = 0.0;
    mCaptureTime = 0.0;
}