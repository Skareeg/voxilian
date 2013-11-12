#include "UI.h"

CUI::CUI()
{
	rend = &CEGUI::OpenGLRenderer::bootstrapSystem();
}
void CUI::Init()
{
	CEGUI::System::create(*rend);
	Log.Log("UI system OK.",0);
}
void CUI::Draw()
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
}
CUI UI;