#pragma once
#include <algorithm>
#define PI 3.1415927f

//vector and matrix classes modified from assaultcube source
//Lots of unnecesary stuff

struct vec3_t
{
	float x, y, z;

	vec3_t() { x = y = z = 0; }
	vec3_t(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3_t(float a, float b) : x(a), y(b), z(0) {}

	vec3_t(float *v) : x(v[0]), y(v[1]), z(v[2]) {}

	bool iszero() const { return x == 0 && y == 0 && z == 0; }
	bool operator!() const { return x == 0 && y == 0 && z == 0; }

	bool operator==(const vec3_t &o) const { return x == o.x && y == o.y && z == o.z; }
	bool operator!=(const vec3_t &o) const { return x != o.x || y != o.y || z != o.z; }
	vec3_t operator-() const { return vec3_t(-x, -y, -z); }

	vec3_t &mul(float f) { x *= f; y *= f; z *= f; return *this; }
	vec3_t &div(float f) { x /= f; y /= f; z /= f; return *this; }
	vec3_t &add(float f) { x += f; y += f; z += f; return *this; }
	vec3_t &sub(float f) { x -= f; y -= f; z -= f; return *this; }

	vec3_t &add(const vec3_t &o) { x += o.x; y += o.y; z += o.z; return *this; }
	vec3_t &sub(const vec3_t &o) { x -= o.x; y -= o.y; z -= o.z; return *this; }

	float squaredlen() const { return x*x + y*y + z*z; }
	float sqrxy() const { return x*x + y*y; }

	float dot(const vec3_t &o) const { return x*o.x + y*o.y + z*o.z; }
	float dotxy(const vec3_t &o) const { return x*o.x + y*o.y; }

	float magnitude() const { return sqrtf(squaredlen()); }
	vec3_t &normalize() { div(magnitude()); return *this; }

	float dist(const vec3_t &e) const { vec3_t t; return dist(e, t); }
	float dist(const vec3_t &e, vec3_t &t) const { t = *this; t.sub(e); return t.magnitude(); }

	float Get2DDist(const vec3_t &e) const { float dx = e.x - x, dy = e.y - y; return sqrtf(dx*dx + dy*dy); }

	float magnitudexy() const { return sqrtf(x*x + y*y); }

	vec3_t &cross(const vec3_t &a, const vec3_t &b) { x = a.y*b.z - a.z*b.y; y = a.z*b.x - a.x*b.z; z = a.x*b.y - a.y*b.x; return *this; }
	float cxy(const vec3_t &a) { return x*a.y - y*a.x; }

	vec3_t scaleFixedPoint(float scalex, float scaley, vec3_t fixedPoint)
	{
		vec3_t newvec;
		newvec.x = x * scalex + fixedPoint.x*(1 - scalex);
		newvec.y = y * scaley + fixedPoint.y*(1 - scaley);
		return newvec;
	}

	bool WorldToScreen(float fovx, float fovy, float windowWidth, float windowHeight, vec3_t left, vec3_t up, vec3_t forward, vec3_t origin, vec3_t &screen)
	{
		vec3_t transform;
		float xc, yc;
		float px, py;
		float z;

		px = tan(fovx * PI / 360.0);
		py = tan(fovy * PI / 360.0);

		transform = this->sub(origin); //this = destination

		xc = windowWidth / 2.0;
		yc = windowHeight / 2.0;

		z = transform.dot(left);
		if (z <= 0.1) { return false; }

		screen.x = xc - transform.dot(up) *xc / (z*px);
		screen.y = yc - transform.dot(forward) *yc / (z*py);
		return true;
	}
};

struct vec4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};
	vec4() {}
	explicit vec4(const vec3_t &p, float w = 0) : x(p.x), y(p.y), z(p.z), w(w) {}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	float &operator[](int i) { return v[i]; }
	float  operator[](int i) const { return v[i]; }
};

struct glmatrixf
{
	float v[16];

