#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("Assets/Audio/Music/main_song.ogg", 90);


	// Create world ground
	createGround();

	// Create circuit's road curse
	createRoadCircuit();

	createCheckpoints();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	// Enable/Disable player's camera linked to car
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		isCameraFixed = !isCameraFixed;
	
	// Reset Scene
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		ResetScene(dt);


	// Player's Camera linked to car
	if(isCameraFixed)
		PlayerCamera();




	// Draw basic ground
	p2List_item<Cube>* c = smallCubes.getFirst();
	while (c != NULL) {
		c->data.Render();
		c = c->next;
	}
	
	// Draw Checkpoints
	p2List_item<CheckPoint>* checkItem = checkPointList.getFirst();
	while (checkItem != NULL) {

		if (checkItem->data.passed == false) {
			checkItem->data.cube.Render();
		}
		checkItem = checkItem->next;
	}

	//Draw rocks
	p2List_item<Rocks>* d = rocks.getFirst();
	while (d != NULL) {
		d->data.c1.SetPos(d->data.b1->GetPos().getX(), d->data.b1->GetPos().getY(), d->data.b1->GetPos().getZ());
		d->data.c1.SetEulerRotation(d->data.b1->GetRotation());
		d->data.c1.Render();

		d->data.c2.SetPos(d->data.b2->GetPos().getX(), d->data.b2->GetPos().getY(), d->data.b2->GetPos().getZ());
		d->data.c2.SetEulerRotation(d->data.b2->GetRotation());
		d->data.c2.Render();

		d->data.c3.SetPos(d->data.b3->GetPos().getX(), d->data.b3->GetPos().getY(), d->data.b3->GetPos().getZ());
		d->data.c3.SetEulerRotation(d->data.b3->GetRotation());
		d->data.c3.Render();
		d = d->next;
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::PlayerCamera() {
	
	if (App->player->position.getY() > CAMERA_Y_LIMIT) 
	{
		float cameraDistance = 10;

		float cameraX = App->player->position.getX() - cameraDistance * App->player->GetVehicleForwardVector().x;
		float cameraY = App->player->position.getY() - cameraDistance * App->player->GetVehicleForwardVector().y + 4;
		float cameraZ = App->player->position.getZ() - cameraDistance * App->player->GetVehicleForwardVector().z;

		App->camera->Position = { cameraX, cameraY, cameraZ };

		float posX = App->player->position.getX();
		float posY = App->player->position.getY();
		float posZ = App->player->position.getZ();

		//Set viewport
		App->camera->LookAt(vec3(posX, posY, posZ));
	}
	else 
	{
		float posX = App->player->position.getX();
		float posY = App->player->position.getY();
		float posZ = App->player->position.getZ();

		//Set viewport
		App->camera->LookAt(vec3(posX, posY, posZ));
	}

}

void ModuleSceneIntro::createRoadCircuit()
{

	//Rampa 1
	addCubeToMap({ 0, 1, 100 }, { 50, 2, 30 }, White, -10, true, false, false);

	//Rampa 2
	addCubeToMap({ -168, 1, 75 }, { 45, 2, 30 }, White, 10, true, false, false);

	//Left
	addCubeToMap({ 25, 1, 100 }, { 2, 2, 100 }, Grey, 0, false, false, false);
	addCubeToMap({ 10, 1, 165 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -15, 1, 190 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -75, 1, 210 }, { 100, 2, 2 }, Grey, 0, false, false, false);
	addCubeToMap({ -190, 1, 100 }, { 250, 2, 2 }, Grey, 90, false, true, false);
	addCubeToMap({ -90, 1, -20 }, { 2, 2, 200 }, Grey, 90, false, true, false);
	addCubeToMap({ 10, 1, 0 }, { 2, 2, 50 }, Grey, 55, false, true, false);
	addCubeToMap({ 25, 1, 25 }, { 2, 2, 50 }, Grey, 0, false, true, false);
	//Right
	addCubeToMap({ -25, 1, 100 }, { 2, 2, 100 }, Grey, 0, false, false, false);
	addCubeToMap({ -40, 1, 165 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -100, 1, 180 }, { 100, 2, 2 }, Grey, 0, false, false, false);
	addCubeToMap({ -145, 1, 210 }, { 100, 2, 2 }, Grey, 0, false, false, false);
	addCubeToMap({ -145, 1, 130 }, { 100, 2, 2 }, Grey, 90, false, true, false);
	addCubeToMap({ -145, 1, 70 }, { 50, 2, 2 }, Grey, 90, false, true, false);
	addCubeToMap({ -85, 1, 45 }, { 120, 2, 2 }, Grey, 0, false, false, false);
	addCubeToMap({ -25, 1, 46.5 }, { 2, 2, 7 }, Grey, 0, false, false, false);

	//Water
	addCheckpoint({ -85, 1, 12 }, { 120, 0.50f, 65 }, Blue, 0, false, false, false, 6);

	//Rocks
	addRock({ 0,-5,80 }, 0);
	addRock({ -10,-5,145 }, 0);
	addRock({ -40,-5,175 }, 0);
	addRock({ -75,-5,185 }, 0);
	addRock({ -100,-5,190 }, 0);
	addRock({ -165,-5,190 }, 0);
	addRock({ -170,-5,165 }, 0);
	addRock({ -163,-5, 125 }, 0);
	addRock({ -163,-5, 100 }, 0);
	addRock({ -168,-5, 75 }, 0);
	addRock({ -162,-5, 45 }, 0);
	addRock({ -160,-5, 25 }, 0);
	addRock({ -145,-5, 10 }, 0);
	addRock({ -120,-5, 5 }, 0);
	addRock({ -90,-5, 2 }, 0);
	addRock({ -55,-5, 7 }, 0);
	addRock({ -55,-5, 20 }, 0);
	addRock({ -35,-5, 15 }, 0);
	addRock({ -15,0, 25 }, 0);

}



void ModuleSceneIntro::createCheckpoints() {
	//Lap1
	addCheckpoint({ 0, 1, 50 }, { 50, 1, 1 }, Purple, 0, false, false, false, 1, false);
	addCheckpoint({ 0, 1, 150 }, { 50, 1, 1 }, Yellow, 0, false, false, false, 2, false);
	addCheckpoint({ -165, 1, 195 }, { 50, 1, 1 }, Blue, 40, false, true, false, 3, false);
	addCheckpoint({ -167, 1, 50 }, { 45, 1, 1 }, Orange, 0, false, false, false, 4, false);
	addCheckpoint({ -90, 1, 10 }, { 70, 1, 1 }, Black, 90, false, true, false, 5, false);
}

void ModuleSceneIntro::createGround() {
	Cube groundToAdd;

	float groundTerrainSize = 40;	// Change this value to increase/decrease basic ground size

	groundToAdd.size = { groundTerrainSize, 1, groundTerrainSize };

	int type = 0;
	// X-axis
	for (int i = 0; i < 10; i++)
	{
		// Z-axis
		for (int j = 0; j < 10; j++) {

			groundToAdd.SetPos(i * -groundTerrainSize + groundTerrainSize, 0, j * groundTerrainSize);

			switch (groundCoordinates[i][j])
			{
			case 0:
				groundToAdd.color = White;	// Ground color

				App->physics->AddBody(groundToAdd, 0);
				smallCubes.add(groundToAdd);

				break;
			}
		}
	}
}

void ModuleSceneIntro::addCubeSensorToMap(vec3 pos, vec3 size, Color rgb, int angle, bool rot_X, bool rot_Y, bool rot_Z, int id)
{
	Cube cube;

	cube.SetPos(pos.x, pos.y, pos.z);
	cube.size = size;
	cube.color = rgb;

	if (rot_X == true) 
		cube.SetRotation(angle, { 1, 0, 0 });	// X-axis
	if (rot_Y == true)
		cube.SetRotation(angle, { 0, 1, 0 });	// Y-axis
	if (rot_Z == true)
		cube.SetRotation(angle, { 0, 0, 1 });	// Z-axis

	PhysBody3D* sensor_cube = App->physics->AddBody(cube, 0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->id = id;
	smallCubes.add(cube);
}

void ModuleSceneIntro::addCubeToMap(vec3 pos, vec3 size, Color rgb, int angle, bool rot_X, bool rot_Y, bool rot_Z)
{
	Cube cube;

	cube.SetPos(pos.x, pos.y, pos.z);
	cube.size = size;
	cube.color = rgb;

	if (rot_X == true) 
		cube.SetRotation(angle, { 1, 0, 0 });	// X-axis
	if (rot_Y == true)
		cube.SetRotation(angle, { 0, 1, 0 });	// Y-axis
	if (rot_Z == true)
		cube.SetRotation(angle, { 0, 0, 1 });	// Z-axis

	App->physics->AddBody(cube, 0);
	smallCubes.add(cube);
}

void ModuleSceneIntro::addCheckpoint(vec3 pos, vec3 size, Color rgb, int angle, bool rot_X, bool rot_Y, bool rot_Z, int id, bool passed_)
{
	Cube cube;

	cube.SetPos(pos.x, pos.y, pos.z);
	cube.size = size;
	cube.color = rgb;

	if (rot_X == true) 
		cube.SetRotation(angle, { 1, 0, 0 });	// X-axis
	if (rot_Y == true)
		cube.SetRotation(angle, { 0, 1, 0 });	// Y-axis
	if (rot_Z == true)
		cube.SetRotation(angle, { 0, 0, 1 });	// Z-axis

	CheckPoint checkpoint;
	checkpoint.body = App->physics->AddBody(cube, 0.0f);
	checkpoint.body->SetAsSensor(true);
	checkpoint.body->SetId(id);
	checkpoint.cube = cube;
	checkpoint.passed = passed_;
	checkPointList.add(checkpoint);

	if (id == 6)
		water = checkpoint;
}

void ModuleSceneIntro::addRock(vec3 position, float angle) 
{
	Cube cube1, cube2, cube3;
	
	// Cube 1
	cube1.size = { 2, 2, 2 };
	cube1.SetPos(position.x, position.y, position.z);
	cube1.SetRotation(angle, { 0, 1, 0 });
	cube1.color = DarkGrey;

	// Cube 2
	cube2.size = { 2, 2, 3 };
	cube2.SetPos(position.x, position.y, position.z);
	cube2.SetRotation(angle, { 0, 1, 0 });
	cube2.color = DarkGrey;

	// Cube 3
	cube3.size = { 3, 3, 3 };
	cube3.SetPos(position.x, position.y, position.z);
	cube3.SetRotation(angle, { 0, 1, 0 });
	cube3.color = DarkGrey;

	btTransform frameA;
	frameA.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameA.setOrigin(btVector3(0, 0, 0));

	btTransform frameB;
	frameB.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameB.setOrigin(btVector3(0, 0, 0));

	Rocks rock;
	rock.c1 = cube1;
	rock.c2 = cube2;
	rock.c3 = cube3;
	rock.b1 = App->physics->AddBody(rock.c1, 1);
	rock.b2 = App->physics->AddBody(rock.c2, 1);
	rock.b3 = App->physics->AddBody(rock.c3, 1);
	rock.pos = position;

	// Add rocks as SLIDER Constrains
	App->physics->AddConstraintSlider(*rock.b1, *rock.b2, frameA, frameB);
	App->physics->AddConstraintSlider(*rock.b1, *rock.b3, frameA, frameB);
	App->physics->AddConstraintSlider(*rock.b2, *rock.b3, frameA, frameB);

	rocks.add(rock);

}

void ModuleSceneIntro::ResetScene(float dt)
{
	App->player->resetCarPos();
	
	float timer = 0;
	while (timer < 150) {
		timer+=1*dt;
		LOG("TIMERRRRRR: %float", timer);
	}

	// Draw Checkpoints
	p2List_item<CheckPoint>* checkReset = checkPointList.getFirst();
	while (checkReset != NULL) {

		checkReset->data.passed = false;

		checkReset = checkReset->next;
	}

	App->player->checkpointCount = 0;
	App->player->gameTimer = 120;
}