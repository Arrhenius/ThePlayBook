#include "WindowHandler.h"
#include <stdio.h>
#include <stdlib.h>






WindowHandler::WindowHandler()
{

}

WindowHandler::~WindowHandler()
{
	
}

void WindowHandler::RunWindow(bool* p_open)
{
	// Main body of the Demo window starts here.
	if (!ImGui::Begin("The Play Book Demo", p_open, 0))
	{
		ImGui::End();
		return;
	}
	
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);



	ImGui::PopItemWidth();
	ImGui::End();
}