/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Alpha.hh"


namespace B1
{

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();

    fGPS->SetParticleDefinition(G4Alpha::Definition());

    fGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
    fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(
        G4ThreeVector(0., 0., 0.));

    fGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("beam1d");

    fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(
        G4ThreeVector(0., 0., 1.));

    fGPS->GetCurrentSource()->GetEneDist()->SetEnergyDisType("Mono");

    fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(5.0 * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fGPS->GeneratePrimaryVertex(event);
}

} // namespace B1




