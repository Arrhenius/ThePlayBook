#include "Validator.h"
#include <string.h>
#include <ctype.h>
#include <regex>



bool FirstNameValidator(char* firstname)
{
	char* p;
	p = firstname;
	if (*p == '\n' || *p == '\0')
		return true;
	while (*p)
	{
		if (isalpha(*p) == 0)
			return true;
		p++;
	}
	return false;
}


bool LastNameValidator(char* lastname)
{
	char* p;
	p = lastname;
	if (*p == '\n' || *p == '\0')
	{
		return true;
	}
	while (*p)
	{
		if (isalpha(*p) == 0)
			return true;
		p++;
	}
	return false;
}

bool UsernameValidator(char* username)
{
	char* p;
	p = username;
	if (*p == '\n' || *p == '\0')
	{
		return true;
	}
	while (*p)
	{
		if (isalnum(*p) == 0)
			return true;
		p++;
	}
	return false;
}


/* Email validation is something I need to work on, for now I
 * am using this regex expression I located online. The reliability
 * of this method is still questionable but for now this is
 * what I will be using until something seriously breaks
 *
 * const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
 *
 */


 /*
  * This function will perform a variety of email checks to
  * check the validity of the provided email
  *
  * TODO: Create individual error handlers for each error and
  * display that error to the user for them to fix
  */
bool EmailValidator(char* email, char* cmpemail)
{
	char* p = email;
	if (*p == '\n' || *p == '\0')
		return true;
	if (!std::regex_match(email, std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+")))
		return true;
	if (strcmp(email, cmpemail) != 0)
		return true;
	return false;
}

bool KeysValidator(char* key, char* cmpkey)
{
	if (key[0] == '\n' || key[0] == '\0' ||
		cmpkey[0] == '\n' || cmpkey[0] == '\0')
	{
		return true;
	}
	if (strcmp(key, cmpkey) != 0)
		return true;
	if (strlen(key) < 8 || strlen(cmpkey) < 8)
		return true;
	return false;
}
