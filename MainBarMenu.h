#ifndef MAINBARMENU_H
#define MAINBARMENU_H


#include "Helper.h"


class MainBarMenu
{
public:
	MainBarMenu();
	~MainBarMenu();

	//UI declarations
	void	Render();
	void	Disable();
	void	Enable();
	char* getLabel();

private:
	bool	m_active;
	char	m_label[MAXLABELSZ];
};


#endif // MAINBARMENU_H
