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
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"

#include "B1EventAction.hh"
#include "B1SteppingAction.hh"

//#include "G4RunManagerFactory.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);

  // Set the Random engine
  // The following guarantees random generation also for different runs
  // in multithread
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4int seed = time( NULL );
  G4Random::setTheSeed( seed );

  
  // Construct the default run manager
  //
  // auto* runManager =
  // G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new B1DetectorConstruction());

  // Physics list

  /* G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList); */

  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP ;
  physicsList->SetVerboseLevel(2);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  // B1ActionInitialization* actionInitialization = new B1ActionInitialization();
  runManager->SetUserInitialization(new B1ActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // B1RunAction* runAction = new B1RunAction();

// ... Run the simulation ...

// Retrieve the event counter value
// int* eventCounter = runAction->GetEventCounter();

// Print or use the event counter value
// G4cout << "Number of detected events: " << *eventCounter << G4endl;

  
  // After the run is complete, retrieve and display the event counter
  /* B1EventAction* eventAction = const_cast<B1EventAction*>(static_cast<const B1EventAction*>(runManager->GetUserEventAction()));
  G4int eventCounter = eventAction->GetEventCounter();
  G4cout << "Event Counter for this run: " << eventCounter << G4endl;
  */
  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
