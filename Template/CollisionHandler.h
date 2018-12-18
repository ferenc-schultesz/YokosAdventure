#pragma once

#include "Vector3f.h"
#include "Player.h"
#include "BoundingBox.h"
#include "Camera.h"
#include "HeightMapTerrain.h"
#include "Vegetation.h"
#include "PickUpHandler.h"
#include "FelBall.h"
#include "Enemy.h"
#include "AudioHandler.h"

class CollisionHandler {
public:
	CollisionHandler();
	~CollisionHandler();
	void Initialise(AudioHandler* aud, CPlayer* player, Vegetation* vegetation, Camera* camera, 
		HeightMapTerrain* hm, PickUpHandler* pickUps, vector<Enemy*> enms);
	void Update(float dt);
	void UpdateEnemiesVector(vector<Enemy*> enms);


private:
	CPlayer* m_player;
	AudioHandler* m_audio;
	Vegetation* veg;
	Camera* m_camera;
	HeightMapTerrain* heightmap;
	PickUpHandler* picks;
	vector<Enemy*> enemies;
};