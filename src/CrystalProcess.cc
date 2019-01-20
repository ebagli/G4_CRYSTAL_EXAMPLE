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

#include "CrystalProcess.hh"
#include "MaterialExtensionData.hh"
#include "G4CrystalExtension.hh"
#include "G4LogicalCrystalVolume.hh"
#include "G4ExtendedMaterial.hh"

CrystalProcess::
CrystalProcess(const G4String& aName):
G4VDiscreteProcess(aName){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CrystalProcess::~CrystalProcess(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..

G4VParticleChange* CrystalProcess::PostStepDoIt(const G4Track&,
                                                const G4Step&){
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..

G4double CrystalProcess::GetMeanFreePath(const G4Track& aTrack,
                                         G4double,
                                         G4ForceCondition* condition){
    *condition = NotForced;
    G4LogicalVolume* aLV = aTrack.GetVolume()->GetLogicalVolume();
    
    if(G4LogicalCrystalVolume::IsLattice(aLV)){
        G4LogicalCrystalVolume* aLCV = (G4LogicalCrystalVolume*)aLV;
        
        G4cout << aLCV->GetName() << " is a Crystal!" << G4endl;
        G4cout << "Crystal Space Group: " << aLCV->GetCrystal()->GetUnitCell()->GetSpaceGroup() << G4endl;
        
        MaterialExtensionData* data = GetExtension(aTrack);
        if(data != NULL){
            G4cout << "Extended Data Value: " << data->GetValue() << G4endl;
        }
        return DBL_MAX;
    }
    else{
        G4cout << aLV->GetName() <<  " is an Amorphous Material..." << G4endl;
        return DBL_MAX;
    }
    
    
    return DBL_MAX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..

MaterialExtensionData* CrystalProcess::GetExtension(const G4Track& aTrack){
    G4LogicalVolume* aLV = aTrack.GetVolume()->GetLogicalVolume();
    if(aLV->IsExtended() == true){
        G4ExtendedMaterial* aEM = (G4ExtendedMaterial*) aTrack.GetVolume()->GetLogicalVolume()->GetMaterial();
        return (MaterialExtensionData*) aEM->RetrieveExtension("ExtendedData");
    }
    else{
        return nullptr;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..

G4bool CrystalProcess::IsApplicable(const G4ParticleDefinition&){
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..

void CrystalProcess::BuildPhysicsTable(const G4ParticleDefinition&){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..
