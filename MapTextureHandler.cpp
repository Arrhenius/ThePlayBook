#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <vector>
#include "imgui/imgui.h"
#include "MapTextureHandler.h"




MapTexture::MapTexture()
{
	memset(this, 0, sizeof(this));
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
	m_filepath[0] = '\0';
	m_mapname[0] = '\0';
}

MapTexture::~MapTexture()
{
	memset(this, 0, sizeof(this));
}


PDIRECT3DTEXTURE9 MapTexture::getTexture()
{
	return m_texture;
}

int MapTexture::getWidth()
{
	return m_width;
}

int MapTexture::getHeight()
{
	return m_height;
}


const char* MapTexture::getFilepath()
{
	return m_filepath;
}

const char* MapTexture::getMapTextureFlagToString(int flag)
{
	const char* name = NULL;
	switch (flag)
	{
	case MapTexture_Mirage:
		name = "de_mirage";
		break;
	case MapTexture_Inferno:
		name = "de_inferno";
		break;
	case MapTexture_Dust2:
		name = "de_dust2";
		break;
	case MapTexture_Train:
		name = "de_train";
		break;
	case MapTexture_Ancient:
		name = "de_ancient";
		break;
	case MapTexture_Nuke:
		name = "de_nuke";
		break;
	case MapTexture_Vertigo:
		name = "de_vertigo";
		break;
	case MapTexture_Cache:
		name = "de_cache";
		break;
	case MapTexture_Overpass:
		name = "de_overpass";
		break;
	default:
		name = NULL;
		break;
	}
	return name;
}

char* MapTexture::getMapName()
{
	return m_mapname;
}

void MapTexture::setHeight(int ht)
{
	m_height = ht;
}

void MapTexture::setWidth(int wid)
{
	m_width = wid;
}

void MapTexture::setTexture(PDIRECT3DTEXTURE9 tex)
{
	m_texture = tex;
}

void MapTexture::setFilePath(const char* path)
{
	if (*path)
		strcpy(m_filepath, path);
	else
		m_filepath[0] = '\0';
}



void MapTexture::setMapName(int flag)
{

	const char* name = NULL;
	if (flag)
	{
		name = getMapTextureFlagToString(flag);
		if (*name)
			strcpy(m_mapname, name);
		else
			m_mapname[0] = '\0';
	}
	else
		m_mapname[0] = '\0';
}




//TODO: Change path name to project folder path to handle map textures
// within program
void MapTexture::LoadMapTexture(int flags, LPDIRECT3DDEVICE9* g_Device)
{
	char curDir[MAX_PATH];
	if (!g_Device)
	{
		//TODO: Handle Error
		fprintf(stderr, "No 3d device provided!");
		exit(EXIT_FAILURE);
	}

	if (!getcwd(curDir, MAX_PATH))
	{
		// TODO: Handle Error
		fprintf(stderr, "Failed to get current working directory!\n");
		exit(EXIT_FAILURE);
	}
	printf("******************\n");
	printf("Current working directory: ");
	printf("%s\n", curDir);

	// TODO: Adjust this to handle filepaths for each user accordingly
	switch (flags)
	{
	case MapTexture_Mirage:
		//setFilePath("C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_mirage_radar.dds");
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_mirage_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Inferno:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_inferno_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Dust2:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_dust2_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Train:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_train_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Ancient:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_ancient_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Nuke:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_nuke_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Vertigo:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_vertigo_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Cache:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_cache_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);
		break;
	case MapTexture_Overpass:
		strcpy(m_filepath, "C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\DDSFiles\\de_overpass_radar.dds");
		LoadTextureFromFile(g_Device, m_filepath, &m_texture, &m_width, &m_height);

		break;
	default:
		printf("Invalid map choice!!");
		break;
	}
}





