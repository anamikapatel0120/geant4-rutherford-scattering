/// \file EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"

#include "G4Event.hh"

namespace B1
{

EventAction::EventAction(RunAction* runAction)
 : fRunAction(runAction)
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  // Nothing needed for this simulation
}

void EventAction::EndOfEventAction(const G4Event*)
{
  // No energy deposition tracking required
}

}  // namespace B1