#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "../../../imgui/imgui.h"
#include "Headers/LoginMenu.h"



LoginMenu::LoginMenu()
{
	//m_width = 0;
	//m_height = 0;
	//m_active = false;
	//memset(m_label, 0, sizeof(m_label));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));
	//strcpy(m_label, "Login");
	setLabel((char*)"Login");
	m_username[0] = '\0';
	m_password[0] = '\0';
}

LoginMenu::~LoginMenu()
{
	memset(this, 0, sizeof(this));
}

#if 0
void LoginMenu::Disable()
{
	m_active = false;
}

void LoginMenu::Enable()
{
	m_active = true;
}
#endif

void LoginMenu::EnableLoading()
{
	m_loading = true;
}

void LoginMenu::DisableLoading()
{
	m_loading = false;
}

#if 0
int LoginMenu::getHeight()
{
	return m_height;
}

int LoginMenu::getWidth()
{
	return m_width;
}


bool LoginMenu::getIsActive()
{
	return m_active;
}
#endif

bool LoginMenu::getLoading()
{
	return m_loading;
}



void LoginMenu::handleUsernameField(ImVec2 windowSize, int adjustment)
{
	ImGui::SetCursorPos(ImVec2((windowSize.x / 2) - 155, (windowSize.y / 2) - 80));
	ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);
}

void LoginMenu::handlePasswordField(ImVec2 windowSize, int adjustment)
{

	// Draw the Password input box
	ImGui::SetCursorPos(ImVec2((windowSize.x / 2) - 155, windowSize.y / 2 - 35));
	if (ImGui::InputText("Password", m_password, sizeof(m_password),
		ImGuiInputTextFlags_Password | ImGuiInputTextFlags_EnterReturnsTrue, 0, 0))
	{

		//isLoading = true;
		EnableLoading();
		//this->setLoading(true);

	}

}


/*
* This function displays the fields necessary to log into
* the tool and load necessary data associated with the user.
* Specifically, the Username and Password field.
*/
void LoginMenu::LoginMenuForm()
{
	static ImVec2	windowSize;
	int adjustment = 50;
	
	windowSize = ImGui::GetWindowSize();
	

	ImGui::PushItemWidth(300);
	handleUsernameField(windowSize, adjustment);
	handlePasswordField(windowSize, adjustment);
	ImGui::PopItemWidth();

}


void LoginMenu::LoginButton()
{
	static ImVec2	windowSz;
	static ImVec2	size;
	windowSz = ImGui::GetWindowSize();
	size.x = (windowSz.x / 2) - 55;
	size.y = (windowSz.y / 2) + 55;


	// TODO: Look this over for a small rewrite
	// This shows the "Connecting" text with a rotating
	// bar to indicate a loading status
	//ImGui::SetCursorPos(ImVec2((size.x / 2) - 50, size.y / 2 + 30));
	ImGui::SetCursorPos(ImVec2(size.x, size.y - 20));
	if (getLoading() == true)
	{
		//ImGui::SetCursorPos(ImVec2((size.x / 2) - 40, size.y / 2 + 30));
		ImGui::SetCursorPos(ImVec2(size.x + 15, size.y - 20));
		ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

	}
	else if (ImGui::Button("Login", ImVec2(110, 22)))
	{
		
		//loading = true;
		EnableLoading();
		//LoadUser();
		//this->setLoading(true);
	}
}


void LoginMenu::CreateAccountButton()
{
	static ImVec2	windowSz;
	static ImVec2	size;
	windowSz = ImGui::GetWindowSize();
	size.x = (windowSz.x / 2) - 55;
	size.y = (windowSz.y / 2) + 55;

	// Displays the "Create Account" button
	ImGui::SetCursorPos(ImVec2(size.x, size.y + 80));
	if (ImGui::Button("Create Account", ImVec2(110, 22)))
	{
		//this->setDisplayLogin(false);
		//this->setDisplayLogin(false);
		DisableLoading();

		//ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

	}

}

