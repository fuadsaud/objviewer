#pragma once
class Camera
{
public:
	Camera(void);
	~Camera(void);
	void calcDirection();

		//direction   eye         radianos  �ngulo 
	float dx, dy, dz, ex, ey, ez, rad,      a;
};

