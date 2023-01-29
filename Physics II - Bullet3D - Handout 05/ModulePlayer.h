#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 5000.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 3000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	vec3 GetVehicleForwardVector();

	void resetCarPos();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float backwardsAcceleration;
	float brake;

	btVector3 position;

	vec3 initialPosition = { 0, 0, 0 };



};