// Simple helper function to load an image into a DX9 texture with common settings
bool MapTexture::LoadTextureFromFile(LPDIRECT3DDEVICE9* g_Device,
	const char* filename,
	PDIRECT3DTEXTURE9* out_texture,
	int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	//HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
	HRESULT hr = D3DXCreateTextureFromFileA(*g_Device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}



/****************************************************************************/
/*  MapTextureHandler class and the prototypes associated to the class are  */
/*  defined here                                                            */
/****************************************************************************/



/*
* This class handles the MapTexture class
*/
MapTextureHandler::MapTextureHandler(LPDIRECT3DDEVICE9* pdev)
{
	if (!pdev)
	{
		// TODO: Handle Error
		//Handle error here, for now return with exit failure
		fprintf(stderr, "pointer to 3d device missing!!");
		exit(EXIT_FAILURE);
	}
	memset(this, 0, sizeof(this));
	m_mapTextures.resize(MapTexture_COUNT);
	pDevice = pdev;
	LoadAllMapTextures(pDevice);
}

MapTextureHandler::~MapTextureHandler()
{
	m_mapTextures.clear();
	pDevice = NULL;
	memset(this, 0, sizeof(this));
}



void MapTextureHandler::LoadAllMapTextures(LPDIRECT3DDEVICE9* g_Device)
{
	MapTexture tex;
	for (int i = 0; i < MapTexture_COUNT; i++)
	{
		m_mapTextures[i].LoadMapTexture(i, g_Device);
		m_mapTextures[i].setMapName(i);
	}
}



void MapTextureHandler::AddMapTexture(MapTexture tex)
{
	m_mapTextures.push_back(tex);
}


MapTexture MapTextureHandler::getMapTexture(int flag)
{
	return m_mapTextures[flag];
}




















/********************TESTING************************/
void MapTexture::Render()
{
	if (ImGui::Begin(m_mapname, &m_isActive, 0))
	{
		//ImVector<ImVec2> points;
		std::vector<ImVec2> points(100);
		static ImVec2 scrolling(0.0f, 0.0f);
		static bool adding_line = false;
		static bool opt_enable_context_menu = true;
		static bool opt_enable_grid = true;
		ImGuiIO& io = ImGui::GetIO();




		//ImGui::Image((void*)getTexture(), ImVec2(getWidth(), getHeight()));



		/************************************************/
		/******************* Test code ******************/
		/************************************************/

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
		ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
		if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);


		// Draw a red circle
		draw_list->AddImage((void*)getTexture(), canvas_p0, canvas_p1, ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255));
		//draw_list->AddImage((void*)getTexture(), canvas_p0, canvas_p1, ImVec2(0, 0), ImVec2(1, 1));


		// This will catch our interactions
		ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
		const bool is_hovered = ImGui::IsItemHovered(); // Hovered
		const bool is_active = ImGui::IsItemActive();	// Held
		const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
		const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);


		//draw_list->AddCircleFilled(ImVec2(p.x + 50, p.y + 50), 30.0f, IM_COL32(255, 0, 0, 255), 16);
		// Draw a 3 pixel thick yellow line
		draw_list->AddLine(ImVec2(p.x, p.y), ImVec2(p.x + 100.0f, p.y + 100.0f), IM_COL32(255, 255, 0, 255), 3.0f);
		// Advance the ImGui cursor to claim space in the window (otherwise the window will appears small and needs to be resized)
		ImGui::Dummy(ImVec2(200, 200));
		ImGui::Text("x: %d\ny: %d", canvas_p1.x, canvas_p1.y);


		// Add first and second point
		if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			points.push_back(mouse_pos_in_canvas);
			points.push_back(mouse_pos_in_canvas);
			adding_line = true;
		}
		if (adding_line)
		{
			points.back() = mouse_pos_in_canvas;
			if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
				adding_line = false;
		}

		// Pan (we use a zero mouse threshold when there's no context menu)
			// You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
		const float mouse_threshold_for_pan = opt_enable_context_menu ? -1.0f : 0.0f;
		if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
		{
			scrolling.x += io.MouseDelta.x;
			scrolling.y += io.MouseDelta.y;
		}

		// Context menu (under default mouse threshold)
		ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		if (opt_enable_context_menu && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
			ImGui::OpenPopupOnItemClick("context");
		if (ImGui::BeginPopup("context"))
		{
			if (adding_line)
				points.resize(points.size() - 2);
			adding_line = false;
			if (ImGui::MenuItem("Remove one", NULL, false, points.size() > 0)) { points.resize(points.size() - 2); }
			if (ImGui::MenuItem("Remove all", NULL, false, points.size() > 0)) { points.clear(); }
			ImGui::EndPopup();
		}

		// Draw grid + all lines in the canvas
		//ccccccccdraw_list->PushClipRect(canvas_p0, canvas_p1, true);
#if 0
		if (opt_enable_grid)
		{
			const float GRID_STEP = 64.0f;
			for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
				draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
			for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
				draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
		}
#endif

		for (int n = 0; n < points.size(); n += 2)
			draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
		//draw_list->PopClipRect();



#if 0
		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
		ImVec2 canvas_sz = ImGui::GetContentRegionAvail();

		if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
#endif
		// Draw border and background color

		//draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
		//draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
		//draw_list->AddImage()



		/************************************************/
	}
	ImGui::End();
}

void MapTexture::Disable()
{
	m_isActive = false;
}

void MapTexture::Enable()
{
	m_isActive = true;
}

bool MapTexture::getIsActive()
{
	return m_isActive;
}