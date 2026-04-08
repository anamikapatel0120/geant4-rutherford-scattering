# Geant4 Rutherford Scattering Simulation

## Overview

This project simulates Rutherford scattering using Geant4. A beam of alpha particles is directed towards a thin gold foil, and the scattering angles are recorded using a surrounding detector.

The goal is to study how alpha particles deflect after interacting with the gold nucleus.

---

## What the Simulation Does

* Generates alpha particles with fixed energy (5 MeV)
* Sends them along the +z direction
* Places a thin gold foil in their path
* Surrounds the foil with a spherical silicon detector
* Records the scattering angle when a particle reaches the detector
* Stores the results in a file for further analysis

---

## Geometry

* **World**: Air
* **Target**: Thin gold foil placed at z = 3 mm
* **Detector**: Spherical shell (silicon) around the foil

The detector captures particles scattered in all directions.

---

## Physics

* Physics list used: `QBBC`
* Only alpha particles are considered
* Scattering angle is computed using particle momentum direction

---

## How It Works

1. Alpha particle is generated at the origin
2. It travels towards the gold foil
3. It interacts with the foil and gets scattered
4. When it enters the detector:

   * The angle is calculated
   * Value of θ and sin(θ/2) are stored
   * Particle is stopped

---

## Output

The simulation creates a file:

```id="file1"
rutherford_angles.txt
```

It contains:

* Event ID
* Scattering angle (in degrees)
* sin(θ/2)

Example format:

```id="file2"
EventID    Angle(deg)    sin(theta/2)
0          25.3          0.219
1          40.1          0.342
```

---

## How to Run

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
Run the simulation
Release\exampleB1.exe 
```

You can also pass number of events:

```bash
./exampleB1.exe 100000
```

---

## Key Files

* `PrimaryGeneratorAction` → Defines alpha particle source
* `DetectorConstruction` → Defines foil and detector
* `SteppingAction` → Detects particle and computes angle
* `RunAction` → Stores and writes results to file

---

## Possible Improvements

* Plot angular distribution and compare with theory
* Add multiple detector segments for better resolution
* Vary particle energy
* Use different target materials

---

## Author

Anamika Patel
Engineering Physics, IIT Roorkee
