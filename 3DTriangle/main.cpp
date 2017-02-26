#define WIN32_LEAN_AND_MEAN  //去除无用的头文件，加快编译速度

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <tchar.h>

#include <T3DEngine/T3DDevice.h>
#include <T3DEngine/T3DWindow.h>
#include <T3DEngine/T3DCamera.h>
#include <T3DEngine/T3DMath.h>
#include <T3DEngine/T3DMesh.h>
#include <T3DEngine/T3DLog.h>

//游戏初始化
void GameInit()
{

}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdstr, int ncmdshow)
{
	//T3D::Log::OpenErrorFile("ERROR.TXT");

	T3D::Window *window = new T3D::Window(800, 600, "SoftRender");
	if (!window->Init())
	{
		DWORD err = GetLastError();
		MessageBox(NULL, _T("window init error"), _T("ERROR"), MB_OKCANCEL);
		return 1;
	}
	unsigned int *framebuffer = window->GetFrameBuffer();

	T3D::Camera * cam = new T3D::Camera(T3D::Vec4{ 0, 0, 0, 1 }, T3D::Vec4{ 0, 0, 0, 1 }, T3D::Vec4{ 0, 0, 1, 1 }, 50.0, 1000.0, 90.0, 800, 600);

	T3D::Device *device = new T3D::Device(cam);
	device->Init(framebuffer);

	T3D::Object *object = new T3D::Object;
	int result = T3D::PLGLoader::LoadObjectPLG(object, "C:/Users/shentongle/Desktop/tank1.plg", T3D::Vec4{ 1, 1, 1, 0 }, T3D::Vec4{ 0, 0, 300, 0 }, T3D::Vec4{0, 0, 0, 0});
	if (result != 0)
	{
		MessageBox(NULL, _T("Load Plg file error"), _T("ERROR"), MB_OKCANCEL);
		return 1;
	}

	cam->BuildCameraMatrixUVN(UVN_MODE_SIMPLE);

	object->SetPos(T3D::Vec4{ 0, 0, 400 });
	object->SynchroVertex();
	object->ModelToWorld();
	object->WorldToCamera(*cam);
	object->CameraToPerspective(*cam);
	object->PerspectiveToScreen(*cam);

	while (!window->IsExit()) 
	{
		device->Clear();
		object->DrawWire16(*cam, framebuffer, 800);
		window->Update();
	}

	return 0;
}