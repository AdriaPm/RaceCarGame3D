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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

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



	// Player's Camera
	PlayerCamera();



	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::PlayerCamera() {
	
	if (App->player->position.getY() > CAMERA_Y_LIMIT) 
	{
		float cameraDistance = 12;

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