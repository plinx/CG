#ifndef Pixel_h
#define Pixel_h

class Pixel
{
private:
	PBYTE point;

public:
	Pixel() = default;
	~Pixel() = default;

	void setPoint(PBYTE p) { point = p; }
	void setR(double red) { point[2] = (BYTE)red; }
	void setG(double green) { point[1] = (BYTE)green; }
	void setB(double blue) { point[0] = (BYTE)blue; }
	void Next() { point += 3; }

};

#endif