void LoginMenu::ForgotPasswordButton()
{
	static ImVec2	windowSz;
	static ImVec2	size;
	windowSz = ImGui::GetWindowSize();
	size.x = (windowSz.x / 2) - 55;
	size.y = (windowSz.y / 2) + 55;

	// Displays the "Forgot Password" button
	ImGui::SetCursorPos(ImVec2(size.x, size.y + 30));
	ImGui::Button("Forgot Password", ImVec2(110, 22));
}

void LoginMenu::LoginMenuButtons()
{
	static ImVec2	windowSz;
	static ImVec2	size;
	windowSz = ImGui::GetWindowSize();
	size.x = (windowSz.x / 2) - 50;
	size.y = (windowSz.y / 2) + 50;

	LoginButton();
	ForgotPasswordButton();
	CreateAccountButton();
#if 0
	// Displays the "Forgot Password" button
	ImGui::SetCursorPos(ImVec2(size.x, size.y + 30));
	ImGui::Button("Forgot Password", ImVec2(110, 22));


	// Displays the "Create Account" button
	ImGui::SetCursorPos(ImVec2(size.x, size.y + 80));
	if (ImGui::Button("Create Account", ImVec2(110, 22)))
	{
		//this->setDisplayLogin(false);
		//this->setDisplayLogin(false);
		DisableLoading();

		ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

	}
#endif

#if 0
	// TODO: Look this over for a small rewrite
	// This shows the "Connecting" text with a rotating
	// bar to indicate a loading status
	ImGui::SetCursorPos(ImVec2((size.x / 2) - 50, size.y / 2 + 30));
	if (getLoading() == true)
	{
		ImGui::SetCursorPos(ImVec2((size.x / 2) - 40, size.y / 2 + 30));
		ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

	}
	else if (ImGui::Button("Login", ImVec2(110, 22)))
	{
		//loading = true;
		EnableLoading();
		//this->setLoading(true);
	}

#endif

}


void LoginMenu::Render()
{
	static ImVec2	v2Login;
	static ImVec2	v2Forgot;
	static ImVec2	v2;
	static bool		isActive;


	if (getIsActive() == false)
		return;
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 800.f, 680.f });
	if (ImGui::Begin(getLabel(), &isActive, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{

		LoginMenuForm();
		LoginMenuButtons();
#if 0
		v2Login = ImGui::GetWindowSize();
		v2.x = (v2Login.x / 2) - 50;
		v2.y = (v2Login.y / 2) + 50;

		//ImGui::EndMenuBar();
		// Draw the Username input box
		ImGui::SetCursorPos(ImVec2((v2Login.x / 2) - 100, v2Login.y / 2 - 70));
		ImGui::PushItemWidth(200);
		ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);


		// Draw the Password input box
		ImGui::SetCursorPos(ImVec2((v2Login.x / 2) - 105, v2Login.y / 2 - 35));
		if (ImGui::InputText("Password", m_password, sizeof(m_password),
			ImGuiInputTextFlags_Password | ImGuiInputTextFlags_EnterReturnsTrue, 0, 0))
		{
			//isLoading = true;
			EnableLoading();
			//this->setLoading(true);
		}
#endif
#if 0

		// TODO: Look this over for a small rewrite
		// This shows the "Connecting" text with a rotating
		// bar to indicate a loading status
		ImGui::SetCursorPos(ImVec2((v2Login.x / 2) - 50, v2Login.y / 2 + 30));
		if (getLoading() == true)
		{
			ImGui::SetCursorPos(ImVec2((v2Login.x / 2) - 40, v2Login.y / 2 + 30));
			ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

		}
		else if (ImGui::Button("Login", ImVec2(110, 22)))
		{
			//loading = true;
			EnableLoading();
			//this->setLoading(true);
		}
#if 0
		// Displays the "Forgot Password" button
		ImGui::SetCursorPos(ImVec2(v2.x, v2.y + 30));
		ImGui::Button("Forgot Password", ImVec2(110, 22));

		// Displays the "Create Account" button
		ImGui::SetCursorPos(ImVec2(v2.x, v2.y + 80));
		if (ImGui::Button("Create Account", ImVec2(110, 22)))
		{
			//this->setDisplayLogin(false);
			//this->setDisplayLogin(false);
			DisableLoading();

			ImGui::Text("Connecting %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

		}
#endif
#endif
	}
	ImGui::End();
	ImGui::PopStyleVar();
}