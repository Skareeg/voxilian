#include "UI.h"

CUI::CUI()
{
	ui = nullptr;
	loader = nullptr;
}
void CUI::Init()
{
	//Input injections
	InputCallObjPair callpair;
	callpair.call=InjectInput;
	callpair.object=this;
	InputFuncs.push_back(callpair);

	loader = new CUIImageLoader();

	CursorHide();
	CursorWindowsHide();

	ui = new MyGUI::Gui();
	logger = new MyGUI::LogManager();
	platform = new MyGUI::OpenGLPlatform();
	platform->initialise(loader);

	platform->getDataManagerPtr()->addResourceLocation("UI\\Default",false);

	platform->getRenderManagerPtr()->setViewSize(640,480);

	ui->initialise("MyGUI_Core.xml","MYGUI.txt");
	ui = MyGUI::Gui::getInstancePtr();

	Input.LockMouse(false);

	MyGUI::Window* btn = ui->createWidget<MyGUI::Window>("WindowCSX",10,10,64,32,MyGUI::Align::Default,"Main","Hi");

	Log.Log("UI system OK.",0);
}
int glfwtomygui(int i)
{
	switch(i)
	{
		case 'A':
			return MyGUI::KeyCode::A;
		case 'B':
			return MyGUI::KeyCode::B;
		case 'C':
			return MyGUI::KeyCode::C;
		case 'D':
			return MyGUI::KeyCode::D;
		case 'E':
			return MyGUI::KeyCode::E;
		case 'F':
			return MyGUI::KeyCode::F;
		case 'G':
			return MyGUI::KeyCode::G;
		case 'H':
			return MyGUI::KeyCode::H;
		case 'I':
			return MyGUI::KeyCode::I;
		case 'J':
			return MyGUI::KeyCode::J;
		case 'K':
			return MyGUI::KeyCode::K;
		case 'L':
			return MyGUI::KeyCode::L;
		case 'M':
			return MyGUI::KeyCode::M;
		case 'N':
			return MyGUI::KeyCode::N;
		case 'O':
			return MyGUI::KeyCode::O;
		case 'P':
			return MyGUI::KeyCode::P;
		case 'Q':
			return MyGUI::KeyCode::Q;
		case 'R':
			return MyGUI::KeyCode::R;
		case 'S':
			return MyGUI::KeyCode::S;
		case 'T':
			return MyGUI::KeyCode::T;
		case 'U':
			return MyGUI::KeyCode::U;
		case 'V':
			return MyGUI::KeyCode::V;
		case 'W':
			return MyGUI::KeyCode::W;
		case 'X':
			return MyGUI::KeyCode::X;
		case 'Y':
			return MyGUI::KeyCode::Y;
		case 'Z':
			return MyGUI::KeyCode::Z;
	}
	return -1;
}
void InjectInput(InputStruct in)
{
	CUI* s = (CUI*)(in.object);
	if(in.type==InputEnum::KEY)
	{
		int i = in.i;
		int j = in.j;
		int correctcode = glfwtomygui(i);
		if(correctcode>=0)
		{
			if(j==GLFW_PRESS)
			{
				MyGUI::InputManager::getInstancePtr()->injectKeyPress(MyGUI::KeyCode::Enum(correctcode));
			}
			else
			{
				MyGUI::InputManager::getInstancePtr()->injectKeyRelease(MyGUI::KeyCode::Enum(correctcode));
			}
		}
	}
	if(in.type==InputEnum::CHAR)
	{
		int i = in.i;
		int j = in.j;
		int correctcode = glfwtomygui(i);
		if(correctcode>=0)
		{
			MyGUI::InputManager::getInstancePtr()->injectKeyPress(MyGUI::KeyCode::Enum(correctcode),(char)i);
		}
	}
	if(in.type==InputEnum::MB)
	{
		int i = in.i;
		int j = in.j;
		if(i==GLFW_MOUSE_BUTTON_LEFT)
		{
			if(j==GLFW_PRESS)
			{
				MyGUI::InputManager::getInstancePtr()->injectMousePress(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Left);
			}
			else
			{
				MyGUI::InputManager::getInstancePtr()->injectMouseRelease(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Left);
			}
		}
		if(i==GLFW_MOUSE_BUTTON_MIDDLE)
		{
			if(j==GLFW_PRESS)
			{
				MyGUI::InputManager::getInstancePtr()->injectMousePress(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Middle);
			}
			else
			{
				MyGUI::InputManager::getInstancePtr()->injectMouseRelease(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Middle);
			}
		}
		if(i==GLFW_MOUSE_BUTTON_RIGHT)
		{
			if(j==GLFW_PRESS)
			{
				MyGUI::InputManager::getInstancePtr()->injectMousePress(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Right);
			}
			else
			{
				MyGUI::InputManager::getInstancePtr()->injectMouseRelease(Input.Mouse.posX,Input.Mouse.posY,
					MyGUI::MouseButton::Right);
			}
		}
	}
	if(in.type==InputEnum::MP)
	{
		int i = in.i;
		int j = in.j;
		MyGUI::InputManager::getInstancePtr()->injectMouseMove(Input.Mouse.posX,Input.Mouse.posY,0);
	}
	if(in.type==InputEnum::MW)
	{
		int i = in.i;
		int j = in.j;
		MyGUI::InputManager::getInstancePtr()->injectMouseMove(Input.Mouse.posX,Input.Mouse.posY,i);
	}
}
void CUI::Update()
{
	if(Input.Mouse.posX<0)
	{
		Input.Mouse.SetPos(0,Input.Mouse.posY);
	}
	if(Input.Mouse.posY<0)
	{
		Input.Mouse.SetPos(Input.Mouse.posX,0);
	}
	if(Input.Mouse.posX>Graphics.resolution_x)
	{
		Input.Mouse.SetPos(Graphics.resolution_x,Input.Mouse.posY);
	}
	if(Input.Mouse.posY>Graphics.resolution_y)
	{
		Input.Mouse.SetPos(Input.Mouse.posX,Graphics.resolution_y);
	}
}
void CUI::Render()
{
	if(platform)
	{
		platform->getRenderManagerPtr()->drawOneFrame();
	}
}
void CUI::CursorToggle()
{
	if(CursorVisible())
	{
		CursorHide();
	}
	else
	{
		CursorShow();
	}
}
void CUI::CursorShow()
{
	Input.LockMouse(false);
}
void CUI::CursorHide()
{
	Input.LockMouse(true);
}
bool CUI::CursorVisible()
{
	return false;
}
void CUI::CursorWindowsToggle()
{
	if(CursorWindowsVisible())
	{
		CursorWindowsHide();
	}
	else
	{
		CursorWindowsShow();
	}
}
void CUI::CursorWindowsShow()
{
	Graphics.ShowCursor(true);
	Input.LockMouse(false);
}
void CUI::CursorWindowsHide()
{
	Graphics.ShowCursor(false);
	Input.LockMouse(true);
}
bool CUI::CursorWindowsVisible()
{
	return Graphics.CursorVisible();
}
CUI UI;
void CUIImageLoader::saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename)
{
	int result = 0;
	if(_format == MyGUI::PixelFormat::R8G8B8)
	{
		result = SOIL_save_image(_filename.c_str(),SOIL_SAVE_TYPE_BMP,_width,_height,3,(unsigned char*)_texture);
	}
	else
	{
		result = SOIL_save_image(_filename.c_str(),SOIL_SAVE_TYPE_TGA,_width,_height,4,(unsigned char*)_texture);
	}
}