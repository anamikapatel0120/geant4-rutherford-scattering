/// \file SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class
#include "SteppingAction.hh"

#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "RunAction.hh"

#include <algorithm>
#include <cmath>

namespace B1
{

SteppingAction::SteppingAction(RunAction* runAction) : fRunAction(runAction) {}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume)
  {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fScoringVolume = detConstruction->GetScoringVolume();
  }

  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;
  // G4cout << "Particle reached detector!" << G4endl;
  if (step->GetPreStepPoint()->GetStepStatus() != fGeomBoundary) return;

  // Get particle track
  auto track = step->GetTrack();

  // Only consider alpha particles
  if (track->GetDefinition()->GetParticleName() != "alpha") return;

  // Get momentum direction
  auto direction = track->GetMomentumDirection();

  // Compute scattering angle
  G4double cosTheta = std::clamp(direction.z(), -1.0, 1.0);
  G4double theta = std::acos(cosTheta);
  G4double sinHalfTheta = std::sin(theta / 2.0);

  // auto runAction = static_cast<RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());

  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  fRunAction->AddAngle(eventID, theta, sinHalfTheta);

  // Kill particle after detection
  track->SetTrackStatus(fStopAndKill);
}

}  // namespace B1