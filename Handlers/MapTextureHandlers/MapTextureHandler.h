#ifndef MAPTEXTUREHANDLER_H
#define MAPTEXTUREHANDLER_H

#include <vector>

#include <d3d9.h>
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")
#pragma comment(lib, "d3d9.lib")

#define NAMEMAX 64


enum eMapTextureFlags
{
	MapTexture_Mirage = 1,
	MapTexture_Inferno,
	MapTexture_Dust2,
	MapTexture_Train,
	MapTexture_Ancient,
	MapTexture_Nuke,
	MapTexture_Vertigo,
	MapTexture_Cache,
	MapTexture_Overpass,
	MapTexture_COUNT
};


// This class will handle the map itself and everything associated to it. This includes draw data
// and the strats created on this map if such data is available for this particular user

// TODO: Must find solution to handle multi level maps
class MapTexture
{
public:
	MapTexture();
	~MapTexture();

	// Getters
	PDIRECT3DTEXTURE9	getTexture();
	int					getWidth();
	int					getHeight();
	const char* getFilepath();
	const char* getMapTextureFlagToString(int flag);
	char* getMapName();

	// Setters
	void				setHeight(int ht);
	void				setWidth(int wid);
	void				setTexture(PDIRECT3DTEXTURE9 tex);
	void				setFilePath(const char* path);
	void				setMapName(int flag);


	void				LoadMapTexture(int flags, LPDIRECT3DDEVICE9* g_Device);
	bool				LoadTextureFromFile(LPDIRECT3DDEVICE9* g_Device, const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
	void				AddDrawData(int data);

	/**********    Testing   ************/
	void				Render();
	void				Disable();
	void				Enable();
	bool				getIsActive();

private:
	// LPDIRECT3DDEVICE9 g_pd3dDevice;
	// Will probably need a variable to hold draw data such as playbook strats
	PDIRECT3DTEXTURE9	m_texture;
	int					m_width;
	int					m_height;
	char				m_filepath[MAX_PATH];
	char				m_mapname[NAMEMAX];

	// Some variable here will be needed for draw data on the map and
	// another variable for holding all the plays for this map that
	// have been created and saved


	/**********    Testing   ************/
	bool				m_isActive;


	//TODO:	Add necessary variables to handle loading all the plays
	//		associated with this map texture.
};





// This class will be holding everything associated to a particular map in a vector.
// Upon start of the program it will load everything to ram. This seemed like the smart
// thing to do for such a small program.
class MapTextureHandler
{
public:
	MapTextureHandler(LPDIRECT3DDEVICE9* pdev);
	~MapTextureHandler();

	void		AddMapTexture(MapTexture tex);
	void		LoadAllMapTextures(LPDIRECT3DDEVICE9* g_Device);
	MapTexture	getMapTexture(int flag);


	//void	LoadMapTexture(int flags, LPDIRECT3DDEVICE9* g_Device);
	//bool	LoadTextureFromFile(LPDIRECT3DDEVICE9* g_Device, const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
	//void	AddDrawData(int data);
	//void	createNewMapTexture();

private:
	LPDIRECT3DDEVICE9* pDevice;
	std::vector<MapTexture> m_mapTextures;
};





#endif // MAPTEXTUREHANDLER_H
