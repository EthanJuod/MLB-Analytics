/**
 * @file Machine2Factory.cpp
 * @author ejuod
 */

#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Shape.h"
#include "Pulley.h"
#include "Motor.h"
#include "Conveyor.h"
#include "Elevator.h"
#include "Pipe.h"

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
Machine2Factory::Machine2Factory(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #2
 * @param num The machine number
 * @return Shared pointer to Machine
 */
std::shared_ptr<Machine> Machine2Factory::Create(int num)
{
    auto machine = std::make_shared<Machine>(num);

    // Main floor at bottom
    auto floor = std::make_shared<Shape>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    floor->SetInitialPosition(0, -40);
    machine->AddComponent(floor);

    // Tennis ball starts on upper left
    auto marble = std::make_shared<Shape>();
    marble->Circle(10);
    marble->SetImage(mImagesDir + L"/bowlingball.png");
    marble->SetInitialPosition(-280, 350);
    marble->SetDynamic();
    marble->SetPhysics(20, 1, 0);
    machine->AddComponent(marble);


    // Bowling ball on right side platform
    auto bowlingball = std::make_shared<Shape>();
    bowlingball->Circle(16);
    bowlingball->SetImage(mImagesDir + L"/bowlingball.png");
    bowlingball->SetInitialPosition(150, 200);
    bowlingball->SetDynamic();
    bowlingball->SetPhysics(5, 5, 0.2);
    machine->AddComponent(bowlingball);

    // Bowling ball on right side platform
    auto bowlingball2 = std::make_shared<Shape>();
    bowlingball2->Circle(16);
    bowlingball2->SetImage(mImagesDir + L"/bowlingball.png");
    bowlingball2->SetInitialPosition(200, 200);
    bowlingball2->SetDynamic();
    bowlingball2->SetPhysics(5, 5, 0.2);
    machine->AddComponent(bowlingball2);

    auto bowlingball3 = std::make_shared<Shape>();
    bowlingball3->Circle(16);
    bowlingball3->SetImage(mImagesDir + L"/bowlingball.png");
    bowlingball3->SetInitialPosition(250, 200);
    bowlingball3->SetDynamic();
    bowlingball3->SetPhysics(5, 5, 0.2);
    machine->AddComponent(bowlingball3);

    // Basketball in the launcher
    auto basketball = std::make_shared<Shape>();
    basketball->Circle(16);
    basketball->SetImage(mImagesDir + L"/basketball.png");
    basketball->SetInitialPosition(-160, 90);
    basketball->SetDynamic();
    basketball->SetPhysics(.5, 0.5, 0.72);
    machine->AddComponent(basketball);

    auto alien1 = std::make_shared<Shape>();
    alien1->Rectangle(0, 0, 40, 40);
    alien1->SetImage(mImagesDir + L"/alien-right.png");
    alien1->SetInitialPosition(50, 310);
    alien1->SetDynamic();
    machine->AddComponent(alien1);

    auto alien2 = std::make_shared<Shape>();
    alien2->Rectangle(0, 0, 40, 40);
    alien2->SetImage(mImagesDir + L"/alien-right.png");
    alien2->SetInitialPosition(75, 310);
    alien2->SetDynamic();
    machine->AddComponent(alien2);

    auto alien3 = std::make_shared<Shape>();
    alien3->Rectangle(0, 0, 40, 40);
    alien3->SetImage(mImagesDir + L"/alien-right.png");
    alien3->SetInitialPosition(100, 310);
    alien3->SetDynamic();
    machine->AddComponent(alien3);

    auto alien4 = std::make_shared<Shape>();
    alien4->Rectangle(0, 0, 40, 40);
    alien4->SetImage(mImagesDir + L"/alien-right.png");
    alien4->SetInitialPosition(125, 310);
    alien4->SetDynamic();
    machine->AddComponent(alien4);




    // Add the subsystems
    BasketballLauncher(machine);
    ConveyorSystem(machine);
    MarbleTower(machine);
    AlienConveyor(machine);
    PinKnocker(machine, wxPoint2DDouble(19, 65));
    BowlingBallCannon(machine);

    return machine;
}

/**
 * Create a basketball launcher with oscillating motor
 * @param machine Machine to add to
 */
void Machine2Factory::BasketballLauncher(std::shared_ptr<Machine> machine)
{
    // Platform for the launcher
    auto beamLauncher = std::make_shared<Shape>();
    beamLauncher->BottomCenteredRectangle(150, FloorHeight);
    beamLauncher->SetImage(mImagesDir + L"/beam.png");
    beamLauncher->SetInitialPosition(-100, 50);
    machine->AddComponent(beamLauncher);

    // Oscillating motor for launcher
    auto motorLauncher = std::make_shared<Motor>(mImagesDir);
    motorLauncher->SetPosition(-250, -30);
    motorLauncher->SetInitiallyActive(false);
    motorLauncher->SetSpeed(1.2);

    machine->AddComponent(motorLauncher);
    auto motorLauncherShaft = motorLauncher->GetShaftPosition();

    // Pulley system for launcher arm
    auto pulleyMotorLauncher = std::make_shared<Pulley>(10, mImagesDir);
    pulleyMotorLauncher->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMotorLauncher->SetPosition(motorLauncherShaft);
    machine->AddComponent(pulleyMotorLauncher);

    motorLauncher->GetSource()->AddSink(pulleyMotorLauncher);

    auto pulleyMidLauncher = std::make_shared<Pulley>(20, mImagesDir);
    pulleyMidLauncher->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMidLauncher->SetPosition(wxPoint2DDouble(-75, 0));
    machine->AddComponent(pulleyMidLauncher);

    pulleyMotorLauncher->Drive(pulleyMidLauncher);

    auto pulleyArmLauncher = std::make_shared<Pulley>(10, mImagesDir);
    pulleyArmLauncher->SetImage(mImagesDir + L"/pulley2.png");
    pulleyArmLauncher->SetPosition(wxPoint2DDouble(-120, 40));
    machine->AddComponent(pulleyArmLauncher);
    auto pulleyArmLauncherShaft = pulleyArmLauncher->GetPosition();

    pulleyMidLauncher->Drive(pulleyArmLauncher);

    // Launcher arm (spoon)
    auto spoonLauncher = std::make_shared<Shape>();
    spoonLauncher->SetInitialPosition(pulleyArmLauncherShaft.m_x, pulleyArmLauncherShaft.m_y);
    spoonLauncher->AddPoint(-7, 10);
    spoonLauncher->AddPoint(7, 10);
    spoonLauncher->AddPoint(7, -70);
    spoonLauncher->AddPoint(-7, -70);
    spoonLauncher->SetImage(mImagesDir + L"/spoon.png");
    spoonLauncher->SetKinematic();
    spoonLauncher->SetInitialRotation(-0.3);
    machine->AddComponent(spoonLauncher);

    pulleyArmLauncher->GetSource()->AddSink(spoonLauncher);
}

/**
 * Create the conveyor and elevator system
 * @param machine Machine to add to
 */
void Machine2Factory::ConveyorSystem(std::shared_ptr<Machine> machine)
{
    // Motor for elevator (top right)
    auto motorConv = std::make_shared<Motor>(mImagesDir);
    motorConv->SetPosition(10, -10);
    motorConv->SetInitiallyActive(true);
    motorConv->SetSpeed(0.5);
    machine->AddComponent(motorConv);
    auto motorConvShaft = motorConv->GetShaftPosition();

    // Elevator on right side
    auto elevator1 = std::make_shared<Elevator>();
    elevator1->Rectangle(-40, -10, 60, 10);
    elevator1->SetImage(mImagesDir + L"/beam2.png");
    elevator1->SetPosition(30, 65);
    machine->AddComponent(elevator1);

    // Pulley on motor
    auto pulleyMotorConv = std::make_shared<Pulley>(10, mImagesDir);
    pulleyMotorConv->SetImage(mImagesDir + L"/pulley2.png");
    pulleyMotorConv->SetPosition(motorConvShaft);
    machine->AddComponent(pulleyMotorConv);

    motorConv->GetSource()->AddSink(pulleyMotorConv);

    pulleyMotorConv->GetSource()->AddSink(elevator1);
}

/**
 * Creates shapes that make up marble tower
 * @param machine
 */
void Machine2Factory::MarbleTower(std::shared_ptr<Machine> machine)
{
    auto wedge1 = std::make_shared<Shape>();
    wedge1->AddPoint(-20, 0);
    wedge1->AddPoint(20, 0);
    wedge1->AddPoint(20, 4.5);
    wedge1->AddPoint(-20, 45);
    wedge1->SetImage(mImagesDir + L"/wedge.png");
    wedge1->SetInitialPosition(-290, 320);
    machine->AddComponent(wedge1);

    auto wedge2 = std::make_shared<Shape>();
    wedge2->AddPoint(20, 0);     // Bottom right (was -20)
    wedge2->AddPoint(-20, 0);    // Bottom left (was 20)
    wedge2->AddPoint(-20, 4.5);  // Top left (was 20)
    wedge2->AddPoint(20, 45);    // Top right (was -20)
    wedge2->SetImage(mImagesDir + L"/wedge-flipped.png");
    wedge2->SetInitialPosition(-240, 280);  // Different position
    machine->AddComponent(wedge2);

    auto wedge3 = std::make_shared<Shape>();
    wedge3->AddPoint(-20, 0);
    wedge3->AddPoint(20, 0);
    wedge3->AddPoint(20, 4.5);
    wedge3->AddPoint(-20, 45);
    wedge3->SetImage(mImagesDir + L"/wedge.png");
    wedge3->SetInitialPosition(-290, 240);
    machine->AddComponent(wedge3);

    auto wedge4 = std::make_shared<Shape>();
    wedge4->AddPoint(20, 0);
    wedge4->AddPoint(-20, 0);
    wedge4->AddPoint(-20, 4.5);
    wedge4->AddPoint(20, 45);
    wedge4->SetImage(mImagesDir + L"/wedge-flipped.png");
    wedge4->SetInitialPosition(-240, 200);
    machine->AddComponent(wedge4);

    // Wedge 5 - normal (slants right)
    auto wedge5 = std::make_shared<Shape>();
    wedge5->AddPoint(-20, 0);
    wedge5->AddPoint(20, 0);
    wedge5->AddPoint(20, 4.5);
    wedge5->AddPoint(-20, 45);
    wedge5->SetImage(mImagesDir + L"/wedge.png");
    wedge5->SetInitialPosition(-290, 160);
    machine->AddComponent(wedge5);

    // Wedge 6 - flipped (slants left)
    auto wedge6 = std::make_shared<Shape>();
    wedge6->AddPoint(20, 0);
    wedge6->AddPoint(-20, 0);
    wedge6->AddPoint(-20, 4.5);
    wedge6->AddPoint(20, 45);
    wedge6->SetImage(mImagesDir + L"/wedge-flipped.png");
    wedge6->SetInitialPosition(-240, 120);
    machine->AddComponent(wedge6);


    auto chuteLeftWall = std::make_shared<Shape>();
    chuteLeftWall->Rectangle(-5, -80, 5, 100);  // Long thin wall
    chuteLeftWall->SetImage(mImagesDir + L"/beam.png");
    chuteLeftWall->SetInitialPosition(-290, 120);
    machine->AddComponent(chuteLeftWall);

    auto chuteRightWall = std::make_shared<Shape>();
    chuteRightWall->Rectangle(-5, -80, 5, 80);
    chuteRightWall->SetImage(mImagesDir + L"/beam.png");
    chuteRightWall->SetInitialPosition(-250, 110);
    machine->AddComponent(chuteRightWall);
}

/**
 * Creates the mechanism for the conveyer belts
 * @param machine
 */
void Machine2Factory::AlienConveyor(std::shared_ptr<Machine> machine)
{
    auto motorConveyor = std::make_shared<Motor>(mImagesDir);
    motorConveyor->SetPosition(-100, 300);
    motorConveyor->SetInitiallyActive(true);
    motorConveyor->SetSpeed(.5);

    machine->AddComponent(motorConveyor);

    auto alienPulley1 = std::make_shared<Pulley>(10, mImagesDir);
    alienPulley1->SetImage(mImagesDir + L"/pulley2.png");
    alienPulley1->SetPosition(motorConveyor->GetShaftPosition());
    machine->AddComponent(alienPulley1);


    auto alienPulley3 = std::make_shared<Pulley>(10, mImagesDir);
    alienPulley3->SetImage(mImagesDir + L"/pulley2.png");
    alienPulley3->SetPosition(wxPoint2DDouble(110,290));
    machine->AddComponent(alienPulley3);

    auto alienPulley2 = std::make_shared<Pulley>(10, mImagesDir);
    alienPulley2->SetImage(mImagesDir + L"/pulley2.png");
    alienPulley2->SetPosition(wxPoint2DDouble(235,290));
    machine->AddComponent(alienPulley2);


    auto conveyor1 = std::make_shared<Conveyor>(mImagesDir);
    conveyor1->SetPosition(235, 290);
    machine->AddComponent(conveyor1);



    auto conveyor2 = std::make_shared<Conveyor>(mImagesDir);
    conveyor2->SetPosition(110, 290);
    machine->AddComponent(conveyor2);


    motorConveyor->GetSource()->AddSink(alienPulley1);
    alienPulley1->Drive(alienPulley3);
    alienPulley3->Drive(alienPulley2);
    alienPulley3->GetSource()->AddSink(conveyor1);
    alienPulley2->GetSource()->AddSink(conveyor2);
}

/**
 *  Makes pipes as cannons for bowling balls
 * @param machine
 */
void Machine2Factory::BowlingBallCannon(std::shared_ptr<Machine> machine)
{

    auto pipe = std::make_shared<Pipe>(mImagesDir);
    pipe->SetPosition(150, 50);
    pipe->SetShotDirection(wxPoint2DDouble(1, 9));
    machine->AddComponent(pipe);

    auto pipe2 = std::make_shared<Pipe>(mImagesDir);
    pipe2->SetPosition(200, 50);
    pipe2->SetShotDirection(wxPoint2DDouble(1, 9));
    machine->AddComponent(pipe2);

    auto pipe3 = std::make_shared<Pipe>(mImagesDir);
    pipe3->SetPosition(250, 50);
    pipe3->SetShotDirection(wxPoint2DDouble(1, 9));
    machine->AddComponent(pipe3);
}

/**
 * Create bowling pins to be knocked down
 * @param machine Machine to add to
 * @param position Center position
 */
void Machine2Factory::PinKnocker(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    // Triangle formation of bowling pins
    BowlingPin(machine, position + wxPoint2DDouble(0, BowlingPinHeight/2));
    BowlingPin(machine, position + wxPoint2DDouble(-DominoHeight, BowlingPinHeight/2));
    BowlingPin(machine, position + wxPoint2DDouble(DominoHeight, BowlingPinHeight/2));

    Domino(machine, position + wxPoint2DDouble(-DominoHeight/2, BowlingPinHeight + DominoWidth/2), 0.25, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(DominoHeight/2, BowlingPinHeight + DominoWidth/2), 0.25, DominoColor::Blue);
}

/**
 * Create a domino and add it to the machine
 * @param machine Machine to add to
 * @param position Position to place the domino
 * @param rotation Rotation in turns
 * @param color Domino color
 * @return Shared pointer to created domino
 */
std::shared_ptr<Shape> Machine2Factory::Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color)
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
 * Create a bowling pin and add it to the machine
 * @param machine Machine to add to
 * @param position Position to place the pin
 * @return Shared pointer to created bowling pin
 */
std::shared_ptr<Shape> Machine2Factory::BowlingPin(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
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