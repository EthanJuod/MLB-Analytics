/**
 * @file Picture.cpp
 * @author Charles B. Owen
 */
#include "pch.h"
#include <wx/stdpaths.h>

#include "Picture.h"
#include "PictureObserver.h"
#include "Actor.h"


/**
 * Constructor
*/
Picture::Picture()
{
}


/**
 * Set the current animation time
 *
 * This forces the animation of all
 * objects to the current animation location.
 * @param time The new time.
 */
void Picture::SetAnimationTime(double time)
{
    mTimeline.SetCurrentTime(time);
    UpdateObservers();

    for (auto actor : mActors)
    {
        actor->GetKeyframe();
    }

    int frame = time * mTimeline.GetFrameRate();
    for (auto machine : mMachines)
    {
        machine->UpdateMachine(frame, mTimeline.GetFrameRate());
    }
}

/**
 * Get the current animation time.
 * @return The current animation time
 */
double Picture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}

/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/**
 * Draw this picture on a device context
 * @param graphics The device context to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Drawing BAckground first
    if (!mActors.empty())
    {
        mActors[0]->Draw(graphics);
    }

    // Draw machines
    for (auto machine : mMachines)
    {
        machine->Draw(graphics);
    }

    // Draw remaining actors
    for (size_t i = 1; i < mActors.size(); i++)
    {
        mActors[i]->Draw(graphics);
    }


}

/**
 * Add an actor to this drawable.
 * @param actor Actor to add
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}


/**
* Save the picture animation to a file
* @param filename File to save to.
*/
void Picture::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"anim");
    xmlDoc.SetRoot(root);

    // Save the timeline animation into the XML
    mTimeline.Save(root);

    // Save machines
    if (!mMachines.empty())
    {
        auto machinesNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machines");
        root->AddChild(machinesNode);

        for (auto machine : mMachines)
        {
            auto machineNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
            machinesNode->AddChild(machineNode);

            // Match the Timeline::Save() pattern exactly
            machineNode->AddAttribute(L"number", wxString::Format(wxT("%i"), machine->GetMachineNumber()));
            machineNode->AddAttribute(L"start-frame", wxString::Format(wxT("%f"), machine->GetStartFrame()));
        }
    }

    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}



/**
* Load a picture animation from a file
* @param filename file to load from
*/
void Picture::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Animation file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Load the animation from the XML
    mTimeline.Load(root);

    // Clear existing machines
    mMachines.clear();

    // Load machines
    auto child = root->GetChildren();
    for (auto node = child; node; node = node->GetNext())
    {
        if (node->GetName() == L"machines")
        {
            // Get resources directory
            auto standardPaths = wxStandardPaths::Get();
            auto resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();

            for (auto machineNode = node->GetChildren(); machineNode; machineNode = machineNode->GetNext())
            {
                if (machineNode->GetName() == L"machine")
                {
                    // Load machine attributes
                    int machineNumber = wxAtoi(machineNode->GetAttribute(L"number", L"1"));
                    int startFrame = wxAtoi(machineNode->GetAttribute(L"start-frame", L"0"));

                    // Create the machine
                    auto machine = std::make_shared<MachineDrawable>(L"Machine", resourcesDir);
                    machine->SetMachineNumber(machineNumber);
                    machine->SetStartFrame(startFrame);

                    if (machineNumber == 1)
                    {
                        machine->SetPosition(wxPoint(400, 600));
                    }
                    else if (machineNumber == 2)
                    {
                        machine->SetPosition(wxPoint(1000, 600));
                    }

                    AddMachine(machine);
                }
            }
        }
    }

    SetAnimationTime(0);
    UpdateObservers();
}

/**
 * Adds machine to vector of machines in pictures
 * @param machine
 */
void Picture::AddMachine(std::shared_ptr<MachineDrawable> machine)
{
    mMachines.push_back(machine);
}

