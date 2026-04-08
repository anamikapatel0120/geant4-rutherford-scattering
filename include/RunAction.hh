/// \file RunAction.hh
/// \brief Definition of the B1::RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>
#include <tuple>
#include <mutex>

class G4Run;

namespace B1
{

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    // called by worker threads
    void AddAngle(G4int eventID, G4double theta, G4double sinHalfTheta);

  private:

    // store results temporarily
    std::vector<std::tuple<G4int, G4double, G4double>> fResults;

    // protect vector in multithreading
    std::mutex fMutex;
};

}  // namespace B1

#endif