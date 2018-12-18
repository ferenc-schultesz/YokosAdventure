#include "camera.h"
#include <Windows.h>

#include ".\include\glew.h"									// Header File For The Glaux Library
#include ".\include\gl.h"									// Header File For The OpenGL32 Library
#include ".\include\glu.h"									// Header File For The GLu32 Library

#include <math.h>

#include "gamewindow.h"

// Set up a default camera
Camera::Camera()
{
	// variable init
	m_position = CVector3f(0.0f, 3.2f, 0.0f);
	m_viewPoint = CVector3f(0.0f, 1.2f, -15.0f);
	m_upVector = CVector3f(0.0f, 1.0f, 0.0f);
	m_speed = 0.1f;
	m_totalVerticalRotation = 0.0f;

	maxZoomY = 17.0f;			// maximum distance to zoom out (position - viewpoint).Length()
	minZoomY = 1.2f;			// minimum distance to zoom in (position - viewpoint).Length()
}

// Set a specific camera
void Camera::Set(const CVector3f &position, const CVector3f &view, const CVector3f &up_vector, const float &speed)
{
	m_position = position;
	m_viewPoint = view;
	m_upVector = up_vector;
	m_speed = speed;

	Look();
}

void Camera::Set(const CVector3f & position, const CVector3f & viewpoint)
{
	m_position = position;
	m_viewPoint = viewpoint;
}

// Get the camera rotation using the mouse
void Camera::SetViewByMouse()
{
	int middle_x = GameWindow::SCREEN_WIDTH >> 1;
	int middle_y = GameWindow::SCREEN_HEIGHT >> 1;

	POINT mouse;
	GetCursorPos(&mouse);

	if (mouse.x == middle_x && mouse.y == middle_y) {
		return;
	}

	SetCursorPos(middle_x, middle_y);

	float dx = (float)(middle_x - mouse.x) / 25.0f;
	float dy = (float)(middle_y - mouse.y) / 25.0f;


	m_totalVerticalRotation += dy;

	// Clip the rotation rotation about the strafe vector to [-MAX_STRAFE_ROTATION, MAX_STRAFE_ROTATION]

	if (FREE_VIEW)   // in free view,, viewpoint rotated around position
	{
		if (m_totalVerticalRotation > MAX_VERTICAL_ROTATION)
		{
			m_totalVerticalRotation = MAX_VERTICAL_ROTATION;
		}
		else
		{
			if (m_totalVerticalRotation < -MAX_VERTICAL_ROTATION)
			{
				m_totalVerticalRotation = -MAX_VERTICAL_ROTATION;
			}
			else
			{
				RotateView(dy, m_strafeVector);
			}
		}
		RotateView(dx, CVector3f(0, 1, 0));
	}
	else    // in not free view, position rotated around viewpoint
	{
		if (m_totalVerticalRotation > MAX_VERTICAL_ROTATION)
		{
			m_totalVerticalRotation = MAX_VERTICAL_ROTATION;
		}
		else
		{
			if (m_totalVerticalRotation < -MAX_VERTICAL_ROTATION)
			{
				m_totalVerticalRotation = -MAX_VERTICAL_ROTATION;
			}
			else
			{
				RotateEye(dy, m_strafeVector);
			}
		}
		RotateEye(dx, CVector3f(0, 1, 0));
	}

}

// Rotate the camera viewpoint around a vector
void Camera::RotateView(float angle, CVector3f &vector)
{
	CVector3f view = m_viewPoint - m_position;
	CVector3f rotatedView = view.RotateAboutAxis(angle, vector);
	m_viewPoint = m_position + rotatedView;
}

void Camera::RotateEye(float angle, CVector3f &vector)
{
	CVector3f view = m_position - m_viewPoint;		// get vector between viepoint and position
	CVector3f rotatedCampos = view.RotateAboutAxis(angle, vector);	// temp vector for viewpoint after rotation
	// Check if the rotation, moves the position in the ground mesh
	CVector3f temp = m_viewPoint + rotatedCampos;
	if (temp.y <= hmap->ReturnGroundHeight(m_position) + 1.2f)
	{
		// if it does, set the y a bit higher then the mesh so the camera won't get stuck in the mesh
		m_position.y = hmap->ReturnGroundHeight(m_position) + 1.4f; 
	}
	else
	{
		// also check if the rotation goes to high 
		if (temp.y >= hmap->ReturnGroundHeight(m_position) + 17.0f)
		{
			m_position.y = hmap->ReturnGroundHeight(m_position) + 16.8f;
		}
		else
		{
			// if not too high and not too low, just rotate
			m_position = temp;
		}
	}
}


