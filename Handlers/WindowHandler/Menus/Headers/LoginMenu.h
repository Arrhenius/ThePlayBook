#ifndef LOGINMENU_H
#define LOGINMENU_H

#include "Helper.h"


class LoginMenu
{
public:
	LoginMenu();
	~LoginMenu();


	// UI prototypes
	void		Render();
	void		Disable();
	void		Enable();


	void		EnableLoading();
	void		DisableLoading();
	bool		getIsActive();
	int			getHeight();
	int			getWidth();
	bool		getLoading();
private:
	int			m_width;
	int			m_height;
	bool		m_active;
	bool		m_loading;
	char		m_label[MAXLABELSZ];
	char		m_username[MAXNAMESZ];
	char		m_password[MAXKEYSZ];

};


#endif // LOGINMENU_H
