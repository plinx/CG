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
	void setR(BYTE red) { point[3] = red; }
	void setG(BYTE green) { point[2] = green; }
	void setB(BYTE blue) { point[1] = blue; }
	void Next() { point += 3; }

};

#endif