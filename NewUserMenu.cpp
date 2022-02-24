#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include "NewUserMenu.h"
#include "imgui/imgui.h"
#include <stdio.h>
#include <ctype.h>
#include <direct.h>
#include <regex>


NewUserMenu::NewUserMenu()
{
	memset(this, 0, sizeof(this));

	m_height = 0;
	m_width	= 0;
	m_active = false;
	m_formcomplete = false;

	m_errorFirstName = false;
	m_errorLastName	= false;
	m_errorUsername	= false;
	m_errorEmail = false;
	m_errorPassword = false;

	strcpy(m_label, "New User");
	m_firstname[0]	= '\0';
	m_lastname[0]	= '\0';
	m_username[0]	= '\0';
	m_email[0]		= '\0';
	m_cmpemail[0]	= '\0';
	m_password[0]	= '\0';
	m_cmppw[0]		= '\0';
	userData = NULL;
}

NewUserMenu::~NewUserMenu()
{
	memset(this, 0, sizeof(this));
}

void NewUserMenu::NewUserForm()
{
	static ImVec2	wndSz;

	wndSz = ImGui::GetWindowSize();

	int adjustment = -40;
	//TODO: Use variables for position manipulation
	// Draw the First Name input box
	ImGui::PushItemWidth(300);
	//ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 140 + adjustment));
	//ImGui::InputText("First Name", m_firstname, sizeof(m_firstname), 0, 0, 0);
	//ImGui::PopItemWidth();
	handleFirstNameField(wndSz, adjustment);
	handleLastNameField(wndSz, adjustment);
	handleUsernameField(wndSz, adjustment);
	handleEmailField(wndSz, adjustment);
	handlePasswordField(wndSz, adjustment);
	ImGui::PopItemWidth();
#if 0
	if (getErrorLastName() == true && m_lastname[0] != '\0' && m_lastname[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 95 + adjustment));
		ImGui::InputText("Last Name", m_lastname, sizeof(m_lastname), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 95 + adjustment));
		ImGui::InputText("Last Name", m_lastname, sizeof(m_lastname), 0, 0, 0);
	}
	


	ImGui::PushItemWidth(300);
	ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 50 + adjustment));
	ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);

	//ImGui::PushItemWidth(200);
	ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 5 + adjustment));
	ImGui::InputText("Email", m_email, sizeof(m_email), 0, 0, 0);
	ImGui::PopItemWidth();

	ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 40 + adjustment));
	ImGui::InputText("Confirm Email", m_cmpemail, sizeof(m_cmpemail), 0, 0, 0);


	ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 85 + adjustment));
	ImGui::InputText("Password", m_password, sizeof(m_password), ImGuiInputTextFlags_Password, 0, 0);
	

	ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 130 + adjustment));
	ImGui::InputText("Confirm Password", m_cmppw, sizeof(m_cmppw), ImGuiInputTextFlags_Password, 0, 0);
	ImGui::PopItemWidth();
#endif

}

void NewUserMenu::handleFirstNameField(ImVec2 wndSz, int adjustment)
{
	

	if (getErrorFirstName() == true && m_firstname[0] != '\0' && m_firstname[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 140 + adjustment));
		ImGui::InputText("First Name", m_firstname, sizeof(m_firstname), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 140 + adjustment));
		ImGui::InputText("First Name", m_firstname, sizeof(m_firstname), 0, 0, 0);
	}
}


void NewUserMenu::handleLastNameField(ImVec2 wndSz, int adjustment)
{

	if (getErrorLastName() == true && m_lastname[0] != '\0' && m_lastname[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 95 + adjustment));
		ImGui::InputText("Last Name", m_lastname, sizeof(m_lastname), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 95 + adjustment));
		ImGui::InputText("Last Name", m_lastname, sizeof(m_lastname), 0, 0, 0);
	}
}

void NewUserMenu::handleUsernameField(ImVec2 wndSz, int adjustment)
{
	if (getErrorUsername() == true && m_username[0] != '\0' && m_username[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 50 + adjustment));
		ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 50 + adjustment));
		ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);
	}
}

