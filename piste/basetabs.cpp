#include "piste.h"


void MW::TabBarAction(const char* text, std::function<void()> a)
{
	ImGui::Text(text);

	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();


	if (ImGui::IsItemHovered()) {
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(min.x, min.y - ImGui::GetStyle().FramePadding.y), ImVec2(max.x, max.y + ImGui::GetStyle().FramePadding.y), IM_COL32(50, 50, 50, 170));
		if (ImGui::IsItemClicked())
			a();
	}
	ImGui::Separator();
}
void MW::ButtonAction(const char* text, std::function<void()> a)
{
	if (ImGui::Button(text))
		a();

	//ImVec2 min = ImGui::GetItemRectMin();
	//ImVec2 max = ImGui::GetItemRectMax();


	//if (ImGui::IsItemHovered()) {
	//	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(min.x, min.y - ImGui::GetStyle().FramePadding.y), ImVec2(max.x, max.y + ImGui::GetStyle().FramePadding.y), IM_COL32(50, 50, 50, 170));
	//	if (ImGui::IsItemClicked())
	//		a();
	//}
	//ImGui::Separator();
}
void MW::ToggleAction(const char* text, bool& var, std::function<void()> a)
{

	
	if (var) {
		
		//float height = max.y - min.y;
		ImGui::TextColored(ImVec4(0, 255, 0, 170), text);

		//ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(min.x + 10, min.y + 10), ImVec2(min.x + 20, min.y + 20), IM_COL32(0, 255, 0, 170));
	
	}else
		ImGui::Text(text);

	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();


	if (ImGui::IsItemHovered()) {
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(min.x, min.y - ImGui::GetStyle().FramePadding.y), ImVec2(max.x, max.y + ImGui::GetStyle().FramePadding.y), IM_COL32(50, 50, 50, 170));

		if (ImGui::IsItemClicked()) {
			//var = !var;
			a();
		}

	}

	

}
void MW::RenderTabBar()
{
	if (ImGui::BeginMenuBar()) {

		

	}ImGui::EndMenuBar();

}