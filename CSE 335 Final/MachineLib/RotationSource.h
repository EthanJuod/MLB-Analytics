/**
 * @file RotationSource.h
 * @author Ethan Juodawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_ROTATIONSOURCE_H
#include "Component.h"


class IRotationSink;

/**
 * Rotational source class connection sources to sinks
 */
class RotationSource
{
private:
    /// Vector of Sinks connected to the source
    std::vector<std::shared_ptr<IRotationSink>> mRotationSinks;
    /// Rotation for source
    double mRotation = 0.0;
    /// Speed of source
    double mSpeed = 0.0;

public:
    /// Constructor
    RotationSource(Component* component, std::wstring imagesDir);

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    void AddSink(std::shared_ptr<IRotationSink> rotationSink);

    void SetRotation(double rotation);

    /**
     * Getter for rotation
     * @return mRotation
     */
    double GetRotation(){return mRotation;}

    void SetSpeed(double speed);

    /**
     * Getter for speed
     * @return mSpeed
     */
    double GetSpeed(){return mSpeed;}
};


#endif //CANADIANEXPERIENCE_ROTATIONSOURCE_H