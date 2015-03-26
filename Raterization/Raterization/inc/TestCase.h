#ifndef TestCase_h
#define TestCase_h

#include "..\stdafx.h"

void AutoTest();
void VectorTest();
template <typename T>
void VectorTest(T& v0, T& v1, T& v2, T& v3);
void MatrixTest();

#endif