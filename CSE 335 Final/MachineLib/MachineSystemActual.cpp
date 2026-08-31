/**
 * @file MachineSystemActual.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "MachineSystemActual.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"
#include "MachineCFactory.h"

/**
 * Constructor for MachineSystemActual
 * @param resourcesDir
 */
MachineSystemActual::MachineSystemActual(std::wstring resourcesDir)
    : mResourcesDir(resourcesDir)
{
    ChooseMachine(1);
}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystemActual::SetLocation(wxPoint location)
{
    mMachine->SetLocation(location);
}

/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystemActual::GetLocation()
{
    return mMachine->GetLocation();
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystemActual::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    mMachine->DrawMachine(graphics);
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystemActual::SetMachineFrame(int frame)
{
    mMachine->SetMachineFrame(frame);
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystemActual::SetFrameRate(double rate)
{
    mMachine->SetFrameRate(rate);
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystemActual::ChooseMachine(int machine)
{
    if (machine == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create(1);
        mMachine->Reset();
    }
    else if (machine == 2)
    {
        Machine2Factory factory(mResourcesDir);
        mMachine = factory.Create(2);
        mMachine->Reset();
    }
    else if (machine == 3)
    {
        MachineCFactory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
    }

}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystemActual::GetMachineNumber()
{
    return mMachine->GetMachineNumber();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystemActual::GetMachineTime()
{
    return mMachine->GetMachineTime();
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystemActual::SetFlag(int flag)
{
    mMachine->SetFlag(flag);
}
