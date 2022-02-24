#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "Helper.h"
#include "imgui/imgui.h"


class MainWindow
{
public:
	MainWindow();
	~MainWindow();

	// getters
	int		getWidth();
	int		getHeight();
	char* getLabel();

	// setters
	void	setWidth(int width);
	void	setHeight(int height);
	void	setLabel(char* label);

	// UI Handlers
	void	Render();
	void	Enable();
	void	Disable();

private:
	ImVec2	m_vec2;
	int		m_width;
	int		m_height;
	bool	m_active;
	char	m_label[MAXLABELSZ];

};


#endif // MAINWINDOW_H
