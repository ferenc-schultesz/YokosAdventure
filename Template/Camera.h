#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3f.h"
#include "include/glew.h" 
#include "HeightMapTerrain.h"

#define MAX_VERTICAL_ROTATION 85 

class Camera {
public:
	Camera();

	void Set(const CVector3f &position, const CVector3f &view, const CVector3f &up_vector, const float &speed);
	void Set(const CVector3f &position, const CVector3f &viewpoint);

	CVector3f GetPosition() const;		// Return the camera position (in world coordinates)
	CVector3f GetViewPoint() const;		// Return the point where the camera is looking (in world coordinates)
	CVector3f GetUpVector() const;		// Return the camera up vector (in world coordinates)
	CVector3f GetStrafeVector() const;	// Return the camera strafe vector (in world coordinates)

	void Strafe(float speed);	// Strafing moves the camera left / right
	void Advance(float speed);	// Advance moves the camera forward / backward
	void MoveUp(float speed);	// MoveUp moves the camera up / down

	void Update(double dt);
	void Look();				// Calls gluLookAt() to put the viewing matrix on the modelview matrix stack

	void RotateView(float angle, CVector3f &point);
	void RotateEye(float angle, CVector3f &point);  // rotate the position around the viewpoint for third person control
	void SetViewByMouse();
	void Movement(double dt);

	bool FREE_VIEW = false;							// Free view is usefull for debugging, camera won't be bound to height map terrain y coordinate

	void Zoom(float dz);							// allows the player to zoom in and out

	void SetHMap(HeightMapTerrain* hm);				// saves the height map terrain pointer
private:
	CVector3f m_position;							// camera position
	CVector3f m_viewPoint;							// camera view point
	CVector3f m_upVector;							// camera up vector
	CVector3f m_strafeVector;						// camera strafe vector

	float m_speed;									// speed used for movement
	float m_totalVerticalRotation;					// temo variable used at SetViewByMouse()

	float maxZoomY;									// maximum distance to zoom out 
	float minZoomY;									// minimum distance to zoom in

	HeightMapTerrain* hmap;    // pointer to height map, necessary to avoid camera position moving into the ground
								// and to calculate camera viewpoint (player) y position
};

#endif