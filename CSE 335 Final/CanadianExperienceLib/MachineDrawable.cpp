/**
 * @file MachineDrawable.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "MachineDrawable.h"
#include <machine-api.h>


/**
 * Constructor for MachineDrawable.
 * Creates a machine system using the provided resource directory.
 * @param name Drawable name.
 * @param resourceDir Directory containing machine resources.
 */
MachineDrawable::MachineDrawable(const std::wstring &name, std::wstring resourceDir) : Drawable(name)
{
    MachineSystemFactory factory(resourceDir);
    std::shared_ptr<IMachineSystem> machine = factory.CreateMachineSystem();

    mMachine = machine;
}

/**
 * Draws the machine at the drawable’s position.
 * @param graphics The graphics context to draw with.
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = .5f;

    graphics->PushState();
    graphics->Translate(GetPosition().x, GetPosition().y);
    graphics->Scale(scale, scale);
    mMachine->SetLocation(wxPoint(0, 0));
    mMachine->DrawMachine(graphics);
    graphics->PopState();

}


/**
 * Sets which machine to use.
 * @param number The machine number to select.
 */
void MachineDrawable::SetMachineNumber(int number)
{
    mMachineNumber = number;
    mMachine->ChooseMachine(number);
}

/**
 * Updates the machine animation frame based on the timeline.
 * @param frame The global animation frame.
 * @param frameRate The timeline’s frame rate.
 */
void MachineDrawable::UpdateMachine(int frame, double frameRate)
{
    mMachine->SetFrameRate(frameRate);

    if (frame >= mStartFrame)
    {
        int machineFrame = frame - mStartFrame;
        mMachine->SetMachineFrame(machineFrame);
    }
    else
    {
        mMachine->SetMachineFrame(0);
    }
}

/**
 * Determines whether a click hit the machine’s bounding region.
 * @param pos Mouse click position.
 * @return true if within bounds, otherwise false.
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    double scale = 0.75;
    double width = 1000 * scale;
    double height = 800 * scale;

    if (pos.x >= GetPosition().x - width/2 && pos.x <= GetPosition().x + width/2 && pos.y >= GetPosition().y - height && pos.y <= GetPosition().y + height)
    {
        return true;
    }

    return false;
}
