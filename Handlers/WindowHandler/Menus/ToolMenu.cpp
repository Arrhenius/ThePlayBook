#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "../../../imgui/imgui.h"
#include "Headers/ToolMenu.h"



ToolMenu::ToolMenu()
{

}

ToolMenu::~ToolMenu()
{
	memset(this, 0, sizeof(this));
}

void ToolMenu::Render()
{
	if (m_active == false)
		return;
}