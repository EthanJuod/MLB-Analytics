/**
 * @file Machine.cpp
 * @author Ethan Juodawlkis
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "ContactListener.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Constructor for machine
 * @param machineNumber
 */
Machine::Machine(int machineNumber)
    : mMachineNumber(machineNumber)
{
}

/**
 * Add a component to the machine
 * @param component Component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
}

/**
 * Draw the machine
 * @param graphics Graphics context to draw on
 */
void Machine::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);


    // Draw all components
    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }

    graphics->PopState();
}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void Machine::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        this->Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {
        this->Update(1.0 / mFrameRate);
    }
}

/**
 * Update the machine in time
 * @param elapsed Elapsed time in seconds
 */
void Machine::Update(double elapsed)
{
    if (mWorld == nullptr)
    {
        return;
    }

    for (auto component : mComponents)
    {
        component->Update(elapsed);
    }

    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Reset of machine
 */
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    for (auto component : mComponents)
    {
        component->Reset();
        component->InstallPhysics(mWorld);
        component->RegisterContactListener(mContactListener);

    }
}