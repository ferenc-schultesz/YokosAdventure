#include "FelBall.h"

FelBall::FelBall()
{
	// Initialise static physical quantities
	m_radius = 1.42f; // in meters
	m_mass = 1.45f; // in kg
	m_rotationalInertia = (2.0f / 3.0f) * m_mass * m_radius * m_radius; // in kg m^2
	m_coefficientOfRestitution = 0.55f; // percentage
	m_contactTime = 0.05f; // in seconds

	m_bbox.SetBottom(m_position);
	m_bbox.SetBottom(CVector3f(m_position.x, m_position.y-0.55f, m_position.z));
	m_bbox.SetSize(1.1f, 1.1f, 1.1f);

	active = false;
	exploading = false;

}

FelBall::~FelBall()
{}

void FelBall::Initialise(char *filename, HeightMapTerrain* heightmap)
{
	felexplosion = new CSpriteExplosion();
	felexplosion->Initialise("Resources\\Textures\\effects\\ExplosionFel.tga", 4, 5, 16, false);
	m_mesh.Load(filename);
	hm = heightmap;
}


bool FelBall::CollisionDetection()
{
	float y = hm->ReturnGroundHeight(m_position);
	// Check for collision with the ground by looking at the y value of the ball's position
	if (m_position.y - m_radius < y && m_velocity.y < 0) {
		return true;
	}
	return false;
}

void FelBall::CollisionResponse()
{
	float convergenceThreshold = 0.5f;
	if (m_velocity.Length() > convergenceThreshold) {
		// The ball has bounced!  Implement a bounce by flipping the y velocity.
		m_velocity = CVector3f(m_velocity.x, -m_velocity.y, m_velocity.z) * m_coefficientOfRestitution;

	}
	else {
		// Velocity of the ball is below a threshold.  Stop the ball. 
		m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
		m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
		m_position = CVector3f(m_position.x, m_radius + (hm->ReturnGroundHeight(m_position)) , m_position.z);
		m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	}
}


void FelBall::Update(float dt)
{


	felexplosion->Update(dt);
	if (!felexplosion->Active())
	{
		exploading = false;
	}

	if (!active)
	{
		return; 
	}

	// Update physical quanitities
	m_lastPosition = m_position;
	m_velocity += (m_acceleration + m_instantaneousAcceleration) * dt;
	m_position += m_velocity * dt;
	m_angularVelocity += (m_angularAcceleration + m_instantaneousAngularAcceleration) * dt;
	m_angle += m_angularVelocity * dt;

	// Turn off instantaneous forces if contact time is surpassed
	if (m_instantaneousAcceleration.Length() > 0 && m_contactTime > 0.05) {
		m_instantaneousAcceleration = CVector3f(0, 0, 0);
		m_instantaneousAngularAcceleration = CVector3f(0, 0, 0);
		m_contactTime = 0;
	}
	m_contactTime += dt;

	// Check for collision detection
	
	if (CollisionDetection()) {
		CollisionResponse();
	}
	m_bbox.SetBottom(CVector3f(m_position.x, m_position.y-0.55f, m_position.z));

	if (m_position.y <= hm->ReturnGroundHeight(m_position) + 1.0f)
	{
		m_velocity = CVector3f(0, 0, 0);
	}
}

void FelBall::Expload()
{
	felexplosion->Activate();
	exploading = true;
	active = false;
}

CVector3f  FelBall::GetVelocity()
{
	return m_velocity;
}


void FelBall::Shot( CVector3f origin, Camera* cam)
{
	camera = cam;
	CVector3f targetPos = camera->GetViewPoint();
	//playerPosition = playerPos;
	targetPos.y = targetPos.y + 1.0f;
	origin.y = origin.y + 3.0f;
	m_position = origin;
	active = true;


	CVector3f direction = targetPos - m_position;	// Direction camera is facing
	direction.Normalise();
	direction.y += 0.3f;
													// Initialise all physical variables

	m_acceleration = CVector3f(0.0f, -19.8f, 0.0f);
	m_instantaneousAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_velocity = (m_acceleration + m_instantaneousAcceleration) * 0.00001f; // need to init with bigger than (0,0,0) so it is not exploading at start
	m_angle = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAngularAcceleration = CVector3f(150.0f, 0.0f, 0.0f) / m_rotationalInertia;  
	m_contactTime = 0.0f;

	// Set the ball to the current camera position
	m_instantaneousAcceleration = (250 * direction) / m_mass;

	// Determine rotation angles of camera (from Lab 4)
	m_theta = 90.0f - (180.0f / 3.141529f) * acos(direction.y);
	m_phi = (180.0f / 3.1415290f) * atan2(direction.x, direction.z);
}

void FelBall::Render()
{


	if (exploading)
	{
		CVector3f pos = m_position;
		pos.y += 1.0f;
		felexplosion->Render(pos, m_position - camera->GetPosition(), CVector3f(0, 1, 0), 6.0f, 6.0f);
	}
	if (!active ) { return; }

	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);

	if (m_angle.Length() > 0)
		glRotatef(m_angle.Length(), m_angle.x, m_angle.y, m_angle.z);	// Rotate the ball resulting from torque
	glScalef(2.0f, 2.0f, 2.0f);
	m_mesh.Render();
	glPopMatrix();

#if (_DEBUG)
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
#endif
}

CVector3f FelBall::GetPosition()
{
	return m_position;
}

CVector3f FelBall::GetLastPosition()
{
	return m_lastPosition;
}

CBoundingBox  FelBall::GetBBox()
{
	return m_bbox;
}

bool FelBall::Active()
{
	return active;
}

bool FelBall::Exploading()
{
	return exploading;
}

void FelBall::Active(bool a)
{
	active = a;
}
