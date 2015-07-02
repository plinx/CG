#include "LMath.h"

float sin_table[361];
float cos_table[361];

void Build_SinCos_Tables()
{
	for (int ang = 0; ang <= 360; ang++)
	{
		float theta = (float)ang * PI / (float)180.0;
		cos_table[ang] = cos(theta);
		sin_table[ang] = sin(theta);

	}
}

float Fast_sin(float theta)
{
	theta = fmodf(theta, 360.0);
	if (theta < 0) theta += 360.0;
	int theta_i = (int)theta;
	float theta_d = theta - theta_i;

	return sin_table[theta_i] + theta_d * (sin_table[theta_i + 1] - sin_table[theta_i]);
}

float Fast_cos(float theta)
{
	theta = fmodf(theta, 360.0);
	if (theta < 0) theta += 360.0;
	int theta_i = (int)theta;
	float theta_d = theta - theta_i;

	return cos_table[theta_i] + theta_d * (cos_table[theta_i + 1] - cos_table[theta_i]);
}