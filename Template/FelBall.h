#pragma once

#include <windows.h>									
#include "Vector3f.h"
#include "OpenAssetimporterMesh.h"
#include "BoundingBox.h"
#include "HeightMapTerrain.h"
#include "SpriteExplosion.h"
#include "Camera.h"

class FelBall
{
public:
	FelBall();
	~FelBall();
	void Shot(CVector3f origin, Camera*  cam);
	void Update(float dt);
	void Initialise(char *filename, HeightMapTerrain* heightmap);
	void Render();
	void Active(bool a);
	void Expload();

	bool Active();
	bool Exploading();
	CVector3f GetPosition();
	CVector3f GetLastPosition();
	CBoundingBox GetBBox();
	CVector3f GetVelocity();

private:

	// Linear physical quantities
	CVector3f m_position;
	CVector3f m_velocity;
	CVector3f m_acceleration;
	CVector3f m_instantaneousAcceleration;
	CVector3f m_lastPosition;
	CVector3f m_gravity;

	// Rotational physical quantities
	CVector3f m_angle;
	CVector3f m_angularVelocity;
	CVector3f m_angularAcceleration;
	CVector3f m_instantaneousAngularAcceleration;


	// Other physical quantities
	float m_mass; // in kg
	float m_rotationalInertia; // in kg m^2
	float m_contactTime; // in seconds
	float m_coefficientOfRestitution; // as a percentage
	float m_radius; // radius of ball in meters

	// Angles used for rendering (see Lab 4)
	float m_theta;
	float m_phi;

	// Mesh
	COpenAssetImporterMesh m_mesh;

	// Methods to handle collisions with the ground
	bool CollisionDetection();
	void CollisionResponse();

	bool active;
	bool exploading;

	CBoundingBox m_bbox;
	HeightMapTerrain* hm;
	CSpriteExplosion* felexplosion;
	CVector3f playerPosition;
	Camera* camera;
};