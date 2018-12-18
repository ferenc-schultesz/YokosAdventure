#include "Imp.h"
#include <cstring>

Imp::Imp() {}
Imp::~Imp() {}

Imp::Imp(CVector3f pos, HeightMapTerrain* hmap, AudioHandler* aud)
{
	audio = aud;
	model.LoadNoWeapon("Resources\\Meshes\\animated\\imp\\Imp.md2", "Resources\\Meshes\\animated\\imp\\Imp.jpg");
	//m_player = player;
	position = pos;
	originalPos = pos;
	scale = 0.03f;
	hm = hmap;
	direction = CVector3f(1, 0, 0);
	active = true;
	targeted = false;
	maxHealth = 100.0f;
	health = maxHealth;
	model.SetAnimation(0);

	rotation = 0.0f;
	rotVector = CVector3f(0.0f, 0.0f, 0.0f);
	m_bbox.SetSize(1.0f, 2.8f, 1.0f);

	timer = 0.0f;
	damage = 1.5f;
	frozen = 5.0f;
	state = PATROL;

	felball = NULL;
	unitFrameTexture.Load("Resources\\Textures\\hud\\impframe.png", false);
}

// 'y' is adjusted in render so the Imp stays on the ground
void Imp::Render()
{
	float rad = atan2(direction.z, direction.x);
	float deg = rad * (180 / 3.14f);

	if (active)
	{
		if (state == FROZEN)
		{
			glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			glTranslatef(position.x, position.y, position.z);
			glRotatef(-deg, 0, 1, 0);
			glScalef(scale, scale, scale);
			model.Render(false);
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			glRotatef(-deg, 0, 1, 0);
			glScalef(scale, scale, scale);
			model.Render(false);
			glPopMatrix();
		}
	}
	else
	{
		glPushMatrix();
		glTranslatef(position.x + 1.0f, position.y + 0.8f, position.z - 0.5f);
		glRotatef(90.0f, 0, 0, 1);
		glScalef(scale, scale, scale);
		model.Render(false);
		glPopMatrix();
	}

#if (_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif

	if (targeted && !(state == DEAD))
	{
		//light up the target
		// for target mark
		GLfloat A[3] = { -0.7f, 1.1f, 0.0f };
		GLfloat B[3] = { 0.0f, 1.1f, -0.7f };
		GLfloat C[3] = { 0.0f, 1.1f, 0.7f };
		GLfloat D[3] = { 0.7f, 1.1f, 0.0f };

		GLfloat E[3] = { 0.0f,0.0f,0.0f };
		// CVector for normals
		CVector3f vA(-0.7f, 1.1f, 0.0f);
		CVector3f vB(0.0f, 1.1f, -0.7f);
		CVector3f vC(0.0f, 1.1f, 0.7f);
		CVector3f vD(0.7f, 1.1f, 0.0f);

		CVector3f vE(0.0f, 0.0f, 0.0f);

		// Normals
		// TOP PART
		CVector3f nEDC = ((vC - vE) % (vC - vD));
		GLfloat normalEDC[3] = { nEDC.x,nEDC.y,nEDC.z };
		CVector3f nEBD = ((vD - vE) % (vD - vB));
		GLfloat normalEBD[3] = { nEBD.x,nEBD.y,nEBD.z };
		CVector3f nEAB = ((vB - vE) % (vB - vA));
		GLfloat normalEAB[3] = { nEAB.x,nEAB.y,nEAB.z };
		CVector3f nECA = ((vA - vE) % (vA - vC));
		GLfloat normalECA[3] = { nECA.x,nECA.y,nECA.z };
		GLfloat topnormal[3] = { 0.0f, 1.0f, 0.0f };

		// Top surface
		// ACB
		glPushMatrix();
		glTranslatef(position.x, position.y + 4.0f, position.z);
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
		glNormal3fv(topnormal), glVertex3fv(A),
			glNormal3fv(topnormal), glVertex3fv(C),
			glNormal3fv(topnormal), glVertex3fv(B),
			// BCD
			glNormal3fv(topnormal), glVertex3fv(B),
			glNormal3fv(topnormal), glVertex3fv(C),
			glNormal3fv(topnormal), glVertex3fv(D),

			// Top part
			// EDC
			glNormal3fv(normalEDC), glVertex3fv(E),
			glNormal3fv(normalEDC), glVertex3fv(D),
			glNormal3fv(normalEDC), glVertex3fv(C),
			// EBD
			glNormal3fv(normalEBD), glVertex3fv(E),
			glNormal3fv(normalEBD), glVertex3fv(B),
			glNormal3fv(normalEBD), glVertex3fv(D),
			// EAB
			glNormal3fv(normalEAB), glVertex3fv(E),
			glNormal3fv(normalEAB), glVertex3fv(A),
			glNormal3fv(normalEAB), glVertex3fv(B),
			// ECA
			glNormal3fv(normalECA), glVertex3fv(E),
			glNormal3fv(normalECA), glVertex3fv(C),
			glNormal3fv(normalECA), glVertex3fv(A),
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
}

void Imp::Update(float dt, Camera* cam, bool playerInvisible)
{
	playerPos = cam->GetViewPoint();
	timer += dt;
	position.y = hm->ReturnGroundHeight(position);
	m_bbox.SetBottom(CVector3f(position.x, position.y, position.z));
	float speed = (float)dt * 2.0f;

	if (playerInvisible)
	{
		state = PATROL;
	}
	else
	{
		if ((health < maxHealth * 0.3f) && !(state == FROZEN) && !(state == ENRAGE))
		{
			state = ENRAGE;
		}
	}

	if (health < 1.0f)
	{
		state = DEAD;
	}

	switch (state)
	{
	case PATROL:
		position += direction * 2 * speed;
		position.y = hm->ReturnGroundHeight(position);

		model.SetAnimation(IMP_WALK);
		if ((position - originalPos).Length() > 25.0f)
		{
			direction = (originalPos - position);
			direction.Normalise();
		}

		if (timer > 4.0f)
		{
			int output = -90 + (rand() % static_cast<int>(90 + 90 + 1));
			rotation += output;
			timer = 0;
			direction = direction.RotateAboutAxis(rotation, CVector3f(0, 1, 0));
		}
		// switch state
		if (((position - playerPos).Length() < 20.0f) && !playerInvisible)
		{
			state = CHASE;
		}
		break;

	case CHASE:
		model.SetAnimation(IMP_WALK);
		direction = playerPos - position;
		direction.Normalise();
		position += direction * 2 * speed;
		position.y = hm->ReturnGroundHeight(position);

		// switch state
		if ((position - playerPos).Length() < 2.0f)
		{
			state = ATTACK;
			audio->PlayEventSound(TAKEDAM);
			audio->PlayEventSound(ATT1);
		}
		if ((position - playerPos).Length() > 25.0f)
		{
			state = PATROL;
		}
		break;

	case ATTACK:

		if (((model.GetAnimation() == IMP_ATT) && (model.IsLastFrameRendered()) ||
			((position - playerPos).Length() > 2.0f)))
		{
			state = CHASE;
		}
		else
		{
			model.SetAnimation(IMP_ATT);
		}

		break;

	case FROZEN:
		frozen -= dt;
		model.SetAnimation(IMP_STAND);

		if (frozen < 0.05f)
		{
			state = CHASE;
			frozen = 5.0f;
		}
		break;

	case ENRAGE:
		if (!(model.GetAnimation() == IMP_ATT))
		{
			model.SetAnimation(IMP_ATT);
			audio->PlayEventSound(ATT1);
		}
		else
		{
			if (model.IsLastFrameRendered())
			{
				audio->PlayEventSound(ATT1);
			}
		}
		if ((position - playerPos).Length() > 2.0f)
		{
			direction = playerPos - position;
			direction.Normalise();
			position += direction * 2 * speed;
			position.y = hm->ReturnGroundHeight(position);
		}

		scale = 0.05f;
		damage = 2.0f;

		break;

	case DEAD:

		if (((model.GetAnimation() == IMP_DIE) && model.IsLastFrameRendered()) || !active)
		{
			model.SetAnimation(IMP_STAND);
			active = false;
		}
		else
		{
			model.SetAnimation(IMP_DIE);
		}
		break;
	}
}

void Imp::TakeHit(float damage)
{
	health -= damage;
	if (health < 0.0f)
	{
		Die();
	}
}

void Imp::Die()
{
	state = DEAD;
}

void Imp::AvoidTree(CVector3f treePos)
{
	direction = direction.RotateAboutAxis(-rotation, CVector3f(0, 1, 0));
}

void Imp::ChangeState(State s)
{
	state = s;
}

void Imp::SetPosition(CVector3f pos)
{
	position = pos;
}

// Getter methods
State Imp::GetState() { return state; }
CMD2Model* Imp::GetModel() { return&model; }
float Imp::GetDamage() { return damage; }
FelBall* Imp::GetFelball() { return felball; }
CBoundingBox Imp::GetBBox() { return m_bbox; }
CVector3f Imp::GetPosition() { return position; }
CVector3f Imp::GetrotVector() { return rotVector; }
float Imp::GetRotation() { return rotation; }
float Imp::GetScale() { return scale; }
float Imp::GetHealth() { return health; }