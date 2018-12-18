#include "Fireball.h"

Fireball::Fireball()
{
	active = false;
	m_explosion.Initialise("Resources\\Textures\\effects\\Explosion.tga", 4, 5, 16, true);
	mana = 20.f;
	damage = 20.f;

	m_target = NULL;

	smoke.LoadTexture("./Resources/Textures/effects/smokeBlackAlpha.tga");
}

Fireball::~Fireball()
{
}

void Fireball::Initialise()
{
	
}

void Fireball::Update(float dt)
{

	CVector3f t = m_target->GetPosition();
	t.y += 1.3f;

	m_velocity = (t - m_position);
	m_velocity.Normalise();
	m_velocity *= 20.f;
	m_position +=  m_velocity * dt;
	m_bbox.SetBottom(m_position);
	m_explosion.Update(dt);
	
	// Update the smoke trail if active
	/*if (smoke.IsActive() && (m_target != NULL))
		smoke.UpdateParticles(dt, m_target->GetPosition() - originalPos);*/
}

void Fireball::Render(Camera* cam)
{

	#if (_DEBUG)
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	#endif
	CVector3f t = CVector3f(m_position.x, m_position.y + 0.75f, m_position.z);
	m_explosion.Render(t,t - cam->GetPosition(),CVector3f(0,1,0),1.5f,1.5f);

	
}

void Fireball::Fire(CVector3f direction, CVector3f pos, Enemy* target)
{

	originalPos = pos;

	m_target = target;

	m_position = pos;
	
	m_bbox.SetBottom(CVector3f(m_position.x, m_position.y, m_position.z));
	m_bbox.SetSize(1.2f, 1.2f, 1.2f);
	m_velocity = (target->GetPosition() - m_position);
	m_velocity.Normalise();
	m_velocity *= 20.f;

	active = true;
	m_explosion.Activate();

}

CSpriteExplosion * Fireball::GetExplosion()
{
	return &m_explosion;
}

CBoundingBox * Fireball::GetBBox()
{
	return &m_bbox;
}

CVector3f Fireball::GetPosition()
{
	return m_position;
}

void Fireball::Destroy()
{
	active = false;
	smoke.Clear();
}

bool Fireball::Active()
{
	return active;
}

float Fireball::Mana()
{
	return mana;
}

float Fireball::Damage()
{
	return damage;
}
