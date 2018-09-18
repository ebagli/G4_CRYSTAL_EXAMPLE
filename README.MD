# Crystal usage in Geant4

Enrico Bagli - INFN (Italy)
bagli@fe.infn.it

## 1. INTRODUCTION
This example shows how to add extension to a `G4Material` and use them in a process.
The application requires [Geant4 10.3](www.geant4.org). Geant4 is a toolkit for the simulation of the passage of particles through matter. Its areas of application include high energy, nuclear and accelerator physics, as well as studies in medical and space science. The three main reference papers for Geant4 are:
- [Nuclear Instruments and Methods in Physics Research A 506 (2003) 250-303](http://www.sciencedirect.com/science/article/pii/S0168900203013688)
- [IEEE Transactions on Nuclear Science 53 No. 1 (2006) 270-278](http://ieeexplore.ieee.org/xpls/abs_all.jsp?isnumber=33833&arnumber=1610988&count=33&index=7)
- [Nuclear Instruments and Methods in Physics Research A 835 (2016) 186-225](http://www.sciencedirect.com/science/article/pii/S0168900216306957)

The source code can be found on the [Geant4 10.3](www.geant4.org) website or on [GitHub](https://github.com/Geant4/geant4/tree/geant4-10.3-release). After the installation of the Geant4 10.3 libraries, the code can be compiled via [CMake](www.cmake.org).
The project has been financed by the INFN under the INFN-CSNV-GECO project.

## 2. SETUP
The setup is composed by two close cubes of 1x1x1 mm3 made of:
- Amorphous Silicon
- Crystal Silicon

The crystal is constructed instantiating a `G4ExtendedMaterial` with a name and a pointer to a `G4Material`.
Then, two extensions are added to the `G4ExtendedMaterial`:
- `G4CrystalExtension` that collects the basic information of the crystal structure.
- `MaterialExtensionData` that collects the information needed by the `CrystalProcess` process.

## 3. PRIMARY EVENT
The `geantino` particles are used.

## 4. PHYSICS
The `CrystalPhysics` is added to the `QGSP_BERT` physics list in the `crystal.cc` main file.
The `CrystalPhysics` class attach the `CrystalProcess` to all the particles.
The `CrystalProcess` check if the logical volume is a `G4LogicalCrystalVolume` or a `G4LogicalVolume`:
If the logical volume is a `G4LogicalCrystalVolume`, the process prints the crystal space group and the the value stored in the `MaterialExtensionData` attached to the Silicon crystal.


## 5. EXECUTION & OUTPUT 
The example can be executed with the command line
`./crystal crystal.in`

The output is standard output stream with information on the material and the values stored in the extensions of the extended material.
