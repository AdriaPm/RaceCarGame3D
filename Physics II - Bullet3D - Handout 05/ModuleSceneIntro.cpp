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

	/*App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));*/

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
				groundToAdd.color = Orange;	// Ground color

				App->physics->AddBody(groundToAdd, 0);
				smallCubes.add(groundToAdd);

				break;
			}
		}
	}
}