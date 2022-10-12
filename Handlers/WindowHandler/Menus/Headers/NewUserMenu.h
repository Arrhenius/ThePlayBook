#ifndef NEWUSERMENU_H
#define NEWUSERMENU_H


/*
* NOTE:
* 
* Visual Studio royally screws up the file structure of projects
* when you create new folders and files. For some reason it always
* stores it at the root of the directory and never actually adds
* files or folders where you place them. For now this messy approach
* to including files will remain until I take the time to do it all
* by hand and fix it within file explorer. I'm avoiding that now
* to not lose focus on the main task
*/ 

#include "../../../../Helper.h"
#include "../../../UserHandler/UserHandler.h"
#include "../../../../BaseWindow.h"


// TODO: Abstract this class with other classes or namespaces
// Current class design is a bit bloated and can probably
// be simplified rather significantly
class NewUserMenu : public BaseWindow
{
public:
	NewUserMenu();
	~NewUserMenu();

	// UI handlers
	void	Render();

	// Getters
	//int		getHeight();
	//int		getWidth();
	//bool	getIsActive();
	//char*	getLabel();

	// Setters
	void	setHeight(int height);
	void	setWidth(int width);
	void	setLabel(const char* label);
	//void	setFirstName(const char* firstname);
	//void	setLastName(const char* lastname);
	//void	setUserName(const char* username);
	//void	setEmail(const char* email);

private:
	// Internal functions that are only called while render function is enabled.
	void	NewUserForm();
	void	NewUserButtons();
	void	ClearNewUserData();
	void	SaveData();

	// Internal functions for data validation
	void	ValidateData();
	void	ValidateFirstName();
	void	ValidateLastName();
	void	ValidateUsername();
	void	ValidateEmail();
	void	ValidatePassword();
	bool	CheckCompletion();

	// Internal functions to handle the individual fields
	void	handleFirstNameField(ImVec2 wndSz, int adjustment);
	void	handleLastNameField(ImVec2 wndSz, int adjustment);
	void	handleUsernameField(ImVec2 wndSz, int adjustment);
	void	handleEmailField(ImVec2 wndsz, int adjustment);
	void	handlePasswordField(ImVec2 wndSz, int adjustment);

	// Internal getters 
	bool	getErrorFirstName();
	bool	getErrorLastName();
	bool	getErrorUsername();
	bool	getErrorEmail();
	bool	getErrorPassword();
	bool	getIsFormComplete();

	// Internal Setters
	void	setErrorFirstName(bool status);
	void	setErrorLastName(bool status);
	void	setErrorUsername(bool status);
	void	setErrorEmail(bool status);
	void	setErrorPassword(bool status);
	void	setIsFormComplete(bool status);


	// Misc
	void	SaveLocal(UserHandler* user);

	// ******************** class members ****************************

	bool	m_formcomplete;

	// TODO: Turn these into bit flags instead in the future
	// Variables used to handle form input errors
	bool	m_errorFirstName;
	bool	m_errorLastName;
	bool	m_errorUsername;
	bool	m_errorEmail;
	bool	m_errorPassword;

	// Data
	char	m_firstname[MAXNAMESZ];
	char	m_lastname[MAXNAMESZ];
	char	m_username[MAXNAMESZ];
	char	m_email[MAXEMAILSZ];
	char	m_cmpemail[MAXEMAILSZ];

	// TODO: Modify how the password is handled
	// I have not decided how I will handle the password for the user in the
	// backend. For now while under development I have left it like this but
	// will be adjusted as development continues...as soon as I figure out
	// what is the best way to handle this in regards to the security of the field
	char	m_password[MAXKEYSZ];
	char	m_cmppw[MAXKEYSZ];

	// This will temporarily hold data before it is saved locally. This will
	// immediately be wiped from memory upon save.
	UserHandler* userData;
};


#endif // NEWUSERMENU_H
