#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H
#include "imgui/imgui.h"

#include "NewUserMenu.h"
#include "MainWindow.h"

#define _CRT_SECURE_NO_WARNINGS


// These flags will be used strictly to determine
// which windows are open and which are currently closed
enum eGameWindowFlags
{
	GameWindowFlags_ImageHandler	= 1 << 0,   // Flag to enable the image handler window
	GameWindowFlags_LoginHandler	= 1 << 1,	// Enables Login handler window
	GameWindowFlags_ChatHandler		= 1 << 2,	// Enables chat handler window
	GameWindowFlags_ToolHandler		= 1 << 3	// enables the tool handler for the image window
};

class WindowHandler
{
public:
	WindowHandler();
	~WindowHandler();

	void	RunWindow(bool* p_open);
private:
};


#endif // WINDOWHANDLER_H
