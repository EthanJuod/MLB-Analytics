/**
 * @file MachineDrawable.h
 * @author Ethan Juodawlkis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_MACHINEDRAWABLE_H
#include "Drawable.h"
#include <machine-api.h>

/**
 * Conversion for machines to Canadian Experience
 */
class MachineDrawable : public Drawable
{
private:
    /// Machine
    std::shared_ptr<IMachineSystem> mMachine;
    /// Machine number
    int mMachineNumber = 1;
    /// Machines start frame
    double mStartFrame;

public:
    MachineDrawable(const std::wstring &name, std::wstring resourceDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetMachineNumber(int number);

    /**
     * Setter for mStartFrame
     * @param startFrame
     */
    void SetStartFrame(double startFrame) {mStartFrame = startFrame;}

    bool HitTest(wxPoint pos) override;

    void UpdateMachine(int frame, double frameRate);

    /**
     * Get Start Frame
     * @return mStartFrame
     */
    double GetStartFrame() { return mStartFrame; }

    /**
     * Gets Machine Number
     * @return mMachineNumber
     */
    int GetMachineNumber() { return mMachineNumber; }


};


#endif //CANADIANEXPERIENCE_MACHINEDRAWABLE_H