#pragma once

#include <windows.h>
#include <thread>
#include <future>
#include"../imgui-includes/imgui.h"
#include"../imgui-backends/imgui_impl_dx9.h"
#include"../imgui-backends/imgui_impl_win32.h"
#include<d3d9.h>
#include<tchar.h>
#include "..\ApplicationServices\ThreadNotifier.h"

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};


bool CreateDeviceD3D(HWND hWnd);

void CleanupDeviceD3D();

void ResetDevice();

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ApplicationObjectHelperTool: public ThreadEventsHandler {

public:

	ApplicationObjectHelperTool();

	int init(ThreadNotifier* threadNoti);

	void close();

	virtual void onMessageRecieved(PanelListener* pll);

private:

	HWND hwnd;
	WNDCLASSEX wc;
	float ImGuiWidth;
	float ImGuiHight;
	float posX;
	float posY;
	bool panelForceClose;

};