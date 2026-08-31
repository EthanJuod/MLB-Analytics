/**
 * @file Pipe.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PIPE_H
#define CANADIANEXPERIENCE_PIPE_H
#include "Component.h"
#include "PhysicsPolygon.h"

/**
 * Shooting Pipe
 */
class Pipe : public Component, public b2ContactListener {
private:
    /// Left wall Polygon
    cse335::PhysicsPolygon mLeftWall;
    /// Right wall polygon
    cse335::PhysicsPolygon mRightWall;
    /// Bottom polygon
    cse335::PhysicsPolygon mBottom;
    /// Pipe Image
    cse335::Polygon mPipeImage;

    /// Position for pipe
    wxPoint2DDouble mPosition;
    /// Image directory
    std::wstring mImagesDir;

    /// Ball that has been captured
    b2Body* mCapturedBall = nullptr;
    /// Time captured
    double mCaptureTime = 0.0;
    /// bool for if something has been captured
    bool mHasCapturedBall = false;
    /// Current time
    double mCurrentTime = 0.0;

    /// Shot direction
    wxPoint2DDouble mShotDirection;

public:
    /**
     * Constructor
     * @param imagesDir Directory containing images
     */
    Pipe(std::wstring imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Update(double elapsed) override;

    void RegisterContactListener(std::shared_ptr<ContactListener> contactListener) override;

    void SetPosition(double x, double y);

    /**
     * Set the shot direction
     * @param direction Direction vector (will be normalized)
     */
    void SetShotDirection(wxPoint2DDouble direction) { mShotDirection = direction; }

    void BeginContact(b2Contact *contact) override;

    void Reset() override;

    /**
     * Get the bottom body for contact detection
     * @return Pointer to bottom body
     */
    b2Body* GetBody() { return mBottom.GetBody(); }
};


#endif //CANADIANEXPERIENCE_PIPE_H