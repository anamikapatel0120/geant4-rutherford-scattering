/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

namespace B1
{

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  G4double env_sizeXY = 40 * cm, env_sizeZ = 60 * cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4bool checkOverlaps = true;

  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld =
    new G4Box("World",  // its name
              0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        world_mat,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  G4Material* Gold_foil = nist->FindOrBuildMaterial("G4_Au");
  G4ThreeVector pos2 = G4ThreeVector(0, 0, 3.0 * mm);

  auto solidFoil = new G4Box("GoldFoil",  // its name
                             0.5 * cm, 0.5 * cm, 0.5 * um);  // its size

  auto logicFoil = new G4LogicalVolume(solidFoil,  // its solid
                                       Gold_foil,  // its material
                                       "GoldFoil");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    pos2,  // at (0,0,3mm)
                    logicFoil,  // its logical volume
                    "GoldFoil",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking

  // ================= Ring Detector Around Foil =================

  // detector material
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_Si");

  // detector dimensions
  // G4double innerRadius = 2.0 * cm;
  // G4double outerRadius = 2.2 * cm;
  // G4double detectorLength = 5.0 * cm;

  // cylindrical ring detector
  // auto solidDetector =
  //   new G4Sphere("ScatteringDetector",
  //                2.0*cm,
  //                2.2*cm,
  //                0.*deg,
  //                360.*deg,
  //                0.*deg,
  //                180.*deg);

    auto solidDetector =
  new G4Sphere("ScatteringDetector",
               10.0*mm,
               11.0*mm,
               0.*deg,
               360.*deg,
               0.*deg,
               180.*deg);

  // logical volume
  auto logicRingDetector = new G4LogicalVolume(solidDetector, det_mat, "ScatteringDetector");

  // place ring centered on foil
  G4ThreeVector ringPos = G4ThreeVector(0, 0, 3.0 * mm);

  new G4PVPlacement(nullptr, ringPos, logicRingDetector, "ScatteringDetector", logicWorld, false, 0,
                    checkOverlaps);

  // scoring volume
  fScoringVolume = logicRingDetector;

  return physWorld;
}

}  // namespace B1
