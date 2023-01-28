#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "Bullet/include/LinearMath/btVector3.h"

class btRigidBody;
class Module;
class btQuaternion;

struct Euler
{
	float roll, pitch, yaw;
};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetRotation(btQuaternion q);

	btQuaternion GetRotation();
	Euler GetEulerAngles(btQuaternion q);
	
	void SetAsSensor(bool is_sensor);
	void SetId(int id);

	btVector3 GetPos();

	void SetLinearVelocity(float x, float y, float z);
	void SetAngularVelocity(float x, float y, float z);

	btVector3 GetLinearVelocity();
	btVector3 GetAngularVelocity();
private:
	btRigidBody* body = nullptr;

public:
	int id;
	bool is_sensor;

	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__