#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "MainWindow.h"
//#include "imgui/imgui.h"

MainWindow::MainWindow()
{
	memset(this, 0, sizeof(this));
	m_width = 0;
	m_height = 0;
	strcpy(m_label, "Main Window");
}

MainWindow::~MainWindow()
{
	memset(this, 0, sizeof(this));
}

int MainWindow::getWidth()
{
	return m_width;
}

int MainWindow::getHeight()
{
	return m_height;
}

char* MainWindow::getLabel()
{
	return m_label;
}

void MainWindow::setWidth(int width)
{
	m_width = width;
}

void MainWindow::setHeight(int height)
{
	m_height = height;
}

void MainWindow::setLabel(char* label)
{
	size_t len = sizeof(label);
	if (len >= MAXLABELSZ)
	{
		fprintf(stderr, "Begin function label exceeds max size!");
		exit(EXIT_FAILURE);
	}
	if (*label)
		strcpy(m_label, label);
	else
		m_label[0] = '\0';
}

void MainWindow::Render()
{
	if (m_active == false)
		return;
	//ImGui::GetIO
	ImGui::SetNextWindowPos(ImVec2(1920 * 0.5f, 1080 * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	m_vec2 = ImGui::GetWindowSize();
	ImVec2 v2(1920, 1080);
	ImGui::SetNextWindowSize(v2, 0);
	if (ImGui::Begin(m_label, 0, 0))
	{

	}
	ImGui::End();
}


void MainWindow::Enable()
{
	m_active = true;
}

void MainWindow::Disable()
{
	m_active = false;
}