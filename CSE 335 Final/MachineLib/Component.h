/**
 * @file Component.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H
#include <memory>
#include <wx/graphics.h>

#include "b2_world.h"
#include "ContactListener.h"

/**
 * Base class for all components
 */
class Component
{
private:


public:

    virtual ~Component() = default;

    /**
     * Draw this component onto graphics
     * @param graphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

    /**
     * Install this component into the physics system
     * @param world Physics system world
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world) {}

    /**
     * Update the component in time
     * @param elapsed Elapsed time in seconds
     */
    virtual void Update(double elapsed) {}

    /**
     * Register component and a contact listener
     * @param contactListener
     */
    virtual void RegisterContactListener(std::shared_ptr<ContactListener> contactListener) {}

    /**
     * Reset the component
     */
    virtual void Reset() {}

};


#endif //CANADIANEXPERIENCE_COMPONENT_H