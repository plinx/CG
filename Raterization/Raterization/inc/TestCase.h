#ifndef TestCase_h
#define TestCase_h

#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <fstream>

#include "Vec.h"
#include "Matrix.h"
#include "Quat.h"
#include "LMath.h"

void AutoTest();
void VectorTest(std::ofstream& log);
void MatrixTest(std::ofstream& log);

#endif