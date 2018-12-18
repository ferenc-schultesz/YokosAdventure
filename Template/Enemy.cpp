#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(CVector3f pos, HeightMapTerrain * hmap, AudioHandler* aud)
{

}

Enemy::~Enemy()
{
}


void Enemy::Update(float dt, Camera* cam, bool playerVisible) { }
void Enemy::Render() { }
CBoundingBox Enemy::GetBBox() { return m_bbox; }
void Enemy::AvoidTree(CVector3f treePos) { }
CMD2Model* Enemy::GetModel() { return &model; }
CVector3f Enemy::GetPosition() { return position; }
CVector3f Enemy::GetrotVector() { return rotVector; }

float Enemy::GetDamage()
{
	return damage;
}

float Enemy::GetRotation() { return rotation; }
float Enemy::GetScale() { return scale; }
float Enemy::GetHealth() { return health; }

void Enemy::TakeHit(float damage) { }

void Enemy::SetPosition(CVector3f pos) { }

void Enemy::Target()
{
	targeted = true;
}

void Enemy::Die() {}


void Enemy::ChangeState(State s)
{
	state = s;
}

State Enemy::GetState()
{
	return state;
}



FelBall* Enemy::GetFelball() { return felball; };

void Enemy::Defrost()
{
	frozen = 0.0f;
}

CTexture Enemy::GetFrameTexture()
{
	return unitFrameTexture;
}

float Enemy::MaxHealth()
{
	return maxHealth;
}