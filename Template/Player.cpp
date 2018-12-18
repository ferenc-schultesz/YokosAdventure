#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialise(Camera* cam, AudioHandler* aud)//CVector3f camVP)
{
	md2Model.Load("Resources\\Meshes\\animated\\yokho\\Yohko.md2", "Resources\\Meshes\\animated\\yokho\\Yohko.bmp",
		"Resources\\Meshes\\animated\\yokho\\YohkoWeapon.md2", "Resources\\Meshes\\animated\\yokho\\YohkoWeapon.bmp");
	m_camera = cam;
	m_audio = aud;
	m_position = cam->GetViewPoint();// camVP;
	m_direction = CVector3f(0, 0, 1);
	meleeDam = 15.0f;
	m_bbox.SetSize(1.0f, 2.4f, 1.0f);
	maxMana = 150.0f;
	maxHealth = 200.0f;
	health = maxHealth;
	mana = maxMana;
	fireball = new Fireball();
	fireball->Initialise();
	burnDebuff = 0.0f;
	burn = false;

	invisBuff = 0.0f;
	invis = false;
}

void CPlayer::Update(double dt)
{
	crossfade.Update(dt);
	//m_position += m_direction * m_speed * dt;
	m_position = m_camera->GetViewPoint();// camVp;
	m_direction = m_camera->GetViewPoint() - m_camera->GetPosition(); // camVp - camPos;
	m_bbox.SetBottom(CVector3f(m_position.x, m_position.y - 1.2f, m_position.z));
	Move();
	Attack(dt);
	if (burn)
	{
		burnDebuff -= dt;
		TakeHit(0.25f);
		if (burnDebuff < 0.1f) 
		{
			burn = false;
			burnDebuff = 0.0f;
		}
	}

	if (invis)
	{
		invisBuff -= dt;
		if (invisBuff < 0.01f)
		{
			invis = false;
			invisBuff = 0.0f;
		}
	}

	for each (CSmokeParticleEmitter* s in smokes)
	{
		if (s->IsActive())
		{
			s->UpdateParticles(dt);
		}
	}
}



void CPlayer::Render()
{

	// render player to camera viewpoint and calculate the rotation of the model
	// for this the viewpoint - position vector is used
	float rad = atan2(m_direction.z, m_direction.x);
	float deg = rad * (180 / 3.14f);
	glPushMatrix();
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(-deg, 0, 1, 0);
		glScalef(0.05f, 0.05f, 0.05f);
		md2Model.Render(true);
	glPopMatrix();

	nova.Render();
	//

	#if (_DEBUG)
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		m_bbox.Render(1, 0, 0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	#endif

	if (fireball->Active())
	{
		fireball->Render(m_camera);
	}
	for each (CSmokeParticleEmitter* s in smokes)
	{
		if (s->IsActive())
		{
			s->Render(m_camera->GetViewPoint() - m_camera->GetPosition(), m_camera->GetUpVector());
		}
	}

	crossfade.Render(1,0,0);
}

CMD2Model* CPlayer::GetModel()
{
	return &md2Model;
}

CVector3f CPlayer::Position()
{
	return m_position;
}

Enemy * CPlayer::CurrentTarget()
{
	return currentTarget;
}

Fireball * CPlayer::GetFireball()
{
	return fireball;
}

CAlphaSphere * CPlayer::GetNova()
{
	return &nova;
}

bool CPlayer::GetBurn()
{
	return burn;
}

float CPlayer::GetBurnDebuff()
{
	return burnDebuff;
}

float CPlayer::GetInvisBuff()
{
	return invisBuff;
}

void CPlayer::Attack(float dt)
{
	//crossfade.Update(dt);
	
	if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
	{

		if (currentTarget != NULL)
		{
			if (mana >= 20.0f)
			{
				if (!fireball->Active())
				{
					{
						m_audio->PlayEventSound(FIREBALL);
						CVector3f direction = currentTarget->GetPosition() - m_position;
						direction.y += 1.0f;
						direction.Normalise();

						fireball->Fire(direction, m_position, currentTarget);
						mana -= 20.0f;


						CSmokeParticleEmitter* s = new CSmokeParticleEmitter();
						s->LoadTexture("./Resources/Textures/effects/smokeBlackAlpha.tga");
						s->Initialise(m_position, (currentTarget->GetPosition() - m_position), (int) ((currentTarget->GetPosition() - m_position).Length() /1.5) , .5, .5, currentTarget);

						smokes.push_back(s);

						for each (CSmokeParticleEmitter* sm in smokes)
						{
							if (!(s->IsActive()))
							{
								delete sm;
							}
						}
					}
				}
			}
		}
	}

	nova.Update(dt);
	if ((GetKeyState(VK_CONTROL) & 0x100) != 0)
	{
		if (!nova.Active() && (mana > 15.0f))
		{
			m_audio->PlayEventSound(NOVA);
			nova.Activate(1.0f, CVector3f(0.255f, 0.412f, 0.882f), CVector3f(0.0, 1.0, 1.0), true, 0.75f, m_position);
			mana -= 15.0f;
		}
	}
	// player attack
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && md2Model.GetAnimation() != YOHKO_ATTACK)
	{
		// change to attack animation
		md2Model.SetAnimation(2);
		m_audio->PlayEventSound(SWORD);
		if (currentTarget != NULL)
		{
			float temp = (currentTarget->GetPosition() - m_position).Length();
			if ((currentTarget->active && (currentTarget->GetPosition() - m_position).Length() < 6.0f))
			{
				if (currentTarget->GetState() == FROZEN)
				{
					currentTarget->TakeHit(meleeDam * 2.0f);
				}
				else
				{
					currentTarget->TakeHit(meleeDam);
				}

			}
		}
	}
}



