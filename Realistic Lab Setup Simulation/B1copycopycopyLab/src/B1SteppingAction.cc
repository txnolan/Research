//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "B1RunAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4Track.hh"

#include "G4Neutron.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

#include "G4Material.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/* B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
  {}*/

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fRunAction(runAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*int B1SteppingAction::GetEventCounter() const {
    return eventCounter;
    }*/

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);

  G4Track* track = step->GetTrack();

  // Get the particle definition of the track
  const G4ParticleDefinition* particleDefinition = track->GetDefinition();

  G4ThreeVector position = track->GetPosition();
  //G4double energy = track->GetKineticEnergy();
  G4double energy = 0.0;

  bool Neutron = (particleDefinition == G4Neutron::NeutronDefinition());
  G4double targetPosition = 10.14 * cm;
  bool Position = (position.mag() > targetPosition);
  // bool Energy = (energy > 5.0 * MeV);

   if (Neutron && Position) {
    energy = track->GetKineticEnergy();
    fRunAction->GetEventCounter();
    fRunAction->IncrementEventCounter();
    // eventCounter++;
    track->SetTrackStatus(fStopAndKill);
    }

   /* if(Neutron) {
    energy = track->GetKineticEnergy();
    fRunAction->GetEventCounter();
    fRunAction->IncrementEventCounter();
    // eventCounter++;
    track->SetTrackStatus(fStopAndKill);
    } */

     /* if (Neutron && Position) {
    energy = track->GetKineticEnergy();
    fRunAction->GetEventCounter();
    fRunAction->IncrementEventCounter();

    // Assuming track is a G4Track object
    G4Material* currentMaterial = track->GetMaterial();

    // Check if the current volume material is G4_Air
    if (currentMaterial == G4Material::GetMaterial("G4_AIR")) {
        track->SetTrackStatus(fStopAndKill);
    }
    }*/
  
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   //analysisManager->FillNtupleDColumn(0, 0, energy);
   // analysisManager->AddNtupleRow();
   // analysisManager->FillH1(0, energy);
   // analysisManager->FillNtupleIColumn(0, 0, energy);
   // analysisManager->AddNtupleRow();*/
   // analysisManager->FinishNtuple();
   
    if (energy > 0.00001 * MeV) {
    analysisManager->FillH1(0, energy);
    }

   /*  if (energy > 0.00001 * MeV && energy < 0.01 * MeV) {
    analysisManager->FillH1(0, energy);
    } */

   /*  if (energy > 0.00001 * MeV && energy < 15.00 * MeV) {
    analysisManager->FillH1(0, energy);
    } */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

