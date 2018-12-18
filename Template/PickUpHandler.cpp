#include "PickUpHandler.h"

PickUpHandler::PickUpHandler()
{
}

PickUpHandler::~PickUpHandler()
{
}
void PickUpHandler::Initialise(HeightMapTerrain* heightmap)
{
	hm = heightmap;

	manaTexture.Load("Resources\\Textures\\pickups\\mana.png", false);
	healthTexture.Load("Resources\\Textures\\pickups\\health.png", false);
	invisTexture.Load("Resources\\Textures\\pickups\\invisibility.jpg", false);

	v_potion.push_back(new Potion(CVector3f(13.791628f, 14.674545f, -80.799835f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(41.628914f, 15.066147f, -86.349403f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(74.506500f, 15.601812f, -73.501152f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(96.639946f, 14.057909f, -31.323017f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(84.652069f, 12.655270f, 16.923954f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(50.002983f, 14.103847f, 71.998566f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(-5.360636f, 17.457092f, 80.907372f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(-52.731628f, 17.542393f, 56.504032f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(-67.560699f, 17.447868f, 12.525311f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(-51.510838f, 18.746487f, -37.487118f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(5.058064f, 17.082079f, -61.637295f), "mana", hm));
	v_potion.push_back(new Potion(CVector3f(69.672546f, 12.653504f, -37.954887f), "mana", hm));

	v_potion.push_back(new Potion(CVector3f(-37.894699f, 18.038088f, 68.528770f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(2.741908f, 13.434023f, 43.005215f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(54.116596f, 12.137272f, 39.690136f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(70.577194f, 12.096717f, 1.603765f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(88.661598f, 15.399022f, -44.297058f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(37.655170f, 13.132408f, -56.497971f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(10.373830f, 17.562531f, -93.746338f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(-37.006737f, 16.058300f, -87.080582f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(-86.925476f, 18.215540f, -58.088787f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(-102.816475f, 20.299412f, -26.251621f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(-102.804848f, 19.388817f, 38.845528f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(-31.828653f, 9.710176f, 23.538269f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(19.123793f, 6.090868f, 20.117798f), "health", hm));
	v_potion.push_back(new Potion(CVector3f(63.832928f, 8.181412f, -14.530339f), "health", hm));



	v_invis.push_back(new Invisibility(CVector3f(24.185143f, 12.213412f, -66.323326f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-29.506805f, 16.325701f, -67.808495f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-75.228439f, 15.969508f, -41.503082f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-104.648033f, 17.466215f, -1.491947f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-103.271599f, 18.139767f, 58.291790f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-60.353188f, 18.085072f, 86.362213f), hm));
	v_invis.push_back(new Invisibility(CVector3f(-11.971606f, 14.686858f, 67.105278f), hm));
	v_invis.push_back(new Invisibility(CVector3f(62.878544f, 11.379418f, 25.717056f), hm));
	v_invis.push_back(new Invisibility(CVector3f(77.868721f, 11.492552f, -44.055817f), hm));


	rotation = 0.0f;
}

void PickUpHandler::Update(float dt)
{
	// used to rotate the different pick-ups
	rotation += 55.0f * dt;
	// 360 degrees = 0 degress, therefore reset
	if (rotation >= 360.0f) {
		rotation = 0.0;
	}

}

void PickUpHandler::Render(float dt)
{

	for (unsigned int i = 0; i < v_potion.size(); ++i)
	{
		if (v_potion[i]->Active())
		{
			glPushMatrix();
			glTranslatef(v_potion[i]->GetPosition().x, v_potion[i]->GetPosition().y, v_potion[i]->GetPosition().z);
			if (v_potion[i]->GetType()._Equal("mana"))
			{
				glRotatef(rotation, 0, 1, 0);
				glScalef(0.15f, 0.15f, 0.15f);
				v_potion[i]->Render(dt, &manaTexture);
			}
			else
			{
				glRotatef(-rotation, 0, 1, 0);
				glScalef(0.15f, 0.15f, 0.15f);
				v_potion[i]->Render(dt, &healthTexture);
			}
			glPopMatrix();
			#if (_DEBUG)
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glDisable(GL_TEXTURE_2D);
				v_potion[i]->BBox()->Render(0.690f, 0.769f, 0.871f);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE_2D);
			glPopMatrix();
			#endif
		}
	}

	for (unsigned int i = 0; i < v_invis.size(); ++i)
	{
		if (v_invis[i]->Active())
		{

			glPushMatrix();
			glTranslatef(v_invis[i]->GetPosition().x, v_invis[i]->GetPosition().y, v_invis[i]->GetPosition().z);
			glScalef(0.25f, 0.25f, 0.25f);
			glRotatef(rotation, 0, 1, 0);
			v_invis[i]->Render(dt, &invisTexture);
			glPopMatrix();
			#if (_DEBUG)
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glDisable(GL_TEXTURE_2D);
					v_invis[i]->BBox()->Render(0.690f, 0.769f, 0.871f);
					glEnable(GL_LIGHTING);
					glEnable(GL_TEXTURE_2D);
				glPopMatrix();
			#endif
		}
	}
}

vector<Potion*> PickUpHandler::Potions()
{
	return v_potion;
}

vector<Invisibility*> PickUpHandler::Invises()
{
	return v_invis;
}
