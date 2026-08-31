/**
 * @file Machine.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINE_H
#define CANADIANEXPERIENCE_MACHINE_H
#include "b2_world.h"
#include "ContactListener.h"


class Component;

/**
 * Whole machine architecture
 */
class Machine {
private:
    /// Vector for components of machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// Machine number
    int mMachineNumber = 1;
    /// Location of the machine
    wxPoint mLocation;
    /// Current frame of Machine
    int mFrame = 0;
    /// Frame rate
    double mFrameRate = 30;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

public:
    Machine(int machineNumber);

    /**
     * Set the position for the root of the machine
     * @param location X,Y location in pixels
     */
    void SetLocation(wxPoint location) { mLocation = location; }

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    wxPoint GetLocation() { return mLocation; }

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);

    void SetMachineFrame(int frame);

    /**
     * Get the current machine number
     * @return Machine number
     */
    int GetMachineNumber() { return mMachineNumber; }

    /**
     * Get the current machine time
     * @return Machine time in seconds
     */
    double GetMachineTime() { return mFrame / mFrameRate; }

    /**
     * Set the frame rate
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) { mFrameRate = rate; }

    void AddComponent(std::shared_ptr<Component> component);

    /**
     * Set flag from control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) {}

    void Update(double elapsed);

    void Reset();
};


#endif //CANADIANEXPERIENCE_MACHINE_H