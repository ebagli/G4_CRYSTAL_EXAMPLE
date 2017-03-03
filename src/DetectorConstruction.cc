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

#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4CrystalExtension.hh"
#include "G4ExtendedMaterial.hh"
#include "G4LogicalCrystalVolume.hh"

#include "MaterialExtensionData.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void DetectorConstruction::DefineMaterials(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct(){
    //** World **//
    G4Material* Galactic = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
    
    G4double fWorldSize = 50. * CLHEP::millimeter;
    
    G4Box* fWorldSolid = new G4Box("World",
                                   fWorldSize/2.,
                                   fWorldSize/2.,
                                   fWorldSize/2.);
    
    G4LogicalVolume* fWorldLogic = new G4LogicalVolume(fWorldSolid,
                                                       Galactic,
                                                       "World");
    
    G4PVPlacement* fWorldPhysical = new G4PVPlacement(0,
                                                      G4ThreeVector(),
                                                      fWorldLogic,
                                                      "World",
                                                      0,
                                                      false,
                                                      0);
    
    
    G4double fBoxSize = 2 * CLHEP::millimeter;
    
    G4Box* fBoxSolid = new G4Box("SiCrystal",
                                 fBoxSize/2.,
                                 fBoxSize/2.,
                                 fBoxSize/2.);
    
    //** Amorphous Definition Start**//
    G4Material* Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
    
    G4LogicalVolume* fBoxLogic = new G4LogicalVolume(fBoxSolid,Si,"Si");
    
    new G4PVPlacement(0,
                      G4ThreeVector(fBoxSize*1./2.,0.,0.),
                      fBoxLogic,"Si",
                      fWorldLogic,
                      false,
                      0);
    
    //** Amorphous Definition End**//
    
    
    //** Crystal Definition Start**//
    
    G4ExtendedMaterial* Crystal = new G4ExtendedMaterial("crystal.material",Si);
    
    Crystal->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal)));
    G4CrystalExtension* crystalExtension = (G4CrystalExtension*)Crystal->RetrieveExtension("crystal");
    crystalExtension->SetUnitCell(new G4CrystalUnitCell(5.43 * CLHEP::angstrom,
                                                        5.43 * CLHEP::angstrom,
                                                        5.43 * CLHEP::angstrom,
                                                        CLHEP::halfpi,
                                                        CLHEP::halfpi,
                                                        CLHEP::halfpi,
                                                        227));
    
    Crystal->RegisterExtension(std::unique_ptr<MaterialExtensionData>(new MaterialExtensionData("ExtendedData")));
    MaterialExtensionData* materialExtension = (MaterialExtensionData*)Crystal->RetrieveExtension("ExtendedData");
    materialExtension->SetValue(57.);
    
    G4LogicalCrystalVolume* fBoxLogicCrystal = new G4LogicalCrystalVolume(fBoxSolid,
                                                                          Crystal,
                                                                          "crystal.logic");
    
    new G4PVPlacement(0,
                      G4ThreeVector(fBoxSize*3./2.,0.,0.),
                      fBoxLogicCrystal,"crystal.physical",
                      fWorldLogic,
                      false,
                      0);
    //** Crystal Definition End**//
    
    return fWorldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..