void NewUserMenu::handleEmailField(ImVec2 wndSz, int adjustment)
{

	// First email field
	if (getErrorEmail() == true && m_email[0] != '\0' && m_email[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 5 + adjustment));
		ImGui::InputText("Email", m_email, sizeof(m_email), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 5 + adjustment));
		ImGui::InputText("Email", m_email, sizeof(m_email), 0, 0, 0);
	}

	// 2nd email field
	if (getErrorEmail() == true && m_cmpemail[0] != '\0' && m_cmpemail[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 40 + adjustment));
		ImGui::InputText("Confirm Email", m_cmpemail, sizeof(m_cmpemail), 0, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 40 + adjustment));
		ImGui::InputText("Confirm Email", m_cmpemail, sizeof(m_cmpemail), 0, 0, 0);
	}
}

void NewUserMenu::handlePasswordField(ImVec2 wndSz, int adjustment)
{

	// This handles the first password field
	if (getErrorLastName() == true && m_lastname[0] != '\0' && m_lastname[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 85 + adjustment));
		ImGui::InputText("Password", m_password, sizeof(m_password), ImGuiInputTextFlags_Password, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 85 + adjustment));
		ImGui::InputText("Password", m_password, sizeof(m_password), ImGuiInputTextFlags_Password, 0, 0);
	}


	// This handles the second password field
	if (getErrorLastName() == true && m_lastname[0] != '\0' && m_lastname[0] != '\n')
	{
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 130 + adjustment));
		ImGui::InputText("Confirm Password", m_cmppw, sizeof(m_cmppw), ImGuiInputTextFlags_Password, 0, 0);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 130 + adjustment));
		ImGui::InputText("Confirm Password", m_cmppw, sizeof(m_cmppw), ImGuiInputTextFlags_Password, 0, 0);
	}

}


void NewUserMenu::NewUserButtons()
{
	static ImVec2 wndSz;

	wndSz = ImGui::GetWindowSize();
	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 240, wndSz.y / 2 + 180));
	if (ImGui::Button("Cancel", ImVec2(110, 22)))
	{
		Disable();
	}

	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 50, wndSz.y / 2 + 180));
	if (ImGui::Button("Clear", ImVec2(110, 22)))
	{
		//ZeroMemory(this, sizeof(this));
		ClearNewUserData();
	}

	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) + 140, wndSz.y / 2 + 180));
	if (ImGui::Button("Create User", ImVec2(110, 22)))
	{
		ValidateData();
		if (getIsFormComplete() == true)
		{
			SaveData();
			Disable();
		}
			
		//if(m_formcomplete == true)
		// When button is pressed data that was entered will now be passed to the UserHandler
		// class and will store the data accordingly in the application
	}
}

void NewUserMenu::ClearNewUserData()
{
	m_formcomplete = false;
	m_errorFirstName = false;
	m_errorLastName = false;
	m_errorUsername = false;
	m_errorEmail = false;
	m_errorPassword = false;
	memset(m_firstname,	0, sizeof(m_firstname));
	memset(m_lastname,	0, sizeof(m_lastname));
	memset(m_username,	0, sizeof(m_username));
	memset(m_email,		0, sizeof(m_email));
	memset(m_cmpemail,	0, sizeof(m_cmpemail));
	memset(m_password,	0, sizeof(m_password));
	memset(m_cmppw,		0, sizeof(m_cmppw));
}



/* This will handle saving data to a local program directory */
/* so one can log in to the program in a local environment */

/*
 * This function is meant to save data in an encrypted/hashed manner
 * that currently is not implemented. It will be implemented before
 * release of this tool because user data is treated as the most 
 * important thing I should ever properly handle and I will always
 * see user data in this manner. 
 */
void NewUserMenu::SaveData()
{
	// TODO: Function incomplete 
	char path[MAXBUFSZ];
	memset(path, 0, sizeof(path));
	if(getcwd(path, MAXBUFSZ))
		printf("Directory path: %s\n", path);
}





bool NewUserMenu::getErrorFirstName()
{
	return m_errorFirstName;
}

bool NewUserMenu::getErrorLastName()
{
	return m_errorLastName;
}

bool NewUserMenu::getErrorEmail()
{
	return m_errorEmail;
}

bool NewUserMenu::getErrorPassword()
{
	return m_errorPassword;
}

bool NewUserMenu::getErrorUsername()
{
	return m_errorUsername;
}

