#include "Tree.h"
#include <cstring>

Tree::Tree()
{

}

Tree::Tree(CVector3f pos, HeightMapTerrain* hm)
{

	
		int output = 1 + (rand() % static_cast<int>(5 - 1 + 1));
		type = output;
		switch (output)
		{
		case 0:
			scale = 1.7f;
			m_bbox.SetSize(1.6f, 1.8f, 1.6f);
			break;
		case 1:
			scale = 1.0f;
			m_bbox.SetSize(6.0f, 1.8f, 6.0f);
			break;
		case 2:
			scale = 6.25f;
			m_bbox.SetSize(1.0f, 1.8f, 1.0f);
			break;
		case 3:
			scale = 6.25f;
			m_bbox.SetSize(3.5f, 1.8f, 3.5f);
			break;
		case 4:
			scale = 2.0f;
			m_bbox.SetSize(1.5f, 1.8f, 1.5f);
			break;
		}

	
	position = pos;
	position.y = hm->ReturnGroundHeight(pos); // 'y' is adjusted so the mesh is rendered on the ground
	m_pHM = hm;
	m_bbox.SetBottom(CVector3f(position.x, position.y, position.z));
}
Tree::~Tree()
{
}

CBoundingBox Tree::GetBBox()
{
	return m_bbox;
}

CVector3f Tree::GetPosition() { return position; }
CVector3f Tree::GetrotVector() { return rotVector; }
float Tree::GetScale() { return scale; }

void Tree::Render(COpenAssetImporterMesh* mesh)
{
	// Blending function and alpha test is necessary so achieve proper transparency in mesh textures
	// Source: https://www.sjbaker.org/steve/omniv/alpha_sorting.html
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	//glRotatef(rotation, rotVector.x, rotVector.y, rotVector.z);
	glScalef(scale, scale, scale);
	mesh->Render();
	glPopMatrix();


#if (_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(0, 1, 0);
	//glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
#endif

}

int Tree::GetType()
{
	return type;
}