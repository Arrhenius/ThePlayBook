#ifndef TOOLMENU_H
#define TOOLMENU_H

#include "../../../../Helper.h"

class ToolMenu
{
public:
	ToolMenu();
	~ToolMenu();

	// UI prototypes
	void	Render();
	void	Disable();
	void	Enable();
private:
	bool	m_active;
	char	m_label[MAXLABELSZ];

};


#endif // TOOLMENU_H
