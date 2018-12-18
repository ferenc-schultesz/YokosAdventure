#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::Initialise(AudioHandler* aud, CPlayer * player, Vegetation* vegetation, Camera* camera,
	HeightMapTerrain* hm, PickUpHandler* pickUps, vector<Enemy*> enms)
{
	m_player = player;
	m_audio = aud;
	veg = vegetation;
	m_camera = camera;
	heightmap = hm;
	picks = pickUps;
	enemies = enms;
}

void CollisionHandler::UpdateEnemiesVector(vector<Enemy*> enms)
{
	enemies = enms;
}

void CollisionHandler::Update(float dt)
{
	CVector3f camVP = m_camera->GetViewPoint();
	CVector3f camPos = m_camera->GetPosition();

	m_camera->Update(dt);
	m_player->Update(dt);
	

	for each (Enemy* e in enemies)
	{
		CVector3f tempImpPos = e->GetPosition();
		e->Update(dt, m_camera, m_player->GetInvis());

		// damage imps by nova
		if (m_player->GetNova()->Active())
		{
			if (m_player->GetNova()->GetCurrentRange() > (e->GetPosition() - m_player->GetNova()->GetOrigin()).Length())
			{
				e->TakeHit(0.3f);
				e->ChangeState(FROZEN);
			}
		}

		// check collision with imps - player
		if (e->active && e->GetBBox().Collision(m_player->GetBBox()))
		{
			m_camera->Set(camPos, camVP);
			e->SetPosition(tempImpPos);
		}

		if ((e->GetState() == ATTACK || e->GetState() == ENRAGE) &&
			(e->GetPosition() - m_player->Position()).Length() < 2.0f)
		{
			m_player->TakeHit(e->GetDamage());
		}

		// check if trees is too close and avoid it
		for each (Tree* t in veg->GetTrees())
		{
			if (e->active && (e->GetPosition() - t->GetPosition()).Length() < 3.0f)
			{
				e->AvoidTree(t->GetPosition());
			}
		}

		if (e->GetFelball() != NULL)
		{
			if (e->GetFelball()->Active())
			{
				if ((e->GetFelball()->GetBBox().Collision(m_player->GetBBox())))
				{
					e->GetFelball()->Expload();
					m_player->TakeHit(50.f);
				}
				else
				{
					if (e->GetFelball()->GetVelocity() == CVector3f(0, 0, 0))
					{
						e->GetFelball()->Expload();
					}
				}

				if (e->GetFelball()->Exploading())
				{
					m_audio->PlayEventSound(BEXPL);
					if ((e->GetFelball()->GetPosition() - m_player->Position()).Length() < 6.0f)
					{
						m_player->Burn();
					}
				}
			}
		}
	}
	for each (Tree* t in veg->GetTrees())
	{
		if (t->GetBBox().Collision(m_player->GetBBox()))
		{
			m_camera->Set(camPos, camVP);
			m_player->Update(dt);
		}
	}

	if (m_player->GetFireball()->Active())
	{
		Fireball* fb = m_player->GetFireball();
		fb->Update(dt);
		// destroy if hits ground
		if (fb->GetPosition().y < (heightmap->ReturnGroundHeight(fb->GetPosition())))
		{
			fb->Destroy();
			m_audio->PlayEventSound(SEXPL);
		}
		// destroy if hits imp
		if (m_player->CurrentTarget()->GetBBox().Collision(*fb->GetBBox()))
		{
			m_player->CurrentTarget()->TakeHit(20.0f);
			m_player->CurrentTarget()->Defrost();

			for each (Enemy* e in enemies)
			{
				if ((e->GetPosition() - fb->GetPosition()).Length() < 3.0f)
				{
					e->TakeHit(20.0f);
					e->Defrost();
				}
			}
			fb->Destroy();
			m_audio->PlayEventSound(SEXPL);

		}
		// destroy if hits tree
		for each (Tree* t in veg->GetTrees())
		{
			if (t->GetBBox().Collision(*fb->GetBBox()))
			{
				fb->Destroy();
				m_audio->PlayEventSound(SEXPL);
			}
		}
		// destroy if it misses and goes too far
		if ( ((m_player->Position() - m_player->CurrentTarget()->GetPosition()).Length() * 1.5f) < (m_player->Position()- fb->GetPosition()).Length())
		{
			fb->Destroy();
			m_audio->PlayEventSound(SEXPL);
		}
	}

	for each (Potion* p in picks->Potions())
	{
		if (p->Active())
		{
			if (m_player->GetBBox().Collision(*p->BBox()))
			{
				if (p->GetType()._Equal("health") && (m_player->Health() < m_player->MaxHealth())) 
				{ 
					m_player->Health(p->Health());
					p->Destroy();
					m_audio->PlayEventSound(POTION);
				}
				if (p->GetType()._Equal("mana") && (m_player->Mana() < m_player->MaxMana()))
				{ 
					m_player->Mana(p->Mana()); 
					p->Destroy();
					m_audio->PlayEventSound(POTION);
				}
			}
		}
	}

	for each (Invisibility* i in picks->Invises())
	{
		if (i->Active())
		{
			if (m_player->GetBBox().Collision(*i->BBox()))
			{
				// make something invisible
				i->Destroy();
				m_player->Invis();
				m_audio->PlayEventSound(INVIS);
			}
		}
	}

}
