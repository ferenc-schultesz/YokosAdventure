#include "Forest.h"



Forest::Forest() 
{
	bossUp = false;
	bossDead = false;
	gameover = false;
}
Forest::~Forest() {}

void Forest::Initialise(GameWindow* m_gw)
{

	// saving the game window pointer
	m_GameWindow = m_gw;
	// Creates heiight map terrain
	m_hterrian.Create("resources\\Textures\\\\ground\\craterHM.bmp", "resources\\Textures\\ground\\ground.jpg", CVector3f(0.0f, 0.5f, 0.0f), 400.0f, 400.0f, 15.5f);

	// camera initialised, positin is behind and above the viewpoint, so we arelokkind down to the player
	m_Camera.Set(CVector3f(0.0f, 5.2f + (m_hterrian.ReturnGroundHeight(CVector3f(0.0f, 0.0f, 15.0f)) + 4.2f), 0.0f), 
		CVector3f(0.0f, (m_hterrian.ReturnGroundHeight(CVector3f(0.0f, 0.0f, 15.0f)) + 4.2f) + 1.2f, -15.0f), CVector3f(0, 1, 0), 5.0f);
	// send the reference of heightmap to camera, it will be used to adjust the y coordinates at movement
	m_Camera.SetHMap(&m_hterrian);
	m_Player.Initialise(&m_Camera, &m_audio);

	enemies.push_back(new Imp(CVector3f(54.763634f, -0.002947f, -14.522641f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(74.992393f, 3.863554f, -3.509063f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(92.589241f, 7.287065f, -15.126036f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(76.227982f, 7.042196f, -44.546982f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(53.576378f, 9.426873f, -74.247337f), &m_hterrian, &m_audio));

	enemies.push_back(new Imp(CVector3f(33.105793f, 11.121402f, -95.293449f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(1.481516f, 12.285595f, -87.472977f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-31.663607f, 11.564658f, -74.360268f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-60.194042f, 8.785086f, 3.423497f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-37.172146f, 9.629413f, 59.372906f), &m_hterrian, &m_audio));
	
	enemies.push_back(new Imp(CVector3f(34.848740f, 5.888272f, 49.718395f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(65.780533f, 1.709114f, -22.656147f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-33.910851f, 4.514909f, 32.749462f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-31.721424f, 13.019138f, 75.029518f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(82.145302f, 11.397840f, -99.602013f), &m_hterrian, &m_audio));
	
	enemies.push_back(new Imp(CVector3f(-77.267227f, 10.340671f, -87.245079f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-105.448288f, 11.405280f, 0.891196f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-43.478420f, 10.892039f, -57.037483f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-55.985806f, 6.060709f, 34.306309f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(70.991096f, 3.507840f, 39.764751f), &m_hterrian, &m_audio));
	
	enemies.push_back(new Imp(CVector3f(-17.096870f, 6.390635f, -44.799755f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-71.896240f, 13.421321f, 77.455978f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(53.953480f, 14.533895f, -126.235275f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-91.950783f, 10.567770f, -49.586037f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-55.064411f, 10.871058f, -46.752338f), &m_hterrian, &m_audio));
	
	
	enemies.push_back(new Imp(CVector3f(-62.118118f, 10.843854f, -25.096262f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-3.603154f, 7.604105f, 58.375828f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(94.665833f, 7.724977f, 33.131096f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(81.221504f, 4.859634f, 3.106588f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(4.234109f, 4.113138f, -55.939831f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-27.664459f, 6.076497f, -13.109287f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-68.333450f, 9.917548f, 46.716343f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(7.146554f, 1.878059f, 34.559029f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(76.728989f, 11.055488f, -66.825958f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(24.212160f, 9.023816f, -129.142166f), &m_hterrian, &m_audio));
	enemies.push_back(new Imp(CVector3f(-43.569302f, 11.501232f, -115.826073f), &m_hterrian, &m_audio));

	// Create a class for rendering text
	m_text.Create(m_GameWindow->GetHdc(), "Arial", 35);
	// Create the skybox
	m_skybox.Create("", 0.0f);

	// Initialise audio and play background music
	m_audio.Initialise();

	vegetation.Initialise(5000, &m_hterrian);
	pickUpHandler.Initialise(&m_hterrian);

	collisionHandler.Initialise(&m_audio, &m_Player, &vegetation, &m_Camera, &m_hterrian, &pickUpHandler,  enemies);

	hud.Initialise(&m_Player, m_GameWindow);
	m_audio.PlayMusicStream();
	m_lighting.InitConstantLights(&m_Player, enemies);

	bunny.Load("Resources\\Meshes\\static\\Rabbit\\Rabbit.obj");

	RandomPickups.push_back(new Random(CVector3f(1, 3, 1)));

}

void Forest::Update(float dt)
{


	if (!bossDead)
	{
		m_lighting.Update();
	}

	if (!gameover)
	{
		m_audio.Update();
		collisionHandler.Update(dt);
		pickUpHandler.Update(dt);
		nova.Update(dt);
		unsigned int count = 0;
		for each (Enemy* e in enemies)
		{
			if (e->GetState() == DEAD)
			{
				++count;
			}
		}
		if (count >= 10 && !bossUp)
		{
			bossUp = true;
			boss = new Boss(CVector3f(0.0f, 0.0f, 0.0f), &m_hterrian, &m_audio);
			enemies.push_back(boss);
			collisionHandler.UpdateEnemiesVector(enemies);
			m_lighting.UpdateEnemiesVector(enemies);
			m_fx.ActivateFog(0.005, 0.6, 0.6, 0.6);
		}
		if (boss != NULL)
		{
			if (boss->GetState() == DEAD)
			{
				bossDead = true;
			}
		}

		if (m_Player.Health() < 1.0f)
		{
			gameover = true;
		}
	}
}
void Forest::Render(float dt)
{
	


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// Calling look will put the viewing matrix onto the modelview matrix stack
		m_Camera.Look();

		// Get the camera position and view vector 
		CVector3f vPos = m_Camera.GetPosition();
		CVector3f vView = m_Camera.GetViewPoint();

		// sets default material
		m_material.SetDefaultMaterial();


		glDisable(GL_LIGHTING);
		m_skybox.Render(vPos.x, vPos.y + 15.0f, vPos.z, 250, 500, 250);  // Render the skybox with same ambient light
		glEnable(GL_LIGHTING);

		m_hterrian.Render();

		if (bossDead && (boss->GetModel()->GetAnimation() == BOSS_STAND))
		{
			CVector3f bossPos = boss->GetPosition();
			CVector3f bunnyPos = CVector3f(bossPos.x - 6.0f, bossPos.y + 1.7f, bossPos.z - 0.5f);
			glPushMatrix();
			glTranslatef(bunnyPos.x, bunnyPos.y, bunnyPos.z);
			glRotatef(180.0f, 0, 1, 0);
			glScalef(1.4f, 1.4f, 1.4f);
			bunny.Render();
			glPopMatrix();

			m_lighting.SetTargetLight(bunnyPos);
			m_lighting.SetPlayerSpot(m_Player.Position());

			if ((bunnyPos - m_Player.Position()).Length() < 2.0f)
			{
				gameover = true;
			}
		}


		vegetation.Render();

		// Primitive based mesh with correct texture and normals, not used at the moment
		for (unsigned int i = 0; i < RandomPickups.size(); ++i)
		{
			glPushMatrix();
			glTranslatef(RandomPickups[i]->GetPosition().x, RandomPickups[i]->GetPosition().y, RandomPickups[i]->GetPosition().z);
			glRotatef(125.0f, 1, 0, 1);
			RandomPickups[i]->Render(dt);
			glPopMatrix();
		}



		pickUpHandler.Render(dt);

		if (!gameover)
		{
			for (unsigned int i = 0; i < enemies.size(); ++i)
			{
				enemies[i]->Render();
			}


			m_Player.Render();
		}
		nova.Render();
	
		DrawHUD();
}

void Forest::DrawHUD()
{
	glDisable(GL_LIGHTING);


	float h = m_GameWindow->SCREEN_HEIGHT;
	float w = m_GameWindow->SCREEN_WIDTH;


	if (bossDead && gameover)
	{
		m_text.Render(w/2 - w*0.07f, h/2 , 1, 1, 1, "Game Over");
		m_text.Render(w /2 - w*0.12f, h / 2  + 30, 0, 1, 0, "You got the Bunny!");
	}

	if (!bossDead && gameover)
	{
		m_text.Render(w / 2 - w*0.07f, h / 2, 1, 1, 1, "Game Over");
		m_text.Render(w / 2 - w*0.12f, h / 2 + 30, 1, 0, 0, "You lost the Bunny!");
	}
	glColor3f(1, 1, 1);

	hud.Render();
	glEnable(GL_LIGHTING);
}

Camera * Forest::GetCamera()
{
	return &m_Camera;
}

CPlayer * Forest::GetPlayer()
{
	return &m_Player;
}

vector<Enemy*> Forest::GetEnemies()
{
	return enemies;
}

