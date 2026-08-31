/**
 * @file RotationSource.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "RotationSource.h"

#include "IRotationSink.h"


/**
 * Constructor for RotationSource.
 * @param component The component that owns this rotation source.
 * @param imagesDir Directory for any related images (unused).
 */
RotationSource::RotationSource(Component* component, std::wstring imagesDir)
{

}

/**
 * Add a rotation sink to this source.
 * @param rotationSink The sink to register.
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> rotationSink)
{
    mRotationSinks.push_back(rotationSink);
}

/**
 * Set the rotation value for the source and notify all sinks.
 * @param rotation New rotation value.
 */
void RotationSource::SetRotation(double rotation)
{
    mRotation = rotation;

    for (auto rotationSink : mRotationSinks)
    {
        rotationSink->Rotate(rotation, mSpeed);
    }
}

/**
 * Set the rotational speed for the source and notify all sinks.
 * @param speed New rotational speed.
 */
void RotationSource::SetSpeed(double speed)
{
    mSpeed = speed;

    for (auto rotationSink : mRotationSinks)
    {
        rotationSink->Rotate(mRotation, speed);
    }
}
