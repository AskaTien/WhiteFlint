﻿#include "pch.h"
#include "D3D12HelloWindow.h"

using namespace winrt;
namespace winrt
{
    using namespace Windows::Foundation;
}

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow)
{
    D3D12HelloWindow sample(1280, 800, L"D3D12 Hello Renderer");
    return Win32Application::Run(&sample, hInstance, nCmdShow);
}
