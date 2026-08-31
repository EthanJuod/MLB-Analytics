/**
 * @file MachineSystemActual.h
 * @author Ethan Juodawlkis
 *
 *
 */


#ifndef CANADIANEXPERIENCE_MACHINESYSTEMACTUAL_H
#define CANADIANEXPERIENCE_MACHINESYSTEMACTUAL_H


#include "IMachineSystem.h"

class Machine;

/**
 * Class representing IMachineSystem
 */
class MachineSystemActual : public IMachineSystem {
private:
    /// The Machine
    std::shared_ptr<Machine> mMachine;
    /// Resource directory
    std::wstring mResourcesDir;

public:
    MachineSystemActual(std::wstring resourcesDir);

    void SetLocation(wxPoint location) override;
    wxPoint GetLocation() override;
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    void SetFrameRate(double rate) override;
    void ChooseMachine(int machine) override;
    int GetMachineNumber() override;
    double GetMachineTime() override;
    void SetFlag(int flag) override;
};


#endif //CANADIANEXPERIENCE_MACHINESYSTEMACTUAL_H