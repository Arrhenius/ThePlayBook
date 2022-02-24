#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0000
#include <dinput.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "WindowHandler.h"
#include "LoginMenu.h"
#include "MainBarMenu.h"
#include <D3dx9tex.h>
#include "MapTextureHandler.h"
#pragma comment(lib, "D3dx9")
#pragma comment(lib, "d3d9.lib")



// Data
static LPDIRECT3D9				g_pD3D = NULL;
static LPDIRECT3DDEVICE9		g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS	g_d3dpp = {};

// Code for separators
#if 0
ImGui::Begin("Splitter test");

static float w = 200.0f;
static float h = 300.0f;
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
ImGui::BeginChild("child1", ImVec2(w, h), true);
ImGui::EndChild();
ImGui::SameLine();
ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
if (ImGui::IsItemActive())
w += ImGui::GetIO().MouseDelta.x;
ImGui::SameLine();
ImGui::BeginChild("child2", ImVec2(0, h), true);
ImGui::EndChild();
ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
if (ImGui::IsItemActive())
h += ImGui::GetIO().MouseDelta.y;
ImGui::BeginChild("child3", ImVec2(0, 0), true);
ImGui::EndChild();
ImGui::PopStyleVar();

ImGui::End();
#endif



#if 0
// Simple helper function to load an image into a DX9 texture with common settings
bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9 * out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
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
#endif

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

int main(int nargs, char* argv[])
{

	//D3DDEVICE_CREATION_PARAMETERS cparams;
	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("The Play Book"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	//::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::ShowWindow(hwnd, SW_MAXIMIZE);
	::UpdateWindow(hwnd);



	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);


	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


#if 0

	//float texture_w = (float)io.Fonts->TexWidth;
	//float texture_h = (float)io.Fonts->TexHeight;
	//float my_texture_width = (float)io.Fonts->TexWidth;
	//float my_texture_height = (float)io.Fonts->TexHeight;
	int my_image_width = 0;
	int my_image_height = 0;
	int my_width = 0;
	int my_height = 0;

	PDIRECT3DTEXTURE9 my_texture = NULL;
	PDIRECT3DTEXTURE9 my_tex = NULL;
	bool ret = LoadTextureFromFile("C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\de_inferno_radar.dds",
		&my_texture, &my_image_width, &my_image_height);
	bool ret2 = LoadTextureFromFile("C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\de_mirage_radar.dds",
		&my_tex, &my_width, &my_height);
	IM_ASSERT(ret);
#endif




	/**********************************************/
	/*** Load all map textures before main loop ***/
	/**********************************************/

	MapTextureHandler* gameMaps = new MapTextureHandler(&g_pd3dDevice);
	MapTexture			tempTex;
	int					i;
	for (i = 1; i < MapTexture_COUNT; i++)
	{
		printf("i: %d\n", i);
		tempTex = gameMaps->getMapTexture(i);
		printf("%s\n", tempTex.getMapName());
	}
	/***********************************************/


	/*************************************************/
	/* Some necessary variables to start the program */
	/*************************************************/

	LoginMenu* login = new LoginMenu();
	login->Enable();
	MainBarMenu* barmenu = new MainBarMenu();
	barmenu->Enable();
	NewUserMenu* newUser = new NewUserMenu();
	newUser->Enable();
	MainWindow* main = new MainWindow();
	main->Enable();
	MapTexture mTex2 = gameMaps->getMapTexture(MapTexture_Mirage);


	/*************************************************/


	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}


		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();








		// TODO: Look at refining this mess. A good chunk was copied and
		// pasted due to personal ignorance in the initialization process
		// involved with Dear ImGui. As time progresses this will evidently
		// look cleaner, but for now, deal with this mess

		/*****************************************************************/
		/************************* CODE BEGINS ***************************/
		/*****************************************************************/

		int gameWindowFlags = 0;
		static bool run = true;

		ImGui::ShowDemoWindow();
		//LoginMenu* login = new LoginMenu();

		login->Enable();
		login->Render();
		barmenu->Render();
		newUser->Render();
		//main->Render();


		mTex2.Render();


		// IM_ASSERT(ret);
		 /*
		 * float texture_w = (float)io.Fonts->TexWidth;
		 float texture_h = (float)io.Fonts->TexHeight;
		 int my_image_width = 0;
		 int my_image_height = 0;
		 PDIRECT3DTEXTURE9 my_texture = NULL;
		 bool ret = LoadTextureFromFile("C:\\Users\\Jetfo\\Desktop\\CSGOMaps\\de_inferno_radar.png",
										 &my_texture, &my_image_width, &my_image_height);
		 */


		 //printf("I'm here right now\n\n");
#if 0
		MapTexture mTex = gameMaps->getMapTexture(MapTexture_Ancient);
		MapTexture mTex2 = gameMaps->getMapTexture(MapTexture_Mirage);
		MapTexture mTex3 = gameMaps->getMapTexture(MapTexture_Inferno);
		mTex.DisplayTextureWindow();
		mTex2.DisplayTextureWindow();
		mTex3.DisplayTextureWindow();

		MapTexture tmpTex;
		for (int i = 1; i < MapTexture_COUNT; i++)
		{
			tmpTex = gameMaps->getMapTexture(i);
			if (tmpTex.getIsActive())
				tmpTex.DisplayTextureWindow();
		}
#endif
#if 0
		if (ImGui::Begin("Mirage", &run, 0))
		{

			//ImGui::Text("size = %d x %d", mapMirage.getWidth(), mapMirage.getHeight());
			MapTexture mTex = gameMaps->getMapTexture(MapTexture_Mirage);
			ImGui::Image((void*)mTex.getTexture(), ImVec2(mTex.getWidth(), mTex.getHeight()));
			//ImGui::Text("size = %d x %d", )
		}
		ImGui::End();

		if (ImGui::Begin("Ancient", &run, 0))
		{

			//ImGui::Text("size = %d x %d", mapMirage.getWidth(), mapMirage.getHeight());
			MapTexture mTex = gameMaps->getMapTexture(MapTexture_Ancient);
			ImGui::Image((void*)mTex.getTexture(), ImVec2(mTex.getWidth(), mTex.getHeight()));
			//ImGui::Text("size = %d x %d", )
		}
		ImGui::End();

#endif
#if 0
		if (ImGui::Begin("Image Demo", &run, 0))
		{
			//ImGui::Text("pointer = %p", my_texture);
			ImGui::Text("size = %d x %d", my_image_width, my_image_height);
			ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
		}
		ImGui::End();

		if (ImGui::Begin("Image Demo 2", &run, 0))
		{
			ImGui::Text("size = %d x %d", my_width, my_height);
			ImGui::Image((void*)my_tex, ImVec2(my_width, my_height));
		}

		ImGui::End();

#endif
		/*****************************************************************/
		/************************** CODE ENDS ****************************/
		/*****************************************************************/







		// Rendering
		ImGui::EndFrame();
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		// Handle loss of D3D9 device
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			ResetDevice();



	} // while (msg.message != WM_QUIT)




	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);


	return EXIT_SUCCESS;
}