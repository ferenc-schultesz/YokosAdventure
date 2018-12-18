#include "Vegetation.h"

Vegetation::Vegetation()
{
}

Vegetation::~Vegetation()
{
}

void Vegetation::Initialise(int numOfGrass, HeightMapTerrain* hm)
{

	// Create trees
	elm_mesh.Load("Resources\\Meshes\\static\\Trees\\elm\\elm.3ds");
	giant_mesh.Load("Resources\\Meshes\\static\\Trees\\giant\\giant.obj");
	tree_mesh.Load("Resources\\Meshes\\static\\Trees\\tree\\Tree.obj");
	needle01_mesh.Load("Resources\\Meshes\\static\\Trees\\needle01\\needle01.obj");
	walnut_mesh.Load("Resources\\Meshes\\static\\Trees\\walnut\\walnut.obj");

	trees.push_back(new Tree(CVector3f(-7.104463f, -7.151120f, -1.648711f)  , hm));
	trees.push_back(new Tree(CVector3f(21.365747f, -9.452344f, 13.872203f), hm));
	trees.push_back(new Tree(CVector3f(42.211105f, -6.193990f, -11.386981f), hm));
	trees.push_back(new Tree(CVector3f(18.199339f, -2.422120f, -32.134739f), hm));
	trees.push_back(new Tree(CVector3f(-21.184774f, 3.066712f, -39.685780f), hm));
	trees.push_back(new Tree(CVector3f(-32.843109f, 1.905820f, -6.608838f), hm));
	trees.push_back(new Tree(CVector3f(-8.390092f, -6.611481f, 26.203812f), hm));
	trees.push_back(new Tree(CVector3f(45.049694f, -6.774548f, 25.922108f), hm));
	trees.push_back(new Tree(CVector3f(59.909077f, -2.904297f, 2.569987f), hm));
	trees.push_back(new Tree(CVector3f(55.605423f, -5.500240f, -20.463449f), hm));
	trees.push_back(new Tree(CVector3f(40.642666f, -4.322948f, -39.407455f), hm));
	trees.push_back(new Tree(CVector3f(39.060898f, 7.700035f, -66.300407f), hm));
	trees.push_back(new Tree(CVector3f(14.390203f, 6.499285f, -83.096619f), hm));
	trees.push_back(new Tree(CVector3f(-14.969895f, 9.059668f, -77.624290f), hm));
	trees.push_back(new Tree(CVector3f(-33.982906f, 7.762094f, -45.389217f), hm));
	trees.push_back(new Tree(CVector3f(-46.712765f, 9.278679f, -14.403440f), hm));
	trees.push_back(new Tree(CVector3f(-42.296825f, 7.409175f, 16.024061f), hm));
	trees.push_back(new Tree(CVector3f(-27.921331f, 3.055744f, 49.603962f), hm));
	trees.push_back(new Tree(CVector3f(1.010106f, 6.754624f, 75.306114f), hm));
	trees.push_back(new Tree(CVector3f(34.366592f, 9.378430f, 73.350212f), hm));
	trees.push_back(new Tree(CVector3f(73.608490f, -2.656220f, 57.133400f), hm));
	trees.push_back(new Tree(CVector3f(-75.126305f, 29.598980f, -42.270008f), hm));
	trees.push_back(new Tree(CVector3f(-86.174805f, 26.881445f, -4.008451f), hm));
	trees.push_back(new Tree(CVector3f(-80.419418f, 16.088287f, 33.472801f), hm));
	trees.push_back(new Tree(CVector3f(-62.340294f, 12.049533f, 67.417076f), hm));
	trees.push_back(new Tree(CVector3f(-42.418072f, 12.662682f, 87.440758f), hm));
	trees.push_back(new Tree(CVector3f(-1.443280f, 17.103655f, 109.088440f), hm));
	trees.push_back(new Tree(CVector3f(35.653988f, 21.408310f, 109.539337f), hm));
	trees.push_back(new Tree(CVector3f(82.856674f, 10.105229f, 98.306892f), hm));
	trees.push_back(new Tree(CVector3f(112.267899f, 8.129011f, 62.125008f), hm));
	trees.push_back(new Tree(CVector3f(118.161484f, 3.599435f, 28.002537f), hm));
	trees.push_back(new Tree(CVector3f(105.712807f, -4.658786f, -20.747177f), hm));
	trees.push_back(new Tree(CVector3f(88.185036f, 2.379258f, -56.931961f), hm));
	trees.push_back(new Tree(CVector3f(71.759995f, 16.415102f, -91.509827f), hm));
	trees.push_back(new Tree(CVector3f(27.451035f, 15.233257f, -116.420898f), hm));
	trees.push_back(new Tree(CVector3f(-2.981542f, 27.772684f, -137.295715f), hm));
	trees.push_back(new Tree(CVector3f(-33.369476f, 34.735157f, -136.289368f), hm));
	trees.push_back(new Tree(CVector3f(-65.629585f, 36.705082f, -119.200638f), hm));
	trees.push_back(new Tree(CVector3f(-40.426926f, 9.839805f, -18.696135f), hm));
	trees.push_back(new Tree(CVector3f(-53.344048f, 10.889444f, -38.140602f), hm));
	trees.push_back(new Tree(CVector3f(-30.901726f, 8.268302f, -30.685835f), hm));
	trees.push_back(new Tree(CVector3f(-55.712837f, 11.297040f, -38.437294f), hm));
	trees.push_back(new Tree(CVector3f(-77.093651f, 10.160937f, -53.015797f), hm));
	trees.push_back(new Tree(CVector3f(-66.241302f, 9.786122f, -74.754486f), hm));
	trees.push_back(new Tree(CVector3f(-64.426537f, 12.208502f, -97.145866f), hm));
	trees.push_back(new Tree(CVector3f(-26.019016f, 10.435385f, -110.739586f), hm));
	trees.push_back(new Tree(CVector3f(13.660542f, 11.614062f, -113.350174f), hm));
	trees.push_back(new Tree(CVector3f(37.906223f, 11.152220f, -120.891670f), hm));
	trees.push_back(new Tree(CVector3f(76.936142f, 12.264794f, -120.958427f), hm));
	trees.push_back(new Tree(CVector3f(94.051201f, 12.481925f, -89.051498f), hm));
	trees.push_back(new Tree(CVector3f(108.904564f, 13.477045f, -66.135284f), hm));
	trees.push_back(new Tree(CVector3f(128.642929f, 12.763718f, -49.287121f), hm));
	trees.push_back(new Tree(CVector3f(135.502060f, 12.793277f, -22.025986f), hm));
	trees.push_back(new Tree(CVector3f(96.560562f, 7.376361f, 15.544484f), hm));
	trees.push_back(new Tree(CVector3f(54.331120f, 3.997301f, 54.531689f), hm));
	trees.push_back(new Tree(CVector3f(21.501350f, 8.866128f, 59.276623f), hm));
	trees.push_back(new Tree(CVector3f(-73.014435f, 11.570302f, -18.533327f), hm));
	trees.push_back(new Tree(CVector3f(-97.485031f, 11.428191f, -37.440868f), hm));
	trees.push_back(new Tree(CVector3f(-98.437447f, 10.508192f, -60.639763f), hm));
	trees.push_back(new Tree(CVector3f(-95.765602f, 10.604036f, -86.434059f), hm));
	trees.push_back(new Tree(CVector3f(-118.574654f, 13.344169f, -92.761215f), hm));
	trees.push_back(new Tree(CVector3f(-138.777771f, 12.664432f, -76.328423f), hm));
	trees.push_back(new Tree(CVector3f(-139.587463f, 13.660247f, -49.222054f), hm));
	trees.push_back(new Tree(CVector3f(-140.228043f, 12.946094f, -23.535135f), hm));
	trees.push_back(new Tree(CVector3f(-136.034012f, 13.674716f, -1.119889f), hm));
	trees.push_back(new Tree(CVector3f(-117.131248f, 12.978857f, 14.018573f), hm));
	trees.push_back(new Tree(CVector3f(-108.878365f, 12.582812f, 32.089947f), hm));
	trees.push_back(new Tree(CVector3f(-126.059120f, 12.556581f, 47.602402f), hm));
	trees.push_back(new Tree(CVector3f(-112.745712f, 12.219531f, 62.577717f), hm));
	trees.push_back(new Tree(CVector3f(-88.546867f, 12.586096f, 60.074638f), hm));
	trees.push_back(new Tree(CVector3f(-82.731300f, 12.592128f, 79.579231f), hm));
	trees.push_back(new Tree(CVector3f(-83.279343f, 8.656948f, 109.374191f), hm));
	trees.push_back(new Tree(CVector3f(-76.389565f, 13.496729f, 127.359100f), hm));
	trees.push_back(new Tree(CVector3f(-58.469570f, 13.797261f, 130.876556f), hm));
	trees.push_back(new Tree(CVector3f(-44.782330f, 12.946094f, 116.145355f), hm));
	trees.push_back(new Tree(CVector3f(-30.633202f, 12.946094f, 104.274170f), hm));
	trees.push_back(new Tree(CVector3f(7.554376f, 12.872230f, 97.856911f), hm));
	trees.push_back(new Tree(CVector3f(42.725384f, 11.557257f, 94.541809f), hm));
	trees.push_back(new Tree(CVector3f(93.844566f, 12.103932f, 83.952789f), hm));
	trees.push_back(new Tree(CVector3f(114.113182f, 13.912607f, 102.217560f), hm));
	trees.push_back(new Tree(CVector3f(133.788849f, 16.137758f, 109.356995f), hm));
	trees.push_back(new Tree(CVector3f(139.545807f, 15.356058f, 71.133812f), hm));
	trees.push_back(new Tree(CVector3f(-50.650368f, 6.035517f, 42.242271f), hm));
	trees.push_back(new Tree(CVector3f(-13.982669f, 12.216113f, 90.799805f), hm));
	trees.push_back(new Tree(CVector3f(85.045258f, 6.583087f, -12.981545f), hm));
	trees.push_back(new Tree(CVector3f(119.586960f, 12.984509f, -42.377243f), hm));
	trees.push_back(new Tree(CVector3f(126.076653f, 14.770553f, -93.474792f), hm));
	trees.push_back(new Tree(CVector3f(95.664871f, 8.662655f, -113.570488f), hm));
	trees.push_back(new Tree(CVector3f(43.245621f, 12.754303f, -101.826157f), hm));
	trees.push_back(new Tree(CVector3f(-21.267103f, 10.261128f, -110.942085f), hm));
	trees.push_back(new Tree(CVector3f(-51.069622f, 12.147111f, -126.401955f), hm));
	trees.push_back(new Tree(CVector3f(-73.247719f, 12.449381f, -130.053055f), hm));
	trees.push_back(new Tree(CVector3f(-94.988945f, 14.505017f, -120.127014f), hm));
	trees.push_back(new Tree(CVector3f(-106.750824f, 7.738687f, -132.744629f), hm));
	trees.push_back(new Tree(CVector3f(-121.313286f, 10.610982f, -144.591919f), hm));
	trees.push_back(new Tree(CVector3f(-131.990875f, 12.464481f, -139.339783f), hm));
	trees.push_back(new Tree(CVector3f(-119.467690f, 12.627362f, -59.728020f), hm));
	trees.push_back(new Tree(CVector3f(-112.493500f, 11.250781f, -19.247534f), hm));
	trees.push_back(new Tree(CVector3f(-104.372284f, 13.596644f, 131.120789f), hm));
	trees.push_back(new Tree(CVector3f(-109.609985f, 13.118550f, 106.963745f), hm));
	trees.push_back(new Tree(CVector3f(-127.880241f, 14.263623f, 103.625397f), hm));
	trees.push_back(new Tree(CVector3f(-136.654922f, 14.141803f, 82.546791f), hm));
	trees.push_back(new Tree(CVector3f(3.717999f, 6.119755f, -54.758373f), hm));
	trees.push_back(new Tree(CVector3f(20.266880f, 15.690834f, -37.300812f), hm));





	// Create grasses

	grassTexture1.Load("Resources\\Textures\\ground\\grass01.png", false);
	grassTexture2.Load("Resources\\Textures\\ground\\grass02.png", false);

	for (int i = 0; i < numOfGrass; ++i)
	{
		float x = -150 + (rand() % static_cast<int>(150 + 150 + 1));
		float z = -150 + (rand() % static_cast<int>(150 + 150 + 1));
		float y = hm->ReturnGroundHeight(CVector3f(x, 0.0f, z));
		grasses.push_back(new Grass(CVector3f(x, y, z)));
	}

}

void Vegetation::Update()
{
}



vector<Tree*> Vegetation::GetTrees()
{
	return trees;
}

void Vegetation::Render()
{

	// Render trees, tree type variable controls which mesh is used
	// By using this method, tree meshes only loaded once and rendered many times (saves memory)
	for (unsigned int i = 0; i < trees.size(); ++i)
	{
		switch (trees[i]->GetType())
		{
		case 0:
			trees[i]->Render(&elm_mesh);
			break;
		case 1:
			trees[i]->Render(&giant_mesh);
			break;
		case 2:
			trees[i]->Render(&tree_mesh);
			break;
		case 3:
			trees[i]->Render(&needle01_mesh);
			break;
		case 4:
			trees[i]->Render(&walnut_mesh);
			break;
		}
	}

	for (unsigned int i = 0; i < grasses.size(); ++i)
	{
	
		switch (grasses[i]->GetType())
		{
		case 0:
			grasses[i]->Render(&grassTexture1);
			break;
		case 1:
			grasses[i]->Render(&grassTexture2);
			break;
		}
	}
}

