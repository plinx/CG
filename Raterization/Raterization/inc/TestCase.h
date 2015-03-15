#ifndef TestCase_h
#define TestCase_h

#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Vec.h"
#include "Matrix.h"
#include "Quat.h"
#include "LMath.h"

class TestLog {
public:
	std::ofstream file;

	TestLog() = default;
	~TestLog() = default;
	TestLog(const std::string path) : file(path, std::ofstream::app) {}

	void Init(const std::string path) { file.open(path, std::ofstream::app); }
	void Close() { file.close(); }

	template <typename T>
	TestLog& operator<<(const T& str) {
		std::cout << str;
		//file << str;
		return *this;
	}
};

void AutoTest();
void VectorTest(TestLog& log);
void MatrixTest(std::ofstream& log);

#endif