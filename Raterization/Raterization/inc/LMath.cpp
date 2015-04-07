#include "LMath.h"

double sin_table[361];
double cos_table[361];

void Build_SinCos_Tables()
{
	for (int ang = 0; ang <= 360; ang++)
	{
		double theta = (double)ang * PI / (double)180.0;
		cos_table[ang] = cos(theta);
		sin_table[ang] = sin(theta);

	}
}

double Fast_sin(double theta)
{
	theta = fmod(theta, 360.0);
	if (theta < 0) theta += 360.0;
	int theta_i = (int)theta;
	double theta_d = theta - theta_i;

	return sin_table[theta_i] + theta_d * (sin_table[theta_i + 1] - sin_table[theta_i]);
}

double Fast_cos(double theta)
{
	theta = fmod(theta, 360.0);
	if (theta < 0) theta += 360.0;
	int theta_i = (int)theta;
	double theta_d = theta - theta_i;

	return cos_table[theta_i] + theta_d * (cos_table[theta_i + 1] - cos_table[theta_i]);
}