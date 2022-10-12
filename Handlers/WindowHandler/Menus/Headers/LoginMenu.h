#ifndef LOGINMENU_H
#define LOGINMENU_H

#include "../../../../BaseWindow.h"


class LoginMenu : public BaseWindow
{
public:
	LoginMenu();
	~LoginMenu();


	
	void		Render();
	void		EnableLoading();
	void		DisableLoading();
	bool		getLoading();
private:

	void		LoginMenuForm();
	void		LoginMenuButtons();
	void		LoginButton();
	void		CreateAccountButton();
	void		ForgotPasswordButton();
	void		handlePasswordField(ImVec2 wndSz, int adjustment);
	void		handleUsernameField(ImVec2 wndSz, int adjustment);


	bool		m_loading;
	char		m_username[MAXNAMESZ];
	char		m_password[MAXKEYSZ];

};


#endif // LOGINMENU_H
