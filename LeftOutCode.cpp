#if 0


int adjustment = -20;

//TODO: Use variables for position manipulation
// Draw the First Name input box
ImGui::PushItemWidth(300);
ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 140 + adjustment));
ImGui::InputText("First Name", m_firstname, sizeof(m_firstname), 0, 0, 0);
//ImGui::PopItemWidth();

//ImGui::PushItemWidth(200);
ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 95 + adjustment));
ImGui::InputText("Last Name", m_lastname, sizeof(m_lastname), 0, 0, 0);


ImGui::PushItemWidth(300);
ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 50 + adjustment));
ImGui::InputText("Username", m_username, sizeof(m_username), 0, 0, 0);

//ImGui::PushItemWidth(200);
ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 - 5 + adjustment));
ImGui::InputText("Email", m_email, sizeof(m_email), 0, 0, 0);
//ImGui::PopItemWidth();

ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 40 + adjustment));
ImGui::InputText("Confirm Email", m_cmpemail, sizeof(m_cmpemail), 0, 0, 0);


ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 85 + adjustment));
ImGui::InputText("Password", m_password, sizeof(m_password), ImGuiInputTextFlags_Password, 0, 0);
//ImGui::PopItemWidth();

ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 180, v2First.y / 2 + 130 + adjustment));
ImGui::InputText("Confirm Password", m_cmppw, sizeof(m_cmppw), ImGuiInputTextFlags_Password, 0, 0);



ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 240, v2First.y / 2 + 180));
if (ImGui::Button("Cancel", ImVec2(110, 22)))
{

}

ImGui::SetCursorPos(ImVec2((v2First.x / 2) - 50, v2First.y / 2 + 180));
if (ImGui::Button("Clear", ImVec2(110, 22)))
{

}
// TODO: Check if passwords match
// TODO: Check if email matches
#endif