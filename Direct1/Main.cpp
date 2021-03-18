#include "stdafx.h"
#include "systemclass.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR IpCmdLine, _In_ int nCmdShow)
{
	//System 객체 생성
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	//System 객체 초기화 및 실행
	if (System->Initialize())
	{
		System->Run();
	}

	//System 객체 종료 및 메모리 반환
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
//{
//	SystemClass* System;
//	bool result;
//
//
//	// Create the system object.
//	System = new SystemClass;
//	if (!System)
//	{
//		return 0;
//	}
//
//	// Initialize and run the system object.
//	result = System->Initialize();
//	if (result)
//	{
//		System->Run();
//	}
//
//	// Shutdown and release the system object.
//	System->Shutdown();
//	delete System;
//	System = 0;
//
//	return 0;
//}