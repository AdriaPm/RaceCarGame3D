#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	turboSFX = App->audio->LoadFx("Assets/Audio/Fx/turboSFX.wav");
	engineSFX = App->audio->LoadFx("Assets/Audio/Fx/engineSFX.wav");

	VehicleInfo car;

	// Car chasis --------------------------------------------
	// Main car structure
	car.chassis_size.Set(2, .3f, 5);
	car.chassis_offset.Set(0, 1.5, 0);

	// FrontWing structure
	car.chassis2_size.Set(1.0f, .5f, 1.3f);
	car.chassis2_offset.Set(0, 1.3f, 3.0);

	// FrontWing part
	car.chassis3_size.Set(3.0f, .25f, .75f);
	car.chassis3_offset.Set(0, 1.15f, 4.0);

	// RearWing stucture 1
	car.chassis4_size.Set(.25f, 1.0f, .75f);
	car.chassis4_offset.Set(.82f, 2.1f, -2.1);

	// RearWing stucture 2
	car.chassis5_size.Set(.25f, 1.0f, .75f);
	car.chassis5_offset.Set(-.82f, 2.1f, -2.1);

	// RearWing part
	car.chassis6_size.Set(1.8f, .15f, 1.0f);
	car.chassis6_offset.Set(0.0f, 2.4f, -2.25);

	// RearWing part 2
	car.chassis7_size.Set(1.8f, .15f, .15f);
	car.chassis7_offset.Set(0.0f, 2.55f, -2.67);

	// Motor part 1
	car.chassis8_size.Set(1.6f, .55f, 1.5f);
	car.chassis8_offset.Set(0.0f, 1.85f, -.7f);

	// Motor part 2
	car.chassis9_size.Set(1.0f, .35f, 1.1f);
	car.chassis9_offset.Set(0.0f, 2.3f, -.5f);

	// Motor part 3
	car.chassis10_size.Set(0.4f, .35f, 0.8f);
	car.chassis10_offset.Set(0.0f, 2.6f, -.2f);

	// Cockpit part 1
	car.chassis11_size.Set(0.2f, .6f, 2.0f);
	car.chassis11_offset.Set(-0.45f, 1.85f, 1.0f);

	// Cockpit part 2
	car.chassis12_size.Set(0.2f, .6f, 2.0f);
	car.chassis12_offset.Set(0.45f, 1.85f, 1.0f);

	// Cockpit part 3
	car.chassis13_size.Set(1.1f, .6f, .3f);
	car.chassis13_offset.Set(0.0f, 1.85f, 2.0f);

	// Steering wheel support
	car.chassis14_size.Set(.1f, .1f, .75f);
	car.chassis14_offset.Set(0.0f, 2.05f, 1.6f);

	// Steering wheel
	car.chassis15_size.Set(.45f, .25f, .1f);
	car.chassis15_offset.Set(0.0f, 2.05f, 1.2f);

	// Steering wheel display
	car.chassis16_size.Set(.2f, .1f, .05f);
	car.chassis16_offset.Set(0.0f, 2.1f, 1.165f);

	// Motor air take hole
	car.chassis17_size.Set(.25f, .25f, .05f);
	car.chassis17_offset.Set(0.0f, 2.6f, 0.2f);

	// Pilot body
	car.chassis18_size.Set(.6f, .4f, .3f);
	car.chassis18_offset.Set(0.0f, 2.0f, 0.6f);

	// Pilot helmet
	car.chassis19_size.Set(.5f, .5f, .55f);
	car.chassis19_offset.Set(0.0f, 2.45f, 0.6f);

	// Pilot helmet visor
	car.chassis20_size.Set(.4f, .2f, .05f);
	car.chassis20_offset.Set(0.0f, 2.5f, 0.87f);

	// Pilot left arm
	car.chassis21_size.Set(.15f, .15f, .7f);
	car.chassis21_offset.Set(0.22f, 2.05f, 0.8f);

	// Pilot right arm
	car.chassis22_size.Set(.15f, .15f, .7f);
	car.chassis22_offset.Set(-0.22f, 2.05f, 0.8f);

	// Car properties ----------------------------------------
	car.mass = 600.0f;
	car.suspensionStiffness = 15.0f;
	car.suspensionCompression = .83f;
	car.suspensionDamping = 10.0f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.5f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.65f;
	float suspensionRestLength = 0.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0.5f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.5f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.5f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0.5f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, 0);
	
	vehicle->collision_listeners.add(this);
	vehicle->SetId(1);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	//Set player-vehicle position
	position.setValue(vehicle->GetPos().getX(), vehicle->GetPos().getY(), vehicle->GetPos().getZ());

	// Accelerate
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() <= MAX_VELOCITY) 
		{
			acceleration = MAX_ACCELERATION;
		}

		if (isEngineSFXPlayed == false) {
			App->audio->PlayFx(engineSFX);
			isEngineSFXPlayed = true;
		}


		// TURBOOOO
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) 
		{
			if (vehicle->GetKmh() < MAX_VELOCITY_TURBO) 
			{
				acceleration = MAX_ACCELERATION * 2;
				if (isTurboSFXPlayed == false) {
					App->audio->PlayFx(turboSFX);
					isTurboSFXPlayed = true;
				}
			}
		}
		else
		{
			isTurboSFXPlayed = false;
		}
		
	}
	else
	{
		isEngineSFXPlayed = false;
	}

	// Turn Left
	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	// Turn Right
	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	// Brake
	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;

	}

	// Car Jumping
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) 
	{
		vehicle->Push(0, 3000, 0);
	}

	// Brake if there's no throttle
	if (App->input->GetKey(SDL_SCANCODE_DOWN) != KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_UP) != KEY_REPEAT) 
	{
		brake = BRAKE_POWER / 100;

		if (vehicle->GetKmh() > 100) 
		{
			brake = BRAKE_POWER / 30;
		}
	}

	// Reset/Respawn car
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		resetCarPos();
	}

	if (App->physics->debug == true)
	{
		/* Change car mass value */
		// Increase
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
			vehicle->info.mass = vehicle->info.mass + 1;
		//Decrease
		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
			vehicle->info.mass = vehicle->info.mass - 1;


		// Enable/Disable Drag Force
		if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			isDragForceEnabled = !isDragForceEnabled;

		// Enable/Disable Buoyancy Force
		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
			isBuoyancyForceEnabled = !isBuoyancyForceEnabled;
	}

	// Mechanical vehicle forces
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);


	if (isDragForceEnabled == true) 
	{
		// Drag force applied to the vehicle
		App->physics->DragForce(vehicle, 30);
	}
	
	if (isBuoyancyForceEnabled == true)
	{
		// Buoyancy force applied to the vehicle
		App->physics->BuoyancyForce(vehicle, 20);
	}


	/* POST UPDATE */
	vehicle->Render();
	
	// Set window title
	char title[200];
	sprintf_s(title, "RACE CAR GAME 3D | Vehicle mass: %.1f kg | Vehicle current velocity: %.1f Km/h | World's Gravity: %.2f m/s2 | Drag Force: %s | Buoyancy Force: %s", vehicle->info.mass, vehicle->GetKmh(), App->physics->gravity_y, isDragForceEnabled ? "ENABLED":"DISABLED", isBuoyancyForceEnabled ? "ENABLED" : "DISABLED");
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::resetCarPos()
{
	vehicle->SetPos(initialPosition.x, initialPosition.y, initialPosition.z);
	vehicle->SetAngularVelocity(0, 0, 0);
	vehicle->SetLinearVelocity(0, 0, 0);
	vehicle->ResetCarOrientation();
}

vec3 ModulePlayer::GetVehicleForwardVector() 
{
	return vehicle->GetForwardVector();
}


