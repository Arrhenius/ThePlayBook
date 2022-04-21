#define _CRT_SECURE_NO_WARNINGS
#include "UserHandler.h"
#include <string.h>



UserHandler::UserHandler()
{
	memset(this, 0, sizeof(this));
	m_firstname[0] = '\0';
	m_lastname[0] = '\0';
	m_username[0] = '\0';
	m_email[0] = '\0';
	m_playbook = NULL;
}

UserHandler::~UserHandler()
{
	memset(this, 0, sizeof(this));
}

PlayBookHandler* UserHandler::getPlayBook()
{
	return m_playbook;
}

char* UserHandler::getUsername()
{
	return m_username;
}

char* UserHandler::getEmail()
{
	return m_email;
}

char* UserHandler::getFirstName()
{
	return m_firstname;
}

char* UserHandler::getLastName()
{
	return m_lastname;
}

char* UserHandler::getKey()
{
	return m_key;
}

void UserHandler::setUsername(const char* username)
{
	if (*username)
		strcpy(m_username, username);
	else
		m_username[0] = '\0';
}

void UserHandler::setLastName(const char* lastname)
{
	if (*lastname)
		strcpy(m_username, lastname);
	else
		m_username[0] = '\0';
}

void UserHandler::setFirstName(const char* firstname)
{
	if (*firstname)
		strcpy(m_username, firstname);
	else
		m_username[0] = '\0';
}

void UserHandler::setEmail(const char* email)
{
	if (*email)
		strcpy(m_username, email);
	else
		m_username[0] = '\0';
}

void UserHandler::setKey(const char* key)
{
	if (*key)
		strcpy(m_key, key);
	else
		m_key[0] = '\0';
}