// Move the camera left/right
void Camera::Strafe(float speed)
{
	if (!FREE_VIEW)
	{
		// deltaY used to keep the Y of the position compared to the viewpoint when the player moves up or down
		// on the mesh (hills)
		float deltaY = m_position.y - m_viewPoint.y;
		m_position.x += m_strafeVector.x * speed;
		m_position.z += m_strafeVector.z * speed;

		m_viewPoint.x += m_strafeVector.x * speed;
		m_viewPoint.z += m_strafeVector.z * speed;
		m_viewPoint.y = hmap->ReturnGroundHeight(m_viewPoint) + 1.2f;
		m_position.y = m_viewPoint.y + deltaY;
		// Checks if strafing would move the position into the mesh
		if (m_position.y <= hmap->ReturnGroundHeight(m_position) + 0.2f)
		{
			m_position.y = hmap->ReturnGroundHeight(m_position) + 0.2f;
		}
	}
	else // in free view no checks are necessary
	{
		m_position.x += m_strafeVector.x * 3 * speed;
		m_position.z += m_strafeVector.z * 3 * speed;

		m_viewPoint.x += m_strafeVector.x * 3 * speed;
		m_viewPoint.z += m_strafeVector.z * 3 * speed;
	}
}

// Move the camera forward/backward
void Camera::Advance(float speed)
{
	CVector3f direction = m_viewPoint - m_position;
	direction.Normalise();
	
	if (!FREE_VIEW)
	{
		// deltaY used to keep the Y of the position compared to the viewpoint when the player moves up or down
		// on the mesh (hills)
		float deltaY = m_position.y - m_viewPoint.y;
		m_position += direction * 2 * speed;
		m_viewPoint += direction * 2 * speed;
		m_viewPoint.y = hmap->ReturnGroundHeight(m_viewPoint) + 1.2f;
		m_position.y = m_viewPoint.y + deltaY;//hmap->ReturnGroundHeight(m_position) + 5.2f;
		// Checks if strafing would move the position into the mesh
		if (m_position.y <= hmap->ReturnGroundHeight(m_position) + 0.2f)
		{
			m_position.y = hmap->ReturnGroundHeight(m_position) + 0.2f;
		}
	}
	else // in free view no checks necessary, speed is also increased
	{
		m_position += direction * 3 * speed;
		m_viewPoint += direction * 3 * speed;
	}
}

// Move the camera up / down --- NOT USED
void Camera::MoveUp(float speed)
{
	m_position += m_upVector * speed;
	m_viewPoint += m_upVector * speed;
}

// Update the camera -- note this typically involves updating the camera position (m_vPosition), viewpoint (m_vViewPoint), and stafe vector (m_vStrafeVector)
void Camera::Update(double dt)
{
	Movement(dt);
	SetViewByMouse();
}

// Call gluLookAt to put a viewing matrix on the modelview matrix stack
void Camera::Look()
{
	gluLookAt(
		m_position.x, m_position.y, m_position.z,
		m_viewPoint.x, m_viewPoint.y, m_viewPoint.z,
		m_upVector.x, m_upVector.y, m_upVector.z);

	m_strafeVector = (m_viewPoint - m_position) % m_upVector;
	m_strafeVector.Normalise();

}

// Move the camera based on arrow keys or WSAD keys
void Camera::Movement(double dt)
{
	float speed = (float)dt * m_speed;

	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {
		Advance(speed);	// Forward
	}

	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {
		Advance(-speed);	// Backward
	}

	if ((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {
		Strafe(-speed ); // Left
	}

	if ((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {
		Strafe(speed ); // Right
	}
}

CVector3f Camera::GetPosition() const
{
	return m_position;
}

CVector3f Camera::GetViewPoint() const
{
	return m_viewPoint;
}

CVector3f Camera::GetUpVector() const
{
	return m_upVector;
}

CVector3f Camera::GetStrafeVector() const
{
	return m_strafeVector;
}

void Camera::Zoom(float delta)
{
	CVector3f norm = CVector3f(m_viewPoint - m_position);
	norm.Normalise();

	if (!FREE_VIEW)
	{

		// Zooms out
		if (delta < 0)
		{
			CVector3f temp = m_position + (norm * -1);
			// Checks if we already zoomed out to max
			if (temp.y < m_viewPoint.y + maxZoomY && (m_viewPoint - temp).Length() < 40.0f) 
			{ 
				m_position = temp;
			}
		}
		// Zoom in
		if (delta > 0)
		{
			// Checks if we zoom in to min
			CVector3f temp = m_position + (norm * 1);
			if ( (m_viewPoint - temp).Length() > 3.5f) //temp.y > m_viewPoint.y + minZoomY &&
			{ 
				m_position = temp; 
			}
		}
	}
	else   // no minimum or maximum zoom is necessary in free view
	{
		if (delta < 0)
		{
			m_position = m_position + (norm * -1);
		}
		// Zoom in
		if (delta > 0)
		{
			m_position = m_position + (norm * 1);
		}
	}
}


void Camera::SetHMap(HeightMapTerrain* hm)
{
	hmap = hm;
}