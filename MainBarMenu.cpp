#define _CRT_SECURE_NO_WARNINGS

#include "MainBarMenu.h"
#include "imgui/imgui.h"



MainBarMenu::MainBarMenu()
{
	memset(this, 0, sizeof(this));
	m_active = false;
	m_label[0] = '\0';
}

MainBarMenu::~MainBarMenu()
{
	memset(this, 0, sizeof(this));
}

void MainBarMenu::Disable()
{
	m_active = false;
}

void MainBarMenu::Enable()
{
	m_active = true;
}

char* MainBarMenu::getLabel()
{
	return m_label;
}


// This is the main render function for this menu
// and everything that it will handle.
void MainBarMenu::Render()
{
	if (m_active == false)
		return;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
}
		ImGui::EndMainMenuBar();
	}

#if 0
	if (ImGui::Begin("MainMenuBar", 0, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Close"))
					Disable();
				ImGui::EndMenu();
			}
			//ImGui::EndMenu();
			ImGui::EndMenuBar();
		}
	}
	ImGui::End();
#endif
	//ImGui::EndMenuBar();
}