	float operator[](int i) const { return v[i]; }
	float &operator[](int i) { return v[i]; }

#define MULMAT(row, col) v[col + row] = x[row]*y[col] + x[row + 4]*y[col + 1] + x[row + 8]*y[col + 2] + x[row + 12]*y[col + 3];

	template<class XT, class YT>
	void mul(const XT x[16], const YT y[16])
	{
		MULMAT(0, 0); MULMAT(1, 0); MULMAT(2, 0); MULMAT(3, 0);
		MULMAT(0, 4); MULMAT(1, 4); MULMAT(2, 4); MULMAT(3, 4);
		MULMAT(0, 8); MULMAT(1, 8); MULMAT(2, 8); MULMAT(3, 8);
		MULMAT(0, 12); MULMAT(1, 12); MULMAT(2, 12); MULMAT(3, 12);
	}

#undef MULMAT

	void mul(const glmatrixf &x, const glmatrixf &y)
	{
		mul(x.v, y.v);
	}

	void translate(float x, float y, float z)
	{
		v[12] += x;
		v[13] += y;
		v[14] += z;
	}

	void translate(const vec3_t &o)
	{
		translate(o.x, o.y, o.z);
	}

	void scale(float x, float y, float z)
	{
		v[0] *= x; v[1] *= x; v[2] *= x; v[3] *= x;
		v[4] *= y; v[5] *= y; v[6] *= y; v[7] *= y;
		v[8] *= z; v[9] *= z; v[10] *= z; v[11] *= z;
	}

	void invertnormal(vec3_t &dir) const
	{
		vec3_t n(dir);
		dir.x = n.x*v[0] + n.y*v[1] + n.z*v[2];
		dir.y = n.x*v[4] + n.y*v[5] + n.z*v[6];
		dir.z = n.x*v[8] + n.y*v[9] + n.z*v[10];
	}

	void invertvertex(vec3_t &pos) const
	{
		vec3_t p(pos);
		p.x -= v[12];
		p.y -= v[13];
		p.z -= v[14];
		pos.x = p.x*v[0] + p.y*v[1] + p.z*v[2];
		pos.y = p.x*v[4] + p.y*v[5] + p.z*v[6];
		pos.z = p.x*v[8] + p.y*v[9] + p.z*v[10];
	}

	void transform(const vec3_t &in, vec4 &out) const
	{
		out.x = transformx(in);
		out.y = transformy(in);
		out.z = transformz(in);
		out.w = transformw(in);
	}

	float transformx(const vec3_t &p) const
	{
		return p.x*v[0] + p.y*v[4] + p.z*v[8] + v[12];
	}

	float transformy(const vec3_t &p) const
	{
		return p.x*v[1] + p.y*v[5] + p.z*v[9] + v[13];
	}

	float transformz(const vec3_t &p) const
	{
		return p.x*v[2] + p.y*v[6] + p.z*v[10] + v[14];
	}

	float transformw(const vec3_t &p) const
	{
		return p.x*v[3] + p.y*v[7] + p.z*v[11] + v[15];
	}

	vec3_t gettranslation() const
	{
		return vec3_t(v[12], v[13], v[14]);
	}

	//assault cube world2screen
	vec3_t transform(glmatrixf *matrix, vec3_t &totransform)
	{
		return vec3_t(matrix->transformx(totransform),
			matrix->transformy(totransform),
			matrix->transformz(totransform)).div(matrix->transformw(totransform));
	}
};

vec3_t Subtract(vec3_t src, vec3_t dst);

float Magnitude(vec3_t vec);

float Distance(vec3_t src, vec3_t dst);

vec3_t Normalize(vec3_t src);

vec3_t CalcAngle(vec3_t src, vec3_t dst);

bool WorldToScreen(vec3_t pos, vec3_t &screen, float v[16], int windowWidth, int windowHeight);

float DifferenceOfAngles(vec3_t src, vec3_t dst);