#pragma once
class Vehicle
{
public:
	Vehicle()
	{
	}

	~Vehicle()
	{
	}

	static void SetOwnshipVehicle(double lat, double lon, double heading);
	static void UpdateOwnship(double lat, double lon, double heading);
};