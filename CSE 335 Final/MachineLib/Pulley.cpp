/**
 * @file Pulley.cpp
 * @author ejuod
 */

#include "pch.h"
#include "Pulley.h"


/**
 * Constructor for Pulley.
 * @param radius Radius of the pulley.
 * @param imageDir Directory containing pulley images.
 */
Pulley::Pulley(double radius, std::wstring imageDir) : mRadius(radius), mSource(this, imageDir)
{

    mPolygon.CenteredSquare(mRadius * 2);
}

/**
 * Draw the pulley and, if connected, draw its belt to the driven pulley.
 * @param graphics Graphics context to draw into.
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mDrivenPulley != nullptr)
    {
        DrawBelt(graphics, mDrivenPulley);
    }

    graphics->PushState();
    graphics->Translate(mPosition.m_x, mPosition.m_y);
    graphics->Rotate(mRotation * 2 * 3.14);

    mPolygon.DrawPolygon(graphics, 0, 0, 0);

    graphics->PopState();
}

/**
 * Set the image used to render the pulley.
 * @param filename Path to the image file.
 */
void Pulley::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Set the world position of the pulley.
 * @param position The new pulley position.
 */
void Pulley::SetPosition(wxPoint2DDouble position)
{
    mPosition = position;
}

/**
 * Rotate the pulley
 * @param rotation Current rotation in revolutions.
 * @param speed Rotational speed.
 */
void Pulley::Rotate(double rotation, double speed)
{
    mRotation = rotation;
    mSpeed = speed;

    if (mDrivenPulley != nullptr)
    {
        mSource.SetRotation(mRotation * mRadius / mDrivenPulley->GetRadius());
        mSource.SetSpeed(speed * mRadius / mDrivenPulley->GetRadius());
    }
    else
    {
        mSource.SetRotation(mRotation);
        mSource.SetSpeed(mSpeed);
    }

}

/**
 * Draw the belt between this pulley and another pulley.
 * @param graphics Graphics context.
 * @param pulley The pulley being driven.
 */
void Pulley::DrawBelt(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Pulley> pulley)
{
    double x1 = mPosition.m_x;
    double y1 = mPosition.m_y;
    double x2 = pulley->GetPosition().m_x;
    double y2 = pulley->GetPosition().m_y;

    double r1 = mRadius - 2 ;
    double r2 = pulley->GetRadius() - 2 ;

    double theta = atan2(y2 - y1, x2 - x1);
    double phi =  (r2 - r1) / (sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)));

    double B1 = theta + phi + (M_PI / 2);
    double B2 = theta - phi - (M_PI / 2);

    double PX1 = x1 + r1 * cos(B1);
    double PY1 = y1 + r1 * sin(B1);
    double PX2 = x2 + r2 * cos(B1);
    double PY2 = y2 + r2 * sin(B1);

    graphics->SetPen(wxPen(*wxBLACK, 2));
    graphics->StrokeLine(PX1, PY1, PX2, PY2);

    double PX3 = x1 + r1 * cos(B2);
    double PY3 = y1 + r1 * sin(B2);
    double PX4 = x2 + r2 * cos(B2);
    double PY4 = y2 + r2 * sin(B2);

    graphics->StrokeLine(PX3, PY3, PX4, PY4);

}

/**
 * Connect this pulley to drive another pulley.
 * @param pulley Pulley to be driven.
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mDrivenPulley = pulley;


    mSource.AddSink(pulley);


}