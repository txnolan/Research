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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 30*cm, env_sizeZ = 30*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4Material* Eljin_mat1 = nist->FindOrBuildMaterial("G4_C");
G4Material* Eljin_mat2 = nist->FindOrBuildMaterial("G4_H");

G4double density = 1.02 * g/cm3;
G4int ncomponents = 2;          

G4Material* Eljin; // Declare the Eljin variable
 
Eljin = new G4Material("Eljin", density, ncomponents);
Eljin->AddMaterial(Eljin_mat1, 91.55 * perCent);
Eljin->AddMaterial(Eljin_mat2, 8.45 * perCent);

G4Material* GAGG_mat1 = nist->FindOrBuildMaterial("G4_Gd");
G4Material* GAGG_mat2 = nist->FindOrBuildMaterial("G4_Al");
G4Material* GAGG_mat3 = nist->FindOrBuildMaterial("G4_Ga");
G4Material* GAGG_mat4 = nist->FindOrBuildMaterial("G4_O");

G4double density3 = 6.63 * g/cm3; 
G4int ncomponents3 = 4;

G4Material* GAGG;
  
GAGG = new G4Material("GAGG", density3, ncomponents3);
GAGG->AddMaterial(GAGG_mat1, 44.2 * perCent);
GAGG->AddMaterial(GAGG_mat2, 5.06 * perCent);
GAGG->AddMaterial(GAGG_mat3, 19.6 * perCent);
GAGG->AddMaterial(GAGG_mat4, 18.0 * perCent);

G4Material* TungSh_mat1 = nist->FindOrBuildMaterial("G4_W");
G4Material* TungSh_mat2 = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

G4double density2 = 15 * g/cm3; 
G4int ncomponents2 = 2;  

G4Material* TungstenShield;
  
TungstenShield = new G4Material("TungstenShield", density2, ncomponents2);
TungstenShield->AddMaterial(TungSh_mat1, 98.19 * perCent);
TungstenShield->AddMaterial(TungSh_mat2, 1.81 * perCent);
   
  
  //     
  // Shape 1
  //  
  /*G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos1 = G4ThreeVector(0, 2*cm, -7*cm);
        
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  G4double shape1_hz = 3.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking */

  // Shape 1 (Sphere)
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);

  // Sphere shape
  G4double sphere_radius = 3.0*cm; // Set the radius of the sphere
  G4double sphere_phimin = 0.*deg;
  G4double sphere_phimax = 360.*deg;
  G4double sphere_thetamin = 0.*deg;
  G4double sphere_thetamax = 180.*deg; // This is a hemisphere
 
  G4Sphere* solidShape1 =
    new G4Sphere("Shape1",
		 0., // Inner radius (0 for a full sphere)
		 sphere_radius, // Outer radius
		 sphere_phimin, sphere_phimax,
		 sphere_thetamin, sphere_thetamax);

  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,   //its solid
			shape1_mat,    //its material
			"Shape1");     //its name

  new G4PVPlacement(0,                //no rotation
		    pos1,             //at position
		    logicShape1,      //its logical volume
		    "Shape1",         //its name
		    logicEnv,         //its mother volume
		    false,            //no boolean operation
		    0,                //copy number
		    checkOverlaps);   //overlaps checking

  //     
  // Shape 2
  //
  /*G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);

  // Trapezoid shape       
  G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
  G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
  G4double shape2_dz  = 6*cm;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                
  // Set Shape2 as scoring volume
  */

  // Shape 2 (Outer Sphere)
  G4Material* shape2_mat = nist->FindOrBuildMaterial("TungstenShield");
  G4ThreeVector pos2 = G4ThreeVector(0, 0, 0);

// Outer Sphere shape
G4double outer_sphere_radius2 = 9.0*cm;  // Adjust the outer radius to fit around the inner sphere
G4double sphere_phimin2 = 0.*deg;
G4double sphere_phimax2 = 360.*deg;
G4double sphere_thetamin2 = 0.*deg;
G4double sphere_thetamax2 = 180.*deg;

G4Sphere* solidShape2 =
  new G4Sphere("Shape2",
               3.*cm,  // Inner radius (0 for a full sphere)
               outer_sphere_radius2,  // Outer radius (for the outer shell)
               sphere_phimin2, sphere_phimax2,
               sphere_thetamin2, sphere_thetamax2);

G4LogicalVolume* logicShape2 =
  new G4LogicalVolume(solidShape2,   // its solid
                      shape2_mat,    // its material
                      "Shape2");     // its name

