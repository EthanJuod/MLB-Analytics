/**
 * @file MachineCFactory.cpp
 * @author Anik Momtaz
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"
#include "Pulley.h"
#include "Conveyor.h"
#include "Elevator.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
MachineCFactory::MachineCFactory(std::wstring resourcesDir) :mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> MachineCFactory::Create()
{
    auto machine = std::make_shared<Machine>(3);

    // Notice: All dimensions are in centimeters and assume the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    auto floor = std::make_shared<Shape>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    floor->SetInitialPosition(0, -40);
    machine->AddComponent(floor);

    const double BeamWidth = 240;

    auto beam = std::make_shared<Shape>();
    beam->Rectangle(-FloorWidth/2, -FloorHeight, BeamWidth, FloorHeight);
    beam->SetImage(mImagesDir + L"/beam.png");
    beam->SetInitialPosition(FloorWidth/2-BeamWidth/2, 120);
    machine->AddComponent(beam);

    auto wedge = std::make_shared<Shape>();
    wedge->AddPoint(-25, 0);
    wedge->AddPoint(25, 0);
    wedge->AddPoint(25, 4.5);
    wedge->AddPoint(-25, 25);
    wedge->SetImage(mImagesDir + L"/wedge.png");
    wedge->SetInitialPosition(-95, 120);
    machine->AddComponent(wedge);

    auto basketball = std::make_shared<Shape>();
    basketball->Circle(16);
    basketball->SetImage(mImagesDir + L"/basketball.png");
    basketball->SetInitialPosition(200, 110);
    basketball->SetDynamic();
    basketball->SetPhysics(1, 0.5, 0.5);
    machine->AddComponent(basketball);

    auto motor = std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(80, 120);
    motor->SetInitiallyActive(false);      // Initially idle
    motor->SetSpeed(0.25);
    machine->AddComponent(motor);

    auto rotatingShape = std::make_shared<Shape>();
    rotatingShape->Rectangle(-10, -50, 10, 50);
    rotatingShape->SetImage(mImagesDir + L"/spoon.png");
    rotatingShape->SetInitialPosition(80, 120);
    rotatingShape->SetInitialRotation(.5);
    rotatingShape->SetKinematic();
    machine->AddComponent(rotatingShape);

    motor->GetSource()->AddSink(rotatingShape);

    auto motor1 = std::make_shared<Motor>(mImagesDir);
    motor1->SetSpeed(1.0);
    motor1->SetInitiallyActive(true);
    machine->AddComponent(motor1);
    motor1->SetPosition(0, 150);

    // The pulley driven by the motor
    auto pulley1 = std::make_shared<Pulley>(15, mImagesDir);
    pulley1->SetImage(mImagesDir + L"/pulley2.png");
    pulley1->SetPosition(motor1->GetShaftPosition());
    machine->AddComponent(pulley1);

    motor1->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(40, mImagesDir);
    pulley2->SetImage(mImagesDir + L"/pulley2.png");
    pulley2->SetPosition(wxPoint2DDouble(150, 250));
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    auto spoon = std::make_shared<Shape>();
    spoon->Rectangle(-10, -50, 10, 50);
    spoon->SetImage(mImagesDir + L"/spoon.png");
    spoon->SetInitialPosition(190, 250);
    spoon->SetInitialRotation(.25);
    spoon->SetKinematic();
    machine->AddComponent(spoon);

    pulley2->GetSource()->AddSink(spoon);

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    conveyor->SetPosition(200, 100);
    machine->AddComponent(conveyor);

    pulley2->GetSource()->AddSink(conveyor);

    auto elevator = std::make_shared<Elevator>();
    elevator->SetImage(mImagesDir + L"/beam2.png");
    elevator->SetPosition(10, 100);
    elevator->Rectangle(50, 100, 50, 10);
    machine->AddComponent(elevator);

    pulley2->GetSource()->AddSink(elevator);


    return machine;
}
