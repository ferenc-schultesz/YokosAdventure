#include "HUD.h"

HUD::HUD()
{
}

void HUD::Initialise(CPlayer * player, GameWindow* gw)
{
	m_player = player;
	playerTexture.Load("Resources\\Textures\\hud\\playerframev2.png", false);
	frozenTexture.Load("Resources\\Textures\\hud\\frozen.png", false);
	burningTexture.Load("Resources\\Textures\\hud\\burn.png", false);
	invisTexture.Load("Resources\\Textures\\hud\\invis.png", false);
	m_text.Create(gw->GetHdc(), "Arial", 25);
	SCREEN_WIDTH = gw->SCREEN_WIDTH;
	SCREEN_HEIGHT = gw->SCREEN_HEIGHT;
}

HUD::~HUD()
{
}

void HUD::SetOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, m_viewport);
	int w = m_viewport[2];
	int h = m_viewport[3];

	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

void HUD::RestorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

// Render a full-screen quad with varying transparency
void HUD::Render()
{

	// RENDER PLAYER UNIT FRAME---------------------------------

	// Set the OpenGL state and go to 2D mode
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, playerTexture.m_textureID);
	SetOrthographicProjection();
	glLoadIdentity();

	// Get screen width and height
	float w = (float)m_viewport[2];
	float h = (float)m_viewport[3];

	glBegin(GL_QUADS);
	glTexCoord2f(0.01f, 0), glVertex3f(w*0.05f, h * 0.85f, 0);
	glTexCoord2f(1, 0), glVertex3f(w*0.3f, h* 0.85f, 0);
	glTexCoord2f(1, 1.0f), glVertex3f(w*0.3f, h* 0.95f, 0);
	glTexCoord2f(0.01f, 1), glVertex3f(w*0.05f, h*0.95f, 0);

	glEnd();


	// RENDER PLAYERS HEALTH BAR --------------------------

	glDisable(GL_TEXTURE_2D);
	// health bar
	GLfloat A[3] = { w*0.14f,h * 0.9f,0.0f };
	GLfloat B[3] = { w*0.3f,h * 0.9f,0.0f };
	GLfloat C[3] = { w*0.3f,h * 0.93f,0.0f };
	GLfloat D[3] = { w*0.14f,h * 0.93f,0.0f };

	float health = m_player->Health();
	float maxbarlength = B[0] - A[0];
	float currenbarlength = maxbarlength / m_player->MaxHealth() * health;
	

	B[0] = A[0] + currenbarlength;
	C[0] = A[0] + currenbarlength;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3fv(C);
	glVertex3fv(D);
	glEnd();

	// RENDER PLAYER MANA BAR -----------------------------

	GLfloat E[3] = { w*0.14f,h * 0.87f,0.0f };
	GLfloat F[3] = { w*0.3f,h * 0.87f,0.0f };
	GLfloat G[3] = { w*0.3f,h * 0.9f,0.0f };
	GLfloat H[3] = { w*0.14f,h * 0.9f,0.0f };

	float mana = m_player->Mana();
	currenbarlength = maxbarlength / m_player->MaxMana() * mana;

	F[0] = E[0] + currenbarlength;
	G[0] = E[0] + currenbarlength;

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3fv(E);
	glVertex3fv(F);
	glVertex3fv(G);
	glVertex3fv(H);
	glEnd();

	// Go back to 3D mode (perspective projection)
	RestorePerspectiveProjection();
	glPopMatrix();
	//glDisable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);

	// Render Player debuff
	if (m_player->GetBurn())
	{
		glPushMatrix();
		SetOrthographicProjection();
		glLoadIdentity();
		// Render debuff frame
		glBindTexture(GL_TEXTURE_2D, burningTexture.m_textureID);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.01f, 0), glVertex3f(w*0.315f, h * 0.86f, 0);
		glTexCoord2f(1, 0), glVertex3f(w*0.375f, h* 0.86f, 0);
		glTexCoord2f(1, 1.0f), glVertex3f(w*0.375f, h* 0.94f, 0);
		glTexCoord2f(0.01f, 1), glVertex3f(w*0.315f, h*0.94f, 0);
		glEnd();
		RestorePerspectiveProjection();
		glPopMatrix();
		// get time left with 1 decimal
		float t = m_player->GetBurnDebuff();
		string value = to_string_with_precision(t);
		char *cstr = &value[0u];
		m_text.Render(SCREEN_WIDTH *0.326f, SCREEN_HEIGHT * 0.172f, 1, 0, 0, cstr);
	}

	// Render players buff
	if (m_player->GetInvis())
	{
		glPushMatrix();
		SetOrthographicProjection();
		glLoadIdentity();
		// Render debuff frame
		glBindTexture(GL_TEXTURE_2D, invisTexture.m_textureID);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.01f, 0), glVertex3f(w*0.385f, h * 0.86f, 0);
		glTexCoord2f(1, 0), glVertex3f(w*0.45f, h* 0.86f, 0);
		glTexCoord2f(1, 1.0f), glVertex3f(w*0.45f, h* 0.94f, 0);
		glTexCoord2f(0.01f, 1), glVertex3f(w*0.385f, h*0.94f, 0);
		glEnd();
		RestorePerspectiveProjection();
		glPopMatrix();
		float r = m_player->GetInvisBuff();
		string value = to_string_with_precision(r);
		char *cstr = &value[0u];
		m_text.Render(SCREEN_WIDTH *0.40f, SCREEN_HEIGHT * 0.172f, 0, 1, 0, cstr);
	}




	// RENDER Enemy UNIT FRAME --------------------------
 	if (m_player->CurrentTarget() != NULL)
	{
		// Set the OpenGL state and go to 2D mode
		glPushMatrix();
			SetOrthographicProjection();
			glLoadIdentity();
			glBindTexture(GL_TEXTURE_2D, m_player->CurrentTarget()->GetFrameTexture().m_textureID);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.01f, 0), glVertex3f(w*0.7f, h * 0.85f, 0);
				glTexCoord2f(1, 0), glVertex3f(w*0.95f, h* 0.85f, 0);
				glTexCoord2f(1, 1.0f), glVertex3f(w*0.95f, h* 0.95f, 0);
				glTexCoord2f(0.01f, 1), glVertex3f(w*0.7f, h*0.95f, 0);
			glEnd();
			// RENDER ENEMY HEALTH BAR ----------------------
			glDisable(GL_TEXTURE_2D);
			GLfloat I[3] = { w*0.79f,h * 0.88f,0.0f };
			GLfloat J[3] = { w*0.95f,h * 0.88f,0.0f };
			GLfloat K[3] = { w*0.95f,h * 0.92f,0.0f };
			GLfloat L[3] = { w*0.79f,h * 0.92f,0.0f };

 			health = m_player->CurrentTarget()->GetHealth();
			maxbarlength = J[0] - I[0];
			float currenbarlength = maxbarlength / m_player->CurrentTarget()->MaxHealth() * health;

			J[0] = I[0] + currenbarlength;
			K[0] = I[0] + currenbarlength;

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
				glVertex3fv(I);
				glVertex3fv(J);
				glVertex3fv(K);
				glVertex3fv(L);
			glEnd();
			// Go back to 3D mode (perspective projection)
			RestorePerspectiveProjection();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		// Render frozen debuff on enemies
		if (m_player->CurrentTarget()->GetState() == FROZEN)
		{
			glPushMatrix();
				SetOrthographicProjection();
				glLoadIdentity();
				// Render debuff frame
				glBindTexture(GL_TEXTURE_2D, frozenTexture.m_textureID);
				glColor3f(1, 1, 1);
				glBegin(GL_QUADS);
					glTexCoord2f(0.01f, 0), glVertex3f(w*0.63f, h * 0.86f, 0);
					glTexCoord2f(1, 0), glVertex3f(w*0.7f, h* 0.86f, 0);
					glTexCoord2f(1, 1.0f), glVertex3f(w*0.7f, h* 0.94f, 0);
					glTexCoord2f(0.01f, 1), glVertex3f(w*0.63f, h*0.94f, 0);
				glEnd();
				RestorePerspectiveProjection();
			glPopMatrix();
			float r = m_player->CurrentTarget()->frozen;
			string value = to_string_with_precision(r);
			char *cstr = &value[0u];
			m_text.Render(SCREEN_WIDTH *0.645f, SCREEN_HEIGHT * 0.172f, 1, 0, 0, cstr);
		}
	}
}


std::string HUD::to_string_with_precision(float val)
{
	std::ostringstream out;
	if (val < 1.0f)
	{
		out << std::setprecision(1) << val;
	}
	else
	{
		out << std::setprecision(2) << val;
	}
	return out.str();
}