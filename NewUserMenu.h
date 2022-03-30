#ifndef NEWUSERMENU_H
#define NEWUSERMENU_H


#include "Helper.h"
#include "UserHandler.h"

#define SAVEDIR			"\\Local"
#define SAVEFILEWSEP	"\\local.dat"
#define SAVEFILE		"local.dat"


// TODO: Abstract this class with another class or namespace
// Current class design is a bit bloated and can probably
// be simplified significantly
class NewUserMenu
{
public:
	NewUserMenu();
	~NewUserMenu();

	// UI handlers
	void	Render();
	void	Disable();
	void	Enable();

	// Getters
	int		getHeight();
	int		getWidth();
	bool	getIsActive();
	char*	getLabel();

	// Setters
	void	setHeight(int height);
	void	setWidth(int width);
	void	setLabel(const char* label);
	void	setFirstName(const char* firstname);
	void	setLastName(const char* lastname);
	void	setUserName(const char* username);
	void	setEmail(const char* email);

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
	int		m_height;
	int		m_width;
	bool	m_active;
	bool	m_formcomplete;

	// TODO: Turn these into bit flags instead in the future
	// Variables used to handle form input errors
	bool	m_errorFirstName;
	bool	m_errorLastName;
	bool	m_errorUsername;
	bool	m_errorEmail;
	bool	m_errorPassword;

	// Data
	char	m_label[MAXLABELSZ];
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
	char	m_password[MAXPWSZ];
	char	m_cmppw[MAXPWSZ];

	// This will be the data that will be copied to a UserHandler object
	// Program will automatically clear data from memory once transferred
	UserHandler* userData;
};


#endif // NEWUSERMENU_H