new G4PVPlacement(0,                // no rotation
                  pos2,             // at position
                  logicShape2,      // its logical volume
                  "Shape2",         // its name
                  logicEnv,         // its mother volume
                  false,            // no boolean operation
                  0,                // copy number
                  checkOverlaps);   // overlaps checking


 // Shape 3 (Outer Outer Sphere)
/* G4Material* shape3_mat = nist->FindOrBuildMaterial("Eljin");
G4ThreeVector pos3 = G4ThreeVector(0, 0, 0);

// Outer Sphere shape
G4double outer_sphere_radius3 = 19.6*cm;  // Adjust the outer radius to fit around the inner sphere
G4double sphere_phimin3 = 0.*deg;
G4double sphere_phimax3 = 360.*deg;
G4double sphere_thetamin3 = 0.*deg;
G4double sphere_thetamax3 = 180.*deg;

G4Sphere* solidShape3 =
  new G4Sphere("Shape3",
               18.6*cm,  // Inner radius (0 for a full sphere)
               outer_sphere_radius3,  // Outer radius (for the outer shell)
               sphere_phimin3, sphere_phimax3,
               sphere_thetamin3, sphere_thetamax3);

G4LogicalVolume* logicShape3 =
  new G4LogicalVolume(solidShape3,   // its solid
                      shape3_mat,    // its material
                      "Shape3");     // its name

new G4PVPlacement(0,                // no rotation
                  pos3,             // at position
                  logicShape3,      // its logical volume
                  "Shape3",         // its name
                  logicEnv,         // its mother volume
                  false,            // no boolean operation
                  0,                // copy number
                  checkOverlaps);   // overlaps checking */
 
/* // Shape 4 (Outer Outer Outer Sphere)
G4Material* shape4_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
G4ThreeVector pos4 = G4ThreeVector(0, 0, 0);

// Outer Sphere shape
G4double outer_sphere_radius4 = 12.*cm;  // Adjust the outer radius to fit around the inner sphere
G4double sphere_phimin4 = 0.*deg;
G4double sphere_phimax4 = 360.*deg;
G4double sphere_thetamin4 = 0.*deg;
G4double sphere_thetamax4 = 180.*deg;

G4Sphere* solidShape4 =
  new G4Sphere("Shape4",
               9.*cm,  // Inner radius (0 for a full sphere)
               outer_sphere_radius4,  // Outer radius (for the outer shell)
               sphere_phimin4, sphere_phimax4,
               sphere_thetamin4, sphere_thetamax4);

G4LogicalVolume* logicShape4 =
  new G4LogicalVolume(solidShape4,   // its solid
                      shape4_mat,    // its material
                      "Shape4");     // its name

new G4PVPlacement(0,                // no rotation
                  pos4,             // at position
                  logicShape4,      // its logical volume
                  "Shape4",         // its name
                  logicEnv,         // its mother volume
                  false,            // no boolean operation
                  0,                // copy number
                  checkOverlaps);   // overlaps checking */

  // Shape 4 (Outer Outer Outer Sphere)
/* G4Material* shape4_mat = nist->FindOrBuildMaterial("GAGG");
G4ThreeVector pos4 = G4ThreeVector(0, 0, 0);

// Outer Sphere shape
G4double outer_sphere_radius4 = 12.8*cm;  // Adjust the outer radius to fit around the inner sphere
G4double sphere_phimin4 = 0.*deg;
G4double sphere_phimax4 = 360.*deg;
G4double sphere_thetamin4 = 0.*deg;
G4double sphere_thetamax4 = 180.*deg;

G4Sphere* solidShape4 =
  new G4Sphere("Shape4",
               10.0*cm,  // Inner radius (0 for a full sphere)
               outer_sphere_radius4,  // Outer radius (for the outer shell)
               sphere_phimin4, sphere_phimax4,
               sphere_thetamin4, sphere_thetamax4);

G4LogicalVolume* logicShape4 =
  new G4LogicalVolume(solidShape4,   // its solid
                      shape4_mat,    // its material
                      "Shape4");     // its name

new G4PVPlacement(0,                // no rotation
                  pos4,             // at position
                  logicShape4,      // its logical volume
                  "Shape4",         // its name
                  logicEnv,         // its mother volume
                  false,            // no boolean operation
                  0,                // copy number
                  checkOverlaps);   // overlaps checking */
 
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
