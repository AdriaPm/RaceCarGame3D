#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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


	// Create world ground
	createGround();

	// Create circuit's road curse
	createRoadCircuit();



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


	// Player's Camera linked to car
	if(isCameraFixed)
		PlayerCamera();




	// Draw basic ground
	p2List_item<Cube>* c = smallCubes.getFirst();
	while (c != NULL) {
		c->data.Render();
		c = c->next;
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

	addCubeToMap({ 0, 1, 100 }, { 50, 2, 30 }, White, -10, true, false, false);
	addCubeToMap({ 25, 1, 100 }, { 2, 2, 100 }, Grey, 0, false, false, false);
	addCubeToMap({ -25, 1, 100 }, { 2, 2, 100 }, Grey, 0, false, false, false);
	addCubeToMap({ 10, 1, 165 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -40, 1, 165 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -15, 1, 190 }, { 2, 2, 50 }, Grey, -45, false, true, false);
	addCubeToMap({ -100, 1, 180 }, { 100, 2, 2 }, Grey, 0, false, false, false);
	addCubeToMap({ -75, 1, 210 }, { 100, 2, 2 }, Grey, 0, false, false, false);
	
	addCubeToMap({ -145, 1, 210 }, { 100, 2, 2 }, Grey, 0, false, false, false);



}



void ModuleSceneIntro::createGround() {
	Cube groundToAdd;

	float groundTerrainSize = 60;	// Change this value to increase/decrease basic ground size

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
				groundToAdd.color = Orange;	// Ground color

				App->physics->AddBody(groundToAdd, 0);
				smallCubes.add(groundToAdd);

				break;
			}
		}
	}
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