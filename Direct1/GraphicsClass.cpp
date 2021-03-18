#include "GraphicsClass.h"
#include "stdafx.h"
#include "D3DClass.h"

GraphicsClass::GraphicsClass()
{
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    // Direct3D ��ü ����
    m_Direct3D = (D3DClass*)_aligned_malloc(sizeof(D3DClass), 16);
    if (!m_Direct3D)
    {
        return false;
    }

    // Direct3D �ʱ�ȭ
    if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    return true;
}

void GraphicsClass::Shutdown()
{
    // Direct3D ��ü ��ȯ
    if (m_Direct3D)
    {
        m_Direct3D->Shutdown();
        _aligned_free(m_Direct3D);
        m_Direct3D = 0;
    }
}

bool GraphicsClass::Frame()
{
    // �׷��� ������ ó��
    return Render();
}

bool GraphicsClass::Render()
{
    // ���� �׸��� ���� ���۸� ����ϴ�.
    m_Direct3D->BeginScene(0.0f,0.0f,0.0f,1.0f);

    // ������ ������ ȭ�鿡 ����մϴ�
    m_Direct3D->EndScene();

    return true;
}