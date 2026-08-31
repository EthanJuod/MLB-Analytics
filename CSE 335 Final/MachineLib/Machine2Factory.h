/**
 * @file Machine2Factory.h
 * @author ejuod
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINE2FACTORY_H


class Machine;
class Shape;

/**
 * Factory for machine 2
 */
class Machine2Factory {
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

    /// The possible domino colors
    enum class DominoColor { Black, Red, Green, Blue };

    /// Height of a domino
    const double DominoHeight = 25;

    /// Width of a domino
    const double DominoWidth = 5;

    /// Height of a bowling pin
    const double BowlingPinHeight = 35;

    /// Width of a bowling pin
    const double BowlingPinWidth = 10;

    void BasketballLauncher(std::shared_ptr<Machine> machine);
    void ConveyorSystem(std::shared_ptr<Machine> machine);
    void PinKnocker(std::shared_ptr<Machine> machine, wxPoint2DDouble position);

    void MarbleTower(std::shared_ptr<Machine> machine);
    void AlienConveyor(std::shared_ptr<Machine> machine);
    void BowlingBallCannon(std::shared_ptr<Machine> machine);

    std::shared_ptr<Shape> Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color);
    std::shared_ptr<Shape> BowlingPin(std::shared_ptr<Machine> machine, wxPoint2DDouble position);



public:
    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create(int num);
};


#endif //CANADIANEXPERIENCE_MACHINE2FACTORY_H