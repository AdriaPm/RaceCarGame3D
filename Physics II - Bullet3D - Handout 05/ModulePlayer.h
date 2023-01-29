#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 3000.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 2000.0f
#define MAX_VELOCITY 150.0f
#define MAX_VELOCITY_TURBO 200.0f
#define DEATH_FIELD_FALL_DISTANCE -300

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	vec3 GetVehicleForwardVector();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void resetCarPos();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float backwardsAcceleration;
	float brake;

	btVector3 position;

	vec3 initialPosition = { 0, 0, 0 };

	bool isDragForceEnabled = true;
	bool isBuoyancyForceEnabled = true;

	float gameTimer = 250;
	int laps = 0;

private:

	int checkpointCount = 0;

	uint turboSFX = 0;
	bool isTurboSFXPlayed = false;

	uint engineSFX = 0;
	bool isEngineSFXPlayed = false;

};