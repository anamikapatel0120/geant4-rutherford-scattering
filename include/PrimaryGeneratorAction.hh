/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the B1::PrimaryGeneratorAction class

// #ifndef B1PrimaryGeneratorAction_h
// #define B1PrimaryGeneratorAction_h 1
#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4GeneralParticleSource;


// class G4ParticleGun;
// class G4Event;
// class G4Box;

namespace B1
{

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

  private:
    G4GeneralParticleSource* fGPS = nullptr;
};

}  // namespace B1

#endif
