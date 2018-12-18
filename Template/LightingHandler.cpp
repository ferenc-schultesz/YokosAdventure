#include "LightingHandler.h"	


// CONSATNT ON LIGHTs -----------------------------------
LightingHandler::LightingHandler(){}



void LightingHandler::InitConstantLights(CPlayer * player, vector<Enemy*> enemies)
{
	m_player = player;
	m_enemies = enemies;
	SetDefaultAmbient();
	SetPlayerSpot(m_player->Position());
	SetMoonLight();
}

void LightingHandler::Update()
{
	// update players spot pos
	SetPlayerSpot(m_player->Position());

	// player's target spotlight
	if (m_player->CurrentTarget() != NULL)
	{
		glEnable(GL_LIGHT3);
		SetTargetLight(m_player->CurrentTarget()->GetPosition());
	}
	else
	{
		glDisable(GL_LIGHT3);
	}

	// player's fireball spotlight
	if (m_player->GetFireball()->Active())
	{
		glEnable(GL_LIGHT5);
		SetFireballLight(m_player->GetFireball()->GetPosition());
	}
	else
	{
		glDisable(GL_LIGHT5);
	}

	// boss' felball spotlight
	for each (Enemy* e in m_enemies)
	{
		if (e->GetFelball() != NULL)
		{
			if (e->GetFelball()->Active())
			{
				glEnable(GL_LIGHT4);
				SetFelballLight(e->GetFelball()->GetPosition());
			}
		}
		else
		{
			glDisable(GL_LIGHT4);
		}
	}

}

void LightingHandler::SetDefaultAmbient()
{
	GLfloat ambientLight0[] = { 0.25f, 0.25f, 0.25f, 0.25f };
	GLfloat diffuseLight0[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat specularLight0[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat positionLight0[] = { 1.0f, 10.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);

	glEnable(GL_LIGHT0);
}



void LightingHandler::SetPlayerSpot(CVector3f pos)
{
	GLfloat ambientLight1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuseLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat positionLight1[] = { pos.x, pos.y + 20.5f, pos.z, 1.0f };
	
	GLfloat* cutoff = new GLfloat(50.0f);
	GLfloat* exp = new GLfloat(100.0f);
	GLfloat dir[] = { 0.0f, -1.0f, 0.0f, 0.0f };
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, positionLight1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, exp);
	
	glEnable(GL_LIGHT1);
}




void LightingHandler::SetMoonLight()
{
	GLfloat ambientLight2[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuseLight2[] = { 0.3f, 0.3f, 0.3f, 0.0f };
	GLfloat specularLight2[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat positionLight2[] = { -100.0f, 100.0f, 100.0f, 0.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);

	glEnable(GL_LIGHT2);
}




// TEMP LIGHTS --------------------------------------

void LightingHandler::SetTargetLight(CVector3f pos)
{
	GLfloat ambientLight3[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuseLight3[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight3[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat positionLight3[] = { pos.x, pos.y + 20.5f, pos.z, 1.0f };

	GLfloat* cutoff = new GLfloat(50.0f);
	GLfloat* exp = new GLfloat(100.0f);
	GLfloat dir[] = { 0.0f, -1.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight3);
	glLightfv(GL_LIGHT3, GL_POSITION, positionLight3);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT3, GL_SPOT_EXPONENT, exp);

}

void LightingHandler::SetFelballLight(CVector3f pos)
{
	GLfloat ambientLight4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuseLight4[] = { 0.2f, 1.0f, 0.0f, 1.0f };
	GLfloat specularLight4[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat positionLight4[] = { pos.x, pos.y + 20.5f, pos.z, 1.0f };

	GLfloat* cutoff = new GLfloat(8.0f);
	GLfloat* exp = new GLfloat(20.5f);
	GLfloat dir[] = { 0.0f, -1.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientLight4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight4);
	glLightfv(GL_LIGHT4, GL_POSITION, positionLight4);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT4, GL_SPOT_EXPONENT, exp);

}

void LightingHandler::SetFireballLight(CVector3f pos)
{
	GLfloat ambientLight5[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuseLight5[] = { 1.0f, 0.0f, 0.2f, 1.0f };
	GLfloat specularLight5[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat positionLight5[] = { pos.x, pos.y + 20.5f, pos.z, 1.0f };

	GLfloat* cutoff = new GLfloat(5.0f);
	GLfloat* exp = new GLfloat(20.5f);
	GLfloat dir[] = { 0.0f, -1.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT5, GL_AMBIENT, ambientLight5);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseLight5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specularLight5);
	glLightfv(GL_LIGHT5, GL_POSITION, positionLight5);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT5, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT5, GL_SPOT_EXPONENT, exp);

}

void LightingHandler::UpdateEnemiesVector(vector<Enemy*> enemies)
{
	m_enemies = enemies;
}