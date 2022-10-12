#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * The headers are completely broken because visual studio
 * is clueless when it comes to handling folders and file
 * structure of a program. Will Fix when properly releasing.
 */

#include "../../../../Helper.h"
#include "../../../../imgui/imgui.h"
#include "../../../../BaseWindow.h"



class MainWindow : public BaseWindow
{
public:
	MainWindow();
	~MainWindow();

	void Render();

	// getters
	//int		getWidth();
	//int		getHeight();
	//char*	getLabel();

	// setters
	//void	setWidth(int width);
	//void	setHeight(int height);
	//void	setLabel(char* label);

	// UI Handlers
	
	//void	Enable();
	//void	Disable();

private:
	ImVec2	m_vec2;
	//int		m_width;
	//int		m_height;
	//bool	m_active;
	//char	m_label[MAXLABELSZ];

};


#endif // MAINWINDOW_H