void CPlayer::Target(vector<Enemy*> enemies)
{
	float distance;
	for each (Enemy* e in enemies)
	{
		if (e->active)
		{
			if (currentTarget == NULL || !currentTarget->active)
			{
				currentTarget = e;
			}
			distance = (currentTarget->GetPosition() - m_position).Length();
			
			float temp = (e->GetPosition() - m_position).Length();
			if (temp < distance)
			{
				currentTarget = e;
			}
		}
		e->targeted = false;
	}
	if (currentTarget != NULL) 
	{ 
		currentTarget->Target();
	}
}

CBoundingBox CPlayer::GetBBox()
{
	return m_bbox;
}


float CPlayer::Mana()
{
	return mana;
}

float CPlayer::Health()
{
	return health;
}

void CPlayer::Mana(float f)
{
	mana += f;
	if (mana > maxMana) { mana = maxMana; }
}

void CPlayer::Health(float f)
{
	health += f;
	if (health > maxHealth) { health = maxHealth; }
}

float CPlayer::MaxHealth()
{
	return maxHealth;
}

float CPlayer::MaxMana()
{
	return maxMana;
}

void CPlayer::TakeHit(float hp)
{
	if (!crossfade.Active())
	{
		crossfade.Activate();
	}
	//m_audio->PlayEventSound(TAKEDAM);
	health -= hp;
	if (health < 1)
	{
		health = 0;
		Die();
	}
}

void CPlayer::Die()
{
	// die
}

void CPlayer::Move()
{
	// these if statements change the animation and direction of the player model, depending on which keys are pressed

	// player moving top right and there's no atatck animation
	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80) && (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
		&&
		(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered()))) {
		// rotate model to top right
		m_direction = m_direction.RotateAboutAxis(-45.0f, CVector3f(0, 1, 0));
		// change to running animation
		md2Model.SetAnimation(1);
	}
	// player moving top left and there's no atatck animation
	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80) && (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)
		&&
		(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered()))) {
		// rotate model to top left
		m_direction = m_direction.RotateAboutAxis(45.0f, CVector3f(0, 1, 0));
		// change to running animation
		md2Model.SetAnimation(1);
	}
	// player moving down right and there's no atatck animation
	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80) && (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
		&&
		(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered()))) {
		// rotate model to down right
		m_direction = m_direction.RotateAboutAxis(-45.0f, CVector3f(0, 1, 0));
		// change to running animation
		md2Model.SetAnimation(1);
	}
	// player moving down left and there's no atatck animation
	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80) && (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)
		&&
		(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered()))) {
		// rotate model to down left
		m_direction = m_direction.RotateAboutAxis(45.0f, CVector3f(0, 1, 0));
		// change to running animation
		md2Model.SetAnimation(1);
	}

	

	// when player move up 
	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {
		// and doesn;t attack
		if (!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered()))
		{
			// change to running animation
			md2Model.SetAnimation(1);
		}
	}
	// when player moves down
	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {
		// but not left right or up and no attack
		if ((!(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) &&
			(!(GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) &&
			(!(GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) &&
			(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered())))
		{
			// change to running animation
			md2Model.SetAnimation(1);
			m_direction = m_direction.RotateAboutAxis(180.0f, CVector3f(0, 1, 0));
		}
	}
	// when player moves left 
	if ((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {
		// but not up and not attack
		if ((!(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) &&
			(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered())))
		{
			// change to running animation
			md2Model.SetAnimation(1);
			m_direction = m_direction.RotateAboutAxis(90.0f, CVector3f(0, 1, 0));
		}
	}
	// when player move right
	if ((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {
		// but not up and no attack
		if ((!(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) &&
			(!(md2Model.GetAnimation() == YOHKO_ATTACK) || (md2Model.GetAnimation() == YOHKO_ATTACK && md2Model.IsLastFrameRendered())))
		{
			// change to running animation
			md2Model.SetAnimation(1);
			// rotate model to right
			m_direction = m_direction.RotateAboutAxis(-90.0f, CVector3f(0, 1, 0));
		}
	}
	// when the current animation is finished and not key pressed render standing animation
	if (//md2Model.IsLastFrameRendered()	&& 
		!(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)
		&& !(GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)
		&& !(GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)
		&& !(GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
		&& ((md2Model.GetAnimation() != YOHKO_ATTACK)

		||  (md2Model.GetAnimation() == YOHKO_ATTACK) && (md2Model.IsLastFrameRendered())) )
	{
		md2Model.SetAnimation(0);
	}

}

void CPlayer::Burn()
{
	if (!burn)
	{
		burn = true;
		burnDebuff = 4.0f;
	}
}


void CPlayer::Invis()
{
	if (!invis)
	{
		invis = true;
		invisBuff = 5.0f;
	}
}

bool CPlayer::GetInvis()
{
	return invis;
}
