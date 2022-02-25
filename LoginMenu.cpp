#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "imgui/imgui.h"
#include "LoginMenu.h"



LoginMenu::LoginMenu()
{
	m_width = 0;
	m_height = 0;
	m_active = false;
	memset(m_label, 0, sizeof(m_label));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));
	strcpy(m_label, "Login");
	m_username[0] = '\0';
	m_password[0] = '\0';
}

LoginMenu::~LoginMenu()
{
	memset(this, 0, sizeof(this));
}


void LoginMenu::Disable()
{
	m_active = false;
}

void LoginMenu::Enable()
{
	m_active = true;
}

void LoginMenu::EnableLoading()
{
	m_loading = true;
}

void LoginMenu::DisableLoading()
{
	m_loading = false;
}

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

bool LoginMenu::getLoading()
{
	return m_loading;
}



void LoginMenu::Render()
{
	static ImVec2	v2Login;
	static ImVec2	v2Forgot;
	static ImVec2	v2;
	static bool		isActive;


	if (m_active == false)
		return;

	if (ImGui::Begin(m_label, &isActive, 0))
	{


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
#if 1

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
	}
	ImGui::End();







	if (isActive == false)
		Disable();
}