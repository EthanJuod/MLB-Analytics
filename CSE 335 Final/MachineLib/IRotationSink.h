/**
 * @file IRotationSink.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_IROTATIONSINK_H
#define CANADIANEXPERIENCE_IROTATIONSINK_H

/**
 * Interface class for rotational sinks
 */
class IRotationSink
{
public:
    virtual ~IRotationSink() = default;

    /**
     * Virtual function to rotate Rotation Sinks
     * @param rotation
     * @param speed
     */
    virtual void Rotate(double rotation, double speed) = 0;
};
#endif //CANADIANEXPERIENCE_IROTATIONSINK_H