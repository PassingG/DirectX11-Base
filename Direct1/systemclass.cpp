#include "stdafx.h"
#include "InputClass.h"
#include "graphicsclass.h"
#include "systemclass.h"

SystemClass::SystemClass()
{
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	// ������ â ����, ���� ���� ���� �ʱ�ȭ
	int screenWidth = 0;
	int screenHeight = 0;

	// ������ ���� �ʱ�ȭ
	InitializeWindows(screenWidth, screenHeight);

	// m_Input ��ü ����. �� Ŭ������ ���� ������� Ű���� �Է� ó���� ���˴ϴ�.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// m_Input ��ü �ʱ�ȭ
	m_Input->Initialize();

	// m_Graphics ��ü ����. �׷��� �������� ó���ϱ� ���� ��ü�Դϴ�.
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	// m_Graphics ��ü �ʱ�ȭ
	return m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
}

void SystemClass::Shutdown()
{
	// m_Graphics ��ü ��ȯ
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// m_Input ��ü ��ȯ
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Windows ���� ó��
	ShutdownWindows();
}

void SystemClass::Run()
{
	// �޽��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// ����ڷκ��� ���� �޽����� ���������� �޽��������� ����.
	while (true)
	{
		// ������ �޽����� ó���Ѵ�.
		if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
		{
			// ���� �޽����� ���� ��� �޽��� ������ Ż���Ѵ�.
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �� �ܿ��� Frame �Լ��� ó���Ѵ�.
			if (!Frame())
				break;
		}
	}
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Ű���尡 �������°� ó��
	case WM_KEYDOWN:
	{
		// Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�.
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Ű���尡 �������°� ó��
	case WM_KEYUP:
	{
		// Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// �� ���� ��� �޽������� �⺻ �޽��� ó���� �ѱ�ϴ�,
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	}
}

bool SystemClass::Frame()
{
	// ESC Ű ���� �� ���� ���θ� ó���Ѵ�.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// �׷��� ��ü�� Frame�� ó��.
	return m_Graphics->Frame();
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	// �ܺ� �����͸� �� ��ü�� �����Ѵ�.
	ApplicationHandle = this;

	// �� ���α׷��� �ν��Ͻ��� �����´�.
	m_hinstance = GetModuleHandle(NULL);

	// ���α׷� �̸��� �����Ѵ�.
	m_applicationName = L"Dx11 Study";

	// windows Ŭ������ �Ʒ��� ���� �����Ѵ�.
	WNDCLASSEX wc;
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	= WndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= m_hinstance;
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm		= wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// windows class �� ����Ѵ�.
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� �о�´�.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	// FULL_SCREEN ���� ���� ���� ȭ���� �����Ѵ�.
	if (FULL_SCREEN)
	{
		// Ǯ��ũ�� ���� �����ߴٸ� ����� ȭ�� �ػ󵵸� ����ũ�� �ػ󵵷� �����ϰ� ������ 32bit�� �����Ѵ�.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ������ ���÷��� ������ �����Ѵ�.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// ������ ����� ��� 800 * 600 ũ��� �����Ѵ�.
		screenWidth = 800;
		screenHeight = 600;

		// ������ â�� ����, ������ �� ��� ������ �Ѵ�.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// �����츦 �����ϰ� �ڵ��� ���Ѵ�.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, 
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �����Ѵ�.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
}

void SystemClass::ShutdownWindows()
{
	// Ǯ��ũ�� ��忴�ٸ� ���÷��� ������ �ʱ�ȭ �Ѵ�.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����Ѵ�.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// ���α׷� �ν��Ͻ��� �����Ѵ�.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// �ܺ������� ������ �ʱ�ȭ�Ѵ�.
	ApplicationHandle = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// ������ ���Ḧ Ȯ���Ѵ�.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// �����찡 �������� Ȯ���Ѵ�.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� ��� �޽������� �ý��� Ŭ������ �޽��� ó���� �ѱ��.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}