bool NewUserMenu::getIsFormComplete()
{
	return m_formcomplete;
}

void NewUserMenu::setErrorFirstName(bool status)
{
	m_errorFirstName = status;
}

void NewUserMenu::setErrorLastName(bool status)
{
	m_errorLastName = status;
}

void NewUserMenu::setErrorUsername(bool status)
{
	m_errorUsername = status;
}

void NewUserMenu::setErrorEmail(bool status)
{
	m_errorEmail = status;
}

void NewUserMenu::setErrorPassword(bool status)
{
	m_errorPassword = status;
}

void NewUserMenu::setIsFormComplete(bool status)
{
	m_formcomplete = status;
}



void NewUserMenu::ValidateFirstName()
{
	char* p;
	p = m_firstname;
	if (*p == '\n' || *p == '\0')
	{
		setErrorFirstName(true);
		return;
	}
	while (*p)
	{
		if (isalpha(*p) == 0)
		{
			setErrorFirstName(true);
			return;
		}
		p++;
	}
	setErrorFirstName(false);
}

void NewUserMenu::ValidateLastName()
{
	char* p;
	p = m_lastname;
	if (*p == '\n' || *p == '\0')
	{
		setErrorLastName(true);
		return;
	}
	while (*p)
	{
		if (isalpha(*p) == 0)
		{
			setErrorLastName(true);
			return;
		}
		p++;
	}
	setErrorLastName(false);
}

void NewUserMenu::ValidateUsername()
{
	char* p;
	p = m_username;
	if (*p == '\n' || *p == '\0')
	{
		setErrorUsername(true);
		return;
	}
	while (*p)
	{
		if (isalnum(*p) == 0)
		{
			setErrorUsername(true);
			return;
		}
		p++;
	}
	setErrorUsername(false);
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
 * display that error to the user or them to fix
 */
void NewUserMenu::ValidateEmail()
{	
	char* p = m_email;
	if (*p == '\n' || *p == '\0')
	{
		setErrorEmail(true);
		return;
	}
	if (std::regex_match(m_email, std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+")))
		setErrorEmail(false);
	else
		setErrorEmail(true);

	if (strcmp(m_email, m_cmpemail) == 0)
		setErrorEmail(false);
	else
		setErrorEmail(true);
}



/* 
 * Checks to see if passwords entered match and verifies if
 * the password is of a correct length.
 */

void NewUserMenu::ValidatePassword()
{
	if (m_password[0] == '\n' || m_password[0] == '\0' ||
		m_cmppw[0] == '\n' || m_cmppw[0] == '\0' )
	{
		setErrorFirstName(true);
		return;
	}
	if (strcmp(m_password, m_cmppw) == 0)
		setErrorPassword(false);
	else
		setErrorPassword(true);
	if (strlen(m_password) >= 8)
		setErrorPassword(false);
	else
		setErrorPassword(true);
}

bool NewUserMenu::CheckCompletion()
{
	if (getErrorFirstName() == true)
		return false;
	else if (getErrorLastName() == true)
		return false;
	else if (getErrorUsername() == true)
		return false;
	else if (getErrorEmail() == true)
		return false;
	else if (getErrorPassword() == true)
		return false;
	else
		return true;
}


void NewUserMenu::ValidateData()
{
	ValidateFirstName();
	ValidateLastName();
	ValidateUsername();
	ValidateEmail();
	ValidatePassword();

	// Verifies all data is acceptable by checking error status for
	// each individual check. If any errors return true it is assumed
	// the form is incomplete
	setIsFormComplete(CheckCompletion());

}





// This is the main function call to render the
// create new user window form if no account
// currently exists for the user
void NewUserMenu::Render()
{

	if (getIsActive() == false)
		return;
	//ImGui::SetNextWindowSize()
	
	if (ImGui::Begin(m_label, 0, 0))
	{
		NewUserForm();
		NewUserButtons();
	}
	ImGui::End();

}

void NewUserMenu::Enable()
{
	m_active = true;
}

void NewUserMenu::Disable()
{
	m_active = false;
}

int NewUserMenu::getWidth()
{
	return m_width;
}

int NewUserMenu::getHeight()
{
	return m_height;
}

bool NewUserMenu::getIsActive()
{
	return m_active;
}
