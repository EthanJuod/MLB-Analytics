/**
 * @file Machine1Factory.cpp
 * @author Anik Momtaz
 */

#include "pch.h"
#include "Machine1Factory.h"
#include "Machine.h"
#include "Shape.h"
#include "Pulley.h"
#include "Motor.h"
#include "Conveyor.h"
#include "Elevator.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";
/// Width of floor
const double FloorWidth = 600;
/// Height of floor
const double FloorHeight = 15;

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine1Factory::Machine1Factory(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #1
 * @param num The machine number
 * @return
 */
std::shared_ptr<Machine> Machine1Factory::Create(int num)
{
    auto machine= std::make_shared<Machine>(num);

    auto basketball = std::make_shared<Shape>();
    basketball->Circle(16);
    basketball->SetImage(mImagesDir + L"/basketball.png");
    basketball->SetInitialPosition(-192, 350);
    basketball->SetDynamic();
    basketball->SetPhysics(.5, 0.5, 0.72);
    machine->AddComponent(basketball);

    auto bowlingball = std::make_shared<Shape>();
    bowlingball->Circle(16);
    bowlingball->SetImage(mImagesDir + L"/bowlingball.png");
    bowlingball->SetInitialPosition(-300, 80);
    bowlingball->SetDynamic();
    bowlingball->SetPhysics(5, 5, 0.1);
    machine->AddComponent(bowlingball);

    auto tennisball = std::make_shared<Shape>();
    tennisball->Circle(8);
    tennisball->SetImage(mImagesDir + L"/tennisball.png");
    tennisball->SetInitialPosition(-230, 100);
    tennisball->SetDynamic();
    tennisball->SetPhysics(1, 0.5, 0.7);
    machine->AddComponent(tennisball);

    auto floor = std::make_shared<Shape>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    floor->SetInitialPosition(25, -40);
    machine->AddComponent(floor);

    ElevatorAndConveyor(machine);

    auto platform1 = std::make_shared<Shape>();
    platform1->Rectangle(-FloorWidth/2, -FloorHeight, 300, FloorHeight);
    platform1->SetImage(mImagesDir + L"/floor.png");
    platform1->SetInitialPosition(300, 250);
    machine->AddComponent(platform1);

    DominoStack(machine, wxPoint2DDouble(150, 250));

    auto platform2 = std::make_shared<Shape>();
    platform2->Rectangle(-FloorWidth/2, -FloorHeight, 300, FloorHeight);
    platform2->SetImage(mImagesDir + L"/floor.png");
    platform2->SetInitialPosition(300, 100);
    machine->AddComponent(platform2);

    BowlingPinStack(machine, wxPoint2DDouble(150, 100));

    SiegeContraption(machine);

    return machine;
}

/**
 * Generate the elevator, the conveyor, and their associated components
 * @param machine Machine to add to
 */
void Machine1Factory::ElevatorAndConveyor(std::shared_ptr<Machine> machine)
{
    auto motorEC = std::make_shared<Motor>(mImagesDir);
    motorEC->SetPosition(-20, 340);
    motorEC->SetInitiallyActive(true);      // Initially active
    motorEC->SetSpeed(.5);
    machine->AddComponent(motorEC);
    auto motorECshaft = motorEC->GetShaftPosition();

    auto conveyorEC = std::make_shared<Conveyor>(mImagesDir);
    conveyorEC->SetPosition(-200, 320);
    machine->AddComponent(conveyorEC);
    auto conveyorECshaft = conveyorEC->GetShaftPosition();

    auto elevator1EC = std::make_shared<Elevator>();
    elevator1EC->Rectangle(-50, -FloorHeight/2, 50, FloorHeight/2);
    elevator1EC->SetImage(mImagesDir + L"/beam2.png");
    elevator1EC->SetPosition(-277.5, -47.5);
    machine->AddComponent(elevator1EC);


    auto wedgeEC = std::make_shared<Shape>();
    wedgeEC->AddPoint(-25, 0);
    wedgeEC->AddPoint(25, 0);
    wedgeEC->AddPoint(25, 4.5);
    wedgeEC->AddPoint(-25, 55);
    wedgeEC->SetImage(mImagesDir + L"/wedge.png");
    wedgeEC->SetInitialRotation(-0.25);
    wedgeEC->SetInitialPosition(-330, 365);
    machine->AddComponent(wedgeEC);

    auto pulleyMotorEC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyMotorEC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMotorEC->SetPosition(motorECshaft);
    machine->AddComponent(pulleyMotorEC);

    motorEC->GetSource()->AddSink(pulleyMotorEC);

    auto pulleyConveyorEC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyConveyorEC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyConveyorEC->SetPosition(conveyorECshaft);
    machine->AddComponent(pulleyConveyorEC);

    pulleyMotorEC->Drive(pulleyConveyorEC);

    pulleyConveyorEC->GetSource()->AddSink(conveyorEC);

    auto pulleyElevatorEC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyElevatorEC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyElevatorEC->SetPosition(wxPoint2DDouble(-310, 370));
    machine->AddComponent(pulleyElevatorEC);

    pulleyConveyorEC->Drive(pulleyElevatorEC);

    pulleyElevatorEC->GetSource()->AddSink(elevator1EC);
}

/**
 * Generate the siege contraption, and its associated components
 * @param machine Machine to add to
 */
void Machine1Factory::SiegeContraption(std::shared_ptr<Machine> machine)
{
    auto beamSC = std::make_shared<Shape>();
    beamSC->BottomCenteredRectangle(180, FloorHeight);
    beamSC->SetImage(mImagesDir + L"/beam.png");
    beamSC->SetInitialPosition(-180, 220);
    machine->AddComponent(beamSC);

    auto wedgeSC = std::make_shared<Shape>();
    wedgeSC->AddPoint(-5, 0);
    wedgeSC->AddPoint(0, 0);
    wedgeSC->AddPoint(0, 4.5);
    wedgeSC->AddPoint(-5, 45);
    wedgeSC->SetImage(mImagesDir + L"/wedge.png");
    wedgeSC->SetInitialRotation(0.25);
    wedgeSC->SetInitialPosition(-90, 240);
    machine->AddComponent(wedgeSC);

    auto motorSC = std::make_shared<Motor>(mImagesDir);
    motorSC->SetPosition(-230, 25);
    motorSC->SetInitiallyActive(false);      // Initially idle
    motorSC->SetSpeed(1);
    motorSC->SetOscillating(true);
    motorSC->SetSpread(0.2);
    motorSC->SetWindupToReleaseRatio(5.0);
    machine->AddComponent(motorSC);
    auto motorSCshaft = motorSC->GetShaftPosition();

    auto pulleyMidOuterSC = std::make_shared<Pulley>(25, mImagesDir);
    pulleyMidOuterSC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMidOuterSC->SetPosition(wxPoint2DDouble(-125, 140));
    machine->AddComponent(pulleyMidOuterSC);

    auto pulleyMotorSC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyMotorSC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMotorSC->SetPosition(motorSCshaft);
    machine->AddComponent(pulleyMotorSC);

    motorSC->GetSource()->AddSink(pulleyMotorSC);

    auto pulleyMidInnerSC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyMidInnerSC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMidInnerSC->SetPosition(wxPoint2DDouble(-125, 140));
    machine->AddComponent(pulleyMidInnerSC);

    pulleyMotorSC->Drive(pulleyMidInnerSC);

    pulleyMidInnerSC->GetSource()->AddSink(pulleyMidOuterSC);

    auto pulleyArmSC = std::make_shared<Pulley>(10, mImagesDir);
    pulleyArmSC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyArmSC->SetPosition(wxPoint2DDouble(-205, 215));
    machine->AddComponent(pulleyArmSC);
    auto pulleyArmSCshaft = pulleyArmSC->GetPosition();

    pulleyMidOuterSC->Drive(pulleyArmSC);

    auto spoonSC = std::make_shared<Shape>();
    spoonSC->SetInitialPosition(pulleyArmSCshaft.m_x, pulleyArmSCshaft.m_y);
    spoonSC->AddPoint(-7, 10);
    spoonSC->AddPoint(7, 10);
    spoonSC->AddPoint(7, -60);
    spoonSC->AddPoint(-7, -60);
    spoonSC->SetImage(mImagesDir + L"/spoon.png");
    spoonSC->SetKinematic();
    spoonSC->SetInitialRotation(0.75);
    machine->AddComponent(spoonSC);

    pulleyArmSC->GetSource()->AddSink(spoonSC);
}

/**
 * Generate a stack of dominoes
 * @param machine Machine to add to
 * @param position position to be place
 */
void Machine1Factory::DominoStack(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    Domino(machine, position + wxPoint2DDouble(-DominoHeight/2 + DominoWidth/2, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2 - DominoWidth/2, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight/2 + DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2 - DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight/2 + DominoWidth/2, DominoHeight*2.5), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2 - DominoWidth/2, DominoHeight*2.5), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2 - DominoWidth*2.5, DominoHeight*3 + DominoWidth/2), 0.25, DominoColor::Black);

    Domino(machine, position + wxPoint2DDouble(-DominoHeight*1.5 - DominoHeight/2 + DominoWidth/2, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*1.5 + DominoHeight/2 - DominoWidth/2, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*1.5 - DominoHeight/2 + DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*1.5 + DominoHeight/2 - DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*1.5 + DominoHeight/2 - DominoWidth*2.5, DominoHeight*2 + DominoWidth/2), 0.25, DominoColor::Black);

    Domino(machine, position + wxPoint2DDouble(DominoHeight*1.5 - DominoHeight/2 + DominoWidth/2, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*1.5 + DominoHeight/2 - DominoWidth/2, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*1.5 - DominoHeight/2 + DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*1.5 + DominoHeight/2 - DominoWidth/2, DominoHeight*1.5), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*1.5 + DominoHeight/2 - DominoWidth*2.5, DominoHeight*2 + DominoWidth/2), 0.25, DominoColor::Black);

    Domino(machine, position + wxPoint2DDouble(-DominoHeight*3 - DominoHeight/2 + DominoWidth/2, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*3 + DominoHeight/2 - DominoWidth/2, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-DominoHeight*3 + DominoHeight/2 - DominoWidth*2.5, DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);

    Domino(machine, position + wxPoint2DDouble(DominoHeight*3 - DominoHeight/2 + DominoWidth/2, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*3 + DominoHeight/2 - DominoWidth/2, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(DominoHeight*3 + DominoHeight/2 - DominoWidth*2.5, DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);
}

/**
 * Generate a stack of bowling pins
 * @param machine Machine to add to
 * @param position position to be place
 */
void Machine1Factory::BowlingPinStack(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    BowlingPin(machine, position + wxPoint2DDouble(0, BowlingPinHeight/2));
    BowlingPin(machine, position + wxPoint2DDouble(-DominoHeight, BowlingPinHeight/2));
    BowlingPin(machine, position + wxPoint2DDouble(DominoHeight, BowlingPinHeight/2));
    Domino(machine, position + wxPoint2DDouble(-DominoHeight/2, BowlingPinHeight + DominoWidth/2), 0.25, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2, BowlingPinHeight + DominoWidth/2), 0.25, DominoColor::Green);

    BowlingPin(machine, position + wxPoint2DDouble(-DominoHeight/2, BowlingPinHeight*1.5 + DominoWidth));
    BowlingPin(machine, position + wxPoint2DDouble(DominoHeight/2, BowlingPinHeight*1.5 + DominoWidth));
    Domino(machine, position + wxPoint2DDouble(0, BowlingPinHeight*2 + DominoWidth*1.5), 0.25, DominoColor::Blue);

    BowlingPin(machine, position + wxPoint2DDouble(0, BowlingPinHeight*2.5 + DominoWidth*2));
}

/**
 * Create a domino and add it to the machine.
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @param rotation Rotation in turns
 * @param color Color code
 * @return Returns the created domino shape
 */
std::shared_ptr<Shape>  Machine1Factory::Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto domino = std::make_shared<Shape>();
    domino->Rectangle(-DominoWidth/2, -DominoHeight/2, DominoWidth, DominoHeight);
    switch(color)
    {
        case DominoColor::Black:
            domino->SetImage(mImagesDir + L"/domino-black.png");
            break;

        case DominoColor::Red:
            domino->SetImage(mImagesDir + L"/domino-red.png");
            break;

        case DominoColor::Green:
            domino->SetImage(mImagesDir + L"/domino-green.png");
            break;

        case DominoColor::Blue:
            domino->SetImage(mImagesDir + L"/domino-blue.png");
            break;
    }

    domino->SetInitialPosition(x, y);
    domino->SetInitialRotation(rotation);
    domino->SetDynamic();
    domino->SetPhysics(0.5, 0.5, 0.75);
    machine->AddComponent(domino);

    return domino;
}

/**
 * Create a bowling pin and add it to the machine.
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @return Returns the created bowling pin shape
 */
std::shared_ptr<Shape> Machine1Factory::BowlingPin(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto pin = std::make_shared<Shape>();
    pin->Rectangle(-BowlingPinWidth/2, -BowlingPinHeight/2, BowlingPinWidth, BowlingPinHeight);
    pin->SetImage(mImagesDir + L"/pin.png");

    pin->SetInitialPosition(x, y);
    pin->SetDynamic();
    pin->SetPhysics(0.5, 0.5, 1.0);
    machine->AddComponent(pin);

    return pin;
}
