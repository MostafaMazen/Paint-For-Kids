#include"ApplicationObjectHelperTool.h"
#include<iostream>
#include<string>
#include<future>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}



ApplicationObjectHelperTool::ApplicationObjectHelperTool()
{
    panelForceClose = false;
}

int ApplicationObjectHelperTool::init(ThreadNotifier* threadNoti) {

    this->ImGuiWidth = 300.f;
    this->ImGuiHight = 450.f;
    this->posX = 0.f;
    this->posY = 0.f;

    wc = { sizeof(WNDCLASSEX), CS_CLASSDC,WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);

    hwnd = ::CreateWindow(wc.lpszClassName, _T("ApplicationManagerHelper"), WS_OVERLAPPED | WS_SYSMENU, posX, posY, ImGuiWidth, ImGuiHight, NULL, NULL, wc.hInstance, NULL);


    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    { 
        threadNoti->on("PANEL_FORCE_CLOSE", this);
        if (panelForceClose == true) {
            break;
        }
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

  

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
       
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
      
        /////////////////////////////////////////////////////////////
         
        std::async(std::launch::async, [this, threadNoti]() {
            {

                //OUR UI WILL BE HERE 
                static bool colorMode = false; // we don't need to send it in the channel 
                ImGui::SetNextWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHight));
                ImGui::SetNextWindowPos(ImVec2((float)posX, (float)posY));
                ImGui::Begin("CFigure Control Panal");
                ImGui::Text("Figure Color");
                static float redBuffer = 0;
                static float greenBuffer = 0;
                static float blueBuffer = 0;
                static float CrossHairColor[3] = { 0,0,0 };
                ImGui::ColorPicker3("Figure Color", CrossHairColor);

                //std::cout << "red : " << std::to_string((int)(CrossHairColor[0] * 255)) << "green : " << std::to_string((int)CrossHairColor[1] * 255) << " blue" << std::to_string(int(CrossHairColor[2] * 255)) << std::endl;
                ImGui::Text("Figure Top and back layer");
                static const char* items[]{ "Background Color","Drawing Color","Filling Color" ,"Figure Color" };
                static int selectedItem = 0;
                ImGui::ListBox("State", &selectedItem, items, IM_ARRAYSIZE(items));
                //std::cout << "selected :  " << selectedItem<<std::endl;
                ImGui::Checkbox("DarkMode", &colorMode);
                if (colorMode == true) {
                    ImGui::StyleColorsDark();
                }
                else {
                    ImGui::StyleColorsLight();
                }
                if (redBuffer != CrossHairColor[0] && greenBuffer != CrossHairColor[1] && blueBuffer != CrossHairColor[2]) {
                    PanelListener pl;
                    pl.appPanelMngr = nullptr;
                    pl.stat = PANAL_SENDING_COLOR;
                    pl.target = selectedItem;
                    pl.selectedObjColor = color(CrossHairColor[0] * 255, CrossHairColor[1] * 255, CrossHairColor[2] * 255);
                    threadNoti->emit("PANEL_CHANGE_COLOR", &pl);
                    redBuffer = CrossHairColor[0];
                    greenBuffer = CrossHairColor[1];
                    blueBuffer = CrossHairColor[2];
                }
                ImGui::End();
            }
            });

        // ///////////////////////////////////////////////////////////
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }


    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    PanelListener* pl = new PanelListener();
    pl->appPanelMngr = nullptr;
    pl->stat = PANEL_CLOSE;
    threadNoti->emit("PANEL_CLOSE", pl);
    
    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

}

void ApplicationObjectHelperTool::close()
{
    // Rendering
    ImGui::EndFrame();
    
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

void ApplicationObjectHelperTool::onMessageRecieved(PanelListener* pll)
{
    panelForceClose = true;
}

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}






