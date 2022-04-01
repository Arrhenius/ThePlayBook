#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE




#include "NewUserMenu.h"
#include "imgui/imgui.h"
#include <stdio.h>
#include <ctype.h>
#include <direct.h>
#include <regex>
#include <fcntl.h>
#include <sys/types.h>


// Solution found:
// https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c

// Might adjust this to something else in the future but for now will be used
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


// Obtained from:
// https://stackoverflow.com/questions/11238918/s-isreg-macro-undefined

// Windows does not define the S_ISREG and S_ISDIR macros in stat.h, so we do.
// We have to define _CRT_INTERNAL_NONSTDC_NAMES 1 before #including sys/stat.h
// in order for Microsoft's stat.h to define names like S_IFMT, S_IFREG, and S_IFDIR,
// rather than just defining  _S_IFMT, _S_IFREG, and _S_IFDIR as it normally does.
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif







NewUserMenu::NewUserMenu()
{

	m_height = 0;
	m_width = 0;
	m_active = false;
	m_formcomplete = false;

	m_errorFirstName = false;
	m_errorLastName = false;
	m_errorUsername = false;
	m_errorEmail = false;
	m_errorPassword = false;

	memset(m_label, 0, sizeof(m_label));
	memset(m_firstname, 0, sizeof(m_firstname));
	memset(m_lastname, 0, sizeof(m_lastname));
	memset(m_username, 0, sizeof(m_username));
	memset(m_email, 0, sizeof(m_email));
	memset(m_cmpemail, 0, sizeof(m_cmpemail));
	memset(m_password, 0, sizeof(m_password));
	memset(m_cmppw, 0, sizeof(m_cmppw));

	strcpy(m_label, "New User");
	m_firstname[0] = '\0';
	m_lastname[0] = '\0';
	m_username[0] = '\0';
	m_email[0] = '\0';
	m_cmpemail[0] = '\0';
	m_password[0] = '\0';
	m_cmppw[0] = '\0';
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
	
	ImGui::PushItemWidth(300);
	handleFirstNameField(wndSz, adjustment);
	handleLastNameField(wndSz, adjustment);
	handleUsernameField(wndSz, adjustment);
	handleEmailField(wndSz, adjustment);
	handlePasswordField(wndSz, adjustment);
	ImGui::PopItemWidth();
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
	bool errEnabled = false;

	// First email field
	if (getErrorEmail() == true && m_email[0] != '\0' && m_email[0] != '\n')
	{
		errEnabled = true;
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
	}
	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 - 5 + adjustment));
	ImGui::InputText("Email", m_email, sizeof(m_email), 0, 0, 0);
	if (errEnabled)
	{
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		errEnabled = false;
	}

	// 2nd email field
	if (getErrorEmail() == true && m_cmpemail[0] != '\0' && m_cmpemail[0] != '\n')
	{
		errEnabled = true;
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
	}
	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 40 + adjustment));
	ImGui::InputText("Confirm Email", m_cmpemail, sizeof(m_cmpemail), 0, 0, 0);
	if (errEnabled)
	{
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		errEnabled = false;
	}

}

void NewUserMenu::handlePasswordField(ImVec2 wndSz, int adjustment)
{
	bool errEnabled = false;
	// This handles the first password field
	if (getErrorPassword() == true && m_password[0] != '\0' && m_lastname[0] != '\n')
	{
		errEnabled = true;
		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
	}
	ImGui::SetCursorPos(ImVec2((wndSz.x / 2) - 180, wndSz.y / 2 + 85 + adjustment));
	ImGui::InputText("Password", m_password, sizeof(m_password), ImGuiInputTextFlags_Password, 0, 0);
	if (errEnabled)
	{
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		errEnabled = false;
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
	
	memset(m_firstname, 0, sizeof(m_firstname));
	memset(m_lastname, 0, sizeof(m_lastname));
	memset(m_username, 0, sizeof(m_username));
	memset(m_email, 0, sizeof(m_email));
	memset(m_cmpemail, 0, sizeof(m_cmpemail));
	memset(m_password, 0, sizeof(m_password));
	memset(m_cmppw, 0, sizeof(m_cmppw));

}



/* This will handle saving data to a local program directory 
 * so one can log in to the program in a local environment 
 * if no internet is available. This also implies I will have
 * all associated files for the player available locally as
 * well. The option will eventually be provided to the user
 * if they wish to store their plays locally and/or on the web.
 */

/*
 * NOTE:
 * This function is meant to save data in an encrypted/hashed manner
 * that currently is not implemented. It will be implemented before
 * release of this tool because user data is treated as the most
 * important thing I should ever properly handle and I will always
 * see user data in this manner.
 */
void NewUserMenu::SaveLocal(UserHandler* user)
{
	int fd;
	char path[MAXBUFSZ];
	struct stat dir;



	// To handle directory existence stat will be used for now
	// but will later be adjusted to avoid the time-of-check to 
	// time-of-use bug (though I think this issue shouldn't be
	// too pressing given the task this tool is being created
	// for
	// TODO: Create error logger to handle the endless mess that
	// could potentially occur here
	memset(path, 0, sizeof(MAXBUFSZ));

	if (getcwd(path, NULL))
		printf("Current directory: %s\n", path);
	else
	{
		fprintf(stderr, "Failed to obtain current directory\n");
		exit(EXIT_FAILURE);
	}

	strcat(path, SAVEDIR);
	if (stat(path, &dir) == 0 && S_ISDIR(dir.st_mode))
	{
		printf("Proceeding to save data...\n");
	}
	else
	{
		if (mkdir(path) == -1)
		{
			fprintf(stderr, "Failed to create directory at path '%s'!\n", path);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	if (chdir(path) != 0)
	{
		perror("Directory change failed ");

	}
	strcat(path, SAVEFILEWSEP);
	
	

	//if( access(SAVEFILE, F_OK) == 0)

	// Data: 3-30-22
	// NOTE:
	// In the future this will check for the existence of the file and 
	// instead of rewriting over the old data will seek to the end and append
	// the new data. For simplicity and just for single user scenarios and for
	// the sake of getting the tool to an alpha/beta stage I have left this
	// as the approach. I will adjust this before release to the public.
	// TODO: Allow adding of data and not just rewriting over saved data.
	fd = open(SAVEFILE, _O_BINARY | _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE);
	if (fd < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}

	
	
	write(fd, (void*)user, sizeof(UserHandler));
	// Check if directory exists


	// append save file name to directory path
	//strcat(path, "\\")

	//fd = open()

	



	//fd = open()
}

// TODO: Isolate this function
void NewUserMenu::SaveData()
{
	// TODO: Function incomplete
	// TODO: Add encryption
	userData = new UserHandler();
	userData->setFirstName(m_firstname);
	userData->setLastName(m_lastname);
	userData->setEmail(m_email);
	userData->setUsername(m_username);
	
	SaveLocal(userData);
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
  * display that error to the user for them to fix
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
		m_cmppw[0] == '\n' || m_cmppw[0] == '\0')
	{
		setErrorPassword(true);
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
