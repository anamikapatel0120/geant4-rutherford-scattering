#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

namespace B1
{

class RunAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(RunAction* runAction);
    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;

  private:
    RunAction* fRunAction = nullptr;
    G4LogicalVolume* fScoringVolume = nullptr;
};

}

#endif