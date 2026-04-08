/// \file RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <fstream>
#include <iomanip>
#include <algorithm>

namespace B1
{

RunAction::RunAction() {}

// Called at beginning of run
void RunAction::BeginOfRunAction(const G4Run*)
{
  if (IsMaster())
  {
    fResults.clear();
  }
}

// Called by worker threads to store results
void RunAction::AddAngle(G4int eventID, G4double theta, G4double sinHalfTheta)
{
  std::lock_guard<std::mutex> lock(fMutex);
  fResults.emplace_back(eventID, theta, sinHalfTheta);
}

// Called at end of run
void RunAction::EndOfRunAction(const G4Run*)
{
  if (!IsMaster()) return;

  std::ofstream out("rutherford_angles.txt");

  out << "EventID\tAngle(deg)\tsin(theta/2)\n";

  std::sort(fResults.begin(), fResults.end(),
            [](const auto& a, const auto& b)
            { return std::get<0>(a) < std::get<0>(b); });

  for (const auto& entry : fResults)
  {
    out << std::get<0>(entry) << "\t"
        << std::fixed << std::setprecision(4)
        << std::get<1>(entry) / deg << "\t"
        << std::get<2>(entry) << "\n";
  }

  out.close();

  G4cout << "\nOutput written to file: rutherford_angles.txt\n" << G4endl;
}

}  // namespace B1