#pragma once
class Orientation
{
public:
	Orientation(float yaw, float pitch, float roll);
	~Orientation();

	float yaw;
	float pitch;
	float roll;
};

