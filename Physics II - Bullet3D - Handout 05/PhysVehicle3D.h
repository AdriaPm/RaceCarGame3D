#pragma once

#include "PhysBody3D.h"
#include "glmath.h"

class btRaycastVehicle;
struct PhysBody3D;

struct Wheel
{
	vec3 connection; // origin of the ray. Must come from within the chassis
	vec3 direction; 
	vec3 axis;
	float suspensionRestLength; // max length for suspension in meters
	float radius;
	float width;
	bool front; // is front wheel ?
	bool drive; // does this wheel received engine power ?
	bool brake; // does breakes affect this wheel ?
	bool steering; // does this wheel turns ?
};

struct VehicleInfo
{
	~VehicleInfo();
	
	/* VEHICLE PARTS */
	// Main car structure
	vec3 chassis_size;
	vec3 chassis_offset;

	// Front wing structure
	vec3 chassis2_size;
	vec3 chassis2_offset;

	// FrontWing part
	vec3 chassis3_size;
	vec3 chassis3_offset;

	// RearWing stucture 1
	vec3 chassis4_size;
	vec3 chassis4_offset;

	// RearWing stucture 2
	vec3 chassis5_size;
	vec3 chassis5_offset;

	// RearWing part
	vec3 chassis6_size;
	vec3 chassis6_offset;

	// RearWing part 2
	vec3 chassis7_size;
	vec3 chassis7_offset;

	// Motor part 1
	vec3 chassis8_size;
	vec3 chassis8_offset;

	// Motor part 2
	vec3 chassis9_size;
	vec3 chassis9_offset;

	// Motor part 3
	vec3 chassis10_size;
	vec3 chassis10_offset;

	// Cockpit part 1
	vec3 chassis11_size;
	vec3 chassis11_offset;

	// Cockpit part 2
	vec3 chassis12_size;
	vec3 chassis12_offset;

	// Cockpit part 3
	vec3 chassis13_size;
	vec3 chassis13_offset;

	// Steering wheel support
	vec3 chassis14_size;
	vec3 chassis14_offset;

	// Steering wheel
	vec3 chassis15_size;
	vec3 chassis15_offset;

	// Steering wheel display
	vec3 chassis16_size;
	vec3 chassis16_offset;

	// Motor air take hole
	vec3 chassis17_size;
	vec3 chassis17_offset;

	// Pilot body
	vec3 chassis18_size;
	vec3 chassis18_offset;
	
	// Pilot helmet
	vec3 chassis19_size;
	vec3 chassis19_offset;

	// Pilot helmet visor
	vec3 chassis20_size;
	vec3 chassis20_offset;

	// Pilot left arm
	vec3 chassis21_size;
	vec3 chassis21_offset;

	// Pilot right arm
	vec3 chassis22_size;
	vec3 chassis22_offset;


	float mass;
	float suspensionStiffness; // default to 5.88 / 10.0 offroad / 50.0 sports car / 200.0 F1 car
	float suspensionCompression; // default to 0.83
	float suspensionDamping; // default to 0.88 / 0..1 0 bounces / 1 rigid / recommended 0.1...0.3
	float maxSuspensionTravelCm; // default to 500 cm suspension can be compressed
	float frictionSlip; // defaults to 10.5 / friction with the ground. 0.8 should be good but high values feels better (kart 1000.0)
	float maxSuspensionForce; // defaults to 6000 / max force to the chassis

	Wheel* wheels;
	int num_wheels;
};


struct PhysVehicle3D : public PhysBody3D
{
public:
	PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info);
	~PhysVehicle3D();

	void Render();
	void ApplyEngineForce(float force);
	void Brake(float force);
	void Turn(float degrees);
	float GetKmh() const;
	void ResetCarOrientation(float angle = 0);
	vec3 GetForwardVector() const;


public:

	VehicleInfo info;
	btRaycastVehicle* vehicle;
};