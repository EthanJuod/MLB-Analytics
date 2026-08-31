/**
 * @file Motor.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "Motor.h"

/// The center point for drawing the wheel relative to the bottom center of the box
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the motor box in centimeters
const auto MotorBoxSize = wxSize(75, 50);

/// Size of the motor wheel (diameter) in centimeters
const double MotorWheelSize = 45;

/// Size of the motor images (square) in centimeters
const double MotorSize = 45;

/// How fast the motor runs (cycles per revolution)
const double MotorSpeed = 4.0;

/// The offset from the bottom center of the motor box to the center of the output shaft
const auto MotorShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the motor box
const std::wstring MotorBoxImage = L"/motor-box.png";

/// The image for the motor wheel
const std::wstring MotorWheelImage = L"/wheel.png";

/// The motor images. Image 0 is idling, 1-4 are the active motor animation images
const std::wstring MotorImages[5] =
    {L"/motor-idle.png", L"/motor-active-1.png",
     L"/motor-active-2.png", L"/motor-active-3.png",
     L"/motor-active-4.png"};

/**
 * Constructor
 * @param imagesDir Directory containing images
 */
Motor::Motor(std::wstring imagesDir) : mImagesDir(imagesDir), mSource(this, imagesDir)
{
    mBox.BottomCenteredRectangle(MotorBoxSize);
    mBox.SetImage(mImagesDir + MotorBoxImage);


    mWheel.CenteredSquare(MotorWheelSize);
    mWheel.SetImage(mImagesDir + MotorWheelImage);

    // Create the motor images (visual only) - centered squares
    for (int i = 0; i < 5; i++)
    {
        mMotors[i].CenteredSquare(MotorSize);
        mMotors[i].SetImage(mImagesDir + MotorImages[i]);
    }

}

/**
 * Set the position of the motor
 * @param x X position in centimeters
 * @param y Y position in centimeters
 */
void Motor::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mBox.SetInitialPosition(x, y);
}

/**
 * Draw the motor
 * @param graphics Graphics context to draw on
 */
void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBox.Draw(graphics);

    // Draw the wheel at the wheel center position
    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y + WheelCenter.m_y);
    graphics->Rotate(mRotation * 2 * 3.1415);
    mWheel.DrawPolygon(graphics, 0, 0, 0);
    graphics->PopState();

    // Draw the motor image (idle or active animation)
    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y + WheelCenter.m_y);

    // Mirror for negative speed
    if (mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }

    // Determine which image to show
    int motorIndex = 0;
    if (mIsActive)
    {
        double cycle = fmod(fabs(mRotation) * MotorSpeed, 1.0);
        motorIndex = 1 + (int)(cycle * 4);
        if (motorIndex > 4) motorIndex = 4;
    }

    mMotors[motorIndex].DrawPolygon(graphics, 0, 0, 0);
    graphics->PopState();
}

/**
 * Install this motor into the physics system
 * @param world Physics system world
 */
void Motor::InstallPhysics(std::shared_ptr<b2World> world)
{
    // Only install the box - it's the only physics object
    mBox.InstallPhysics(world);
}

/**
 * Update the motor in time
 * @param elapsed Elapsed time in seconds
 */
void Motor::Update(double elapsed)
{
    if (!mIsActive)
    {
        return;
    }

    if (mOscillating)
    {
        double forwardSpeed = mSpeed;
        double backwardSpeed = mSpeed / mWindupToReleaseRatio;

        double forwardTime = mSpread / forwardSpeed;
        double backwardTime = mSpread / backwardSpeed;

        mOscillationPhase += elapsed;

        forwardTime *= .9999999999998;
        if (mOscillationWindup)
        {
            mRotation += -forwardSpeed * elapsed;

            if (mOscillationPhase >= forwardTime)
            {
                mOscillationWindup = false;
                mOscillationPhase = 0;  // Reset timer for next phase
            }

            mSource.SetRotation(mRotation);
            mSource.SetSpeed(forwardSpeed);
        }
        else
        {
            mRotation += backwardSpeed * elapsed;

            if (mOscillationPhase >= backwardTime)
            {
                // Switch to wind-up
                mOscillationWindup = true;
                mOscillationPhase = 0;
            }

            mSource.SetRotation(mRotation);
            mSource.SetSpeed(-backwardSpeed);
        }
    }
    else
    {
        mRotation += -mSpeed * elapsed;
        mSource.SetRotation(mRotation);
        mSource.SetSpeed(mSpeed);
    }
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Motor::BeginContact(b2Contact *contact)
{
    mIsActive = true;


}

/**
 * Register this motor with the given contact listener.
 * @param contactListener The contact listener to register with.
 */
void Motor::RegisterContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(GetBody(), this);
}

/**
 * Get the world position of the motor’s shaft.
 * @return The shaft position as a wxPoint2DDouble.
 */
wxPoint2DDouble Motor::GetShaftPosition()
{
    return mPosition + MotorShaftOffset;
}

/**
 * Reset the motor
 */
void Motor::Reset()
{
    mIsActive = mInitiallyActive;  // Reset to initial state
    mRotation = 0.0;
    mOscillationPhase = 0.0;
    mOscillationWindup = true;
}