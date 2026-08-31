/**
 * @file Pulley.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PULLEY_H
#define CANADIANEXPERIENCE_PULLEY_H
#include "IRotationSink.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"

/**
 * Pulley class that connect for motor, sinks and other pulleys
 */
class Pulley : public Component, public IRotationSink
{
private:
    /// Polygon for pulley
    cse335::Polygon mPolygon;
    /// Radius of pulley
    double mRadius;
    /// Rotation of pulley
    double mRotation = 0;
    /// Speed of pulley
    double mSpeed = 0;
    /// Position of pulley
    wxPoint2DDouble mPosition;
    /// Source
    RotationSource mSource;
    /// Connected Pulley
    std::shared_ptr<Pulley> mDrivenPulley = nullptr;


public:
    Pulley(double radius, std::wstring imageDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void DrawBelt(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Pulley> pulley);

    void SetImage(std::wstring filename);

    void SetPosition(wxPoint2DDouble position);

    void Rotate(double rotation, double speed) override;

    void Drive(std::shared_ptr<Pulley> pulley);

    /**
     * Getter for radius
     * @return mRadius
     */
    double GetRadius() { return mRadius; }

    /**
     * Getter for rotation
     * @return mRotation
     */
    double GetRotation() { return mRotation; }

    /**
     * Getter for position
     * @return mPosition
     */
    wxPoint2DDouble GetPosition() { return mPosition; }

    /**
     * Getter for source
     * @return mSource
     */
    RotationSource* GetSource() {return &mSource; }
};


#endif //CANADIANEXPERIENCE_PULLEY_H