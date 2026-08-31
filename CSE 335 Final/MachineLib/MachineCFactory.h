/**
* @file MachineCFactory.h
 * @author Anik Momtaz
 *
 * Factory that creates Machine #17 (checkpoint)
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H

#include <memory>
#include <string>

class Machine;

/**
 * Factory that creates Machine #17 (checkpoint)
 */
class MachineCFactory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    MachineCFactory(std::wstring resourcesDir);

    /// Default constructor (disabled)
    MachineCFactory() = delete;

    /// Copy constructor (disabled)
    MachineCFactory(const MachineCFactory &) = delete;

    /// Assignment operator
    void operator=(const MachineCFactory &) = delete;

    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINECFACTORY_H
