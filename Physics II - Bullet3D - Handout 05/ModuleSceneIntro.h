#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define CAMERA_Y_LIMIT -30


struct PhysBody3D;
struct PhysMotor3D;


struct Rocks
{
	vec3 pos;
	PhysBody3D* b1, * b2, * b3;
	Cube c1, c2, c3;
};

struct CheckPoint 
{
	PhysBody3D* body;
	Cube cube;
	bool passed;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void PlayerCamera();

	void ResetScene(float dt);

	void createGround();
	void createRoadCircuit();
	void createCheckpoints();

	// Geometry shapes
	void addCubeToMap(vec3 pos, vec3 size, Color rgb, int angle = 0, bool rot_X = false, bool rot_Y = false, bool rot_Z = false);
	void addCubeSensorToMap(vec3 pos, vec3 size, Color rgb, int angle = 0, bool rot_X = false, bool rot_Y = false, bool rot_Z = false, int id = -1);
	void addRock(vec3 position, float angle);
	void addCheckpoint(vec3 pos, vec3 size, Color rgb, int angle = 0, bool rot_X = false, bool rot_Y = false, bool rot_Z = false, int id = -1, bool passed_ = false);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	p2List<Cube> smallCubes;
	p2List<Rocks> rocks;
	p2List<CheckPoint> checkPointList;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	CheckPoint water;

private:

	bool isCameraFixed = true;

	int groundCoordinates[10][10] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
};