#include "geom.h"

vec3 Add(vec3 src, vec3 dst)
{
	vec3 sum;
	sum.x = src.x + dst.x;
	sum.y = src.y + dst.y;
	sum.z = src.z + dst.z;
	return sum;
}

vec3 Subtract(vec3 src, vec3 dst)
{
	vec3 diff;
	diff.x = src.x - dst.x;
	diff.y = src.y - dst.y;
	diff.z = src.z - dst.z;
	return diff;
}

vec3 Divide(vec3 src, float num)
{
	vec3 vec;
	vec.x = src.x / num;
	vec.y = src.y / num;
	vec.z = src.z / num;

	return vec;
}

float DotProduct(vec3 src, vec3 dst)
{
	return src.x * dst.x + src.y * dst.y + src.z * dst.z;
}

float Magnitude(vec3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float Distance(vec3 src, vec3 dst)
{
	vec3 diff = Subtract(src, dst);
	return Magnitude(diff);
}

vec3 Normalize(vec3 src)
{
	vec3 vec = Divide(src, Magnitude(src));
	return vec;
}

vec3 CalcAngle(vec3 src, vec3 dst)
{
	vec3 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / Distance(src, dst)) * 180.0f / PI;
	angle.z = 0.0f;

	return angle;
}

float DifferenceOfAngles(vec3 src, vec3 dst)
{
	vec3 diff;

	diff.y = src.y - dst.y;
	diff.x = src.x - dst.x;

	//normalize by making them positive values if they are negative
	if (diff.y < 0)
	{
		diff.y *= -1;
	}
	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	//add them together and divide by 2, gives an average of the 2 angles
	float fDifference = (diff.y + diff.x) / 2;
	return fDifference;
}

bool WorldToScreen(vec3 pos, vec3& screen, float matrix[16], int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool WorldToScreen2(vec3 src, vec3 dst, vec3& screen, float fovx, float fovy, float windowWidth, float windowHeight, vec3 left, vec3 up, vec3 forward)
{
	vec3 transform;
	float xc, yc;
	float px, py;
	float z;

	px = tan(fovx * PI / 360.0);
	py = tan(fovy * PI / 360.0);

	transform = Subtract(dst, src);

	xc = windowWidth / 2.0;
	yc = windowHeight / 2.0;

	z = DotProduct(transform, left);

	if (z <= 0.1)
	{
		return false;
	}

	screen.x = xc - DotProduct(transform, up) * xc / (z * px);
	screen.y = yc - DotProduct(transform, forward) * yc / (z * py);

	return true;
}