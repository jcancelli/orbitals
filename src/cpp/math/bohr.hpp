#pragma once

namespace orbitals {

namespace math {

#define BOHR_IN_PM 52.9177210903
#define PM_TO_BOHR(pm) (pm / BOHR_IN_PM)
#define BOHR_TO_PM(bohr) (bohr * BOHR_IN_PM)

double estimateOrbitalRadius(int n);

}  // namespace math

}  // namespace orbitals
