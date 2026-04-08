#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "QBBC.hh"

#include <string>

using namespace B1;

int main(int argc, char** argv)
{
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  auto runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

  runManager->SetUserInitialization(new DetectorConstruction());

  auto physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization());

  auto UImanager = G4UImanager::GetUIpointer();

  UImanager->ApplyCommand("/run/initialize");

  G4int nEvents = 1000;

  if (argc > 1)
  {
    nEvents = std::stoi(argv[1]);
  }

  G4String runCommand = "/run/beamOn ";
  runCommand += std::to_string(nEvents);

  UImanager->ApplyCommand(runCommand);

  delete runManager;
}



// #include "G4RunManagerFactory.hh"
// #include "G4SteppingVerbose.hh"
// #include "G4UImanager.hh"

// #include "ActionInitialization.hh"
// #include "DetectorConstruction.hh"
// #include "QBBC.hh"

// #include "G4VisExecutive.hh"
// #include "G4UIExecutive.hh"

// using namespace B1;

// int main(int argc, char** argv)
// {
//   auto runManager =
//     G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

//   runManager->SetUserInitialization(new DetectorConstruction());

//   auto physicsList = new QBBC;
//   physicsList->SetVerboseLevel(1);
//   runManager->SetUserInitialization(physicsList);

//   runManager->SetUserInitialization(new ActionInitialization());

//   auto visManager = new G4VisExecutive;
//   visManager->Initialize();

//   auto UImanager = G4UImanager::GetUIpointer();

//   if (argc == 1)
//   {
//     // Interactive mode
//     auto ui = new G4UIExecutive(argc, argv);
//     UImanager->ApplyCommand("/control/execute vis.mac");
//     ui->SessionStart();
//     delete ui;
//   }
//   else
//   {
//     // Batch mode
//     G4String command = "/control/execute ";
//     G4String fileName = argv[1];
//     UImanager->ApplyCommand(command + fileName);
//   }

//   delete visManager;
//   delete runManager;
// }