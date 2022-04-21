#ifndef USERHANDLER_H
#define USERHANDLER_H


#include "Helper.h"
#include "PlayBookHandler.h"

class UserHandler
{
public:
	UserHandler();
	~UserHandler();

	// Getters
	PlayBookHandler* getPlayBook();
	char*	getUsername();
	char*	getEmail();
	char*	getFirstName();
	char*	getLastName();
	char*	getKey();

	// Setters
	void	setUsername(const char* username);
	void	setLastName(const char* lastname);
	void	setFirstName(const char* firstname);
	void	setEmail(const char* email);
	void	setKey(const char* key);

private:
	char	m_firstname[MAXNAMESZ];
	char	m_lastname[MAXNAMESZ];
	char	m_username[MAXNAMESZ];
	char	m_email[MAXEMAILSZ];
	char	m_key[MAXKEYSZ];
	PlayBookHandler* m_playbook;
};



#endif // USERHANDLER_H
