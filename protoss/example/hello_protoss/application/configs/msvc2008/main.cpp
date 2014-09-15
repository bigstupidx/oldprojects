// main.cpp 
// Main entry and main loop in windows.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include <PActivity>
#include <PContext>
#include <PWin32Window>

#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <dbghelp.h>


extern void pMain(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    int exitCode = EXIT_SUCCESS;

	float f = atof("  -423232.0213f    ");
	printf("%f", f);

    PActivity* activity = pNew(PActivity(argc, argv));
    
        
    // Enable memory leak checks and heap validation. 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(-1);
    
    pMain(argc, argv);

    // Set console title.
    SetConsoleTitle(L"protoss debug console");
    
    // Disable the close button of the console window.
    HWND hConsoleWindow = GetConsoleWindow();
    if (hConsoleWindow != NULL)
    {
        HMENU hMenu = GetSystemMenu(hConsoleWindow, 0);
        if (hMenu != NULL)
        {
            DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
            DrawMenuBar(hConsoleWindow);
        }
    }

    PContext* context = activity->findContext(pUint32(0));
    pAssert(context != P_NULL);
    if (context == P_NULL)
    {
        exitCode = EXIT_FAILURE;
        pDelete(activity);
        return exitCode;
    }

    PWin32Window window(context);

    if (!window.create())
    {
        exitCode = EXIT_FAILURE;
        pDelete(activity);
        return exitCode;
    }
    
    // Initialize the context. 
    // kzaPlatformSetInstanceHandle(context, GetModuleHandle(NULL));
    context->setState(P_CONTEXT_STATE_UNINITIALIZED);
    if (!context->initialize())
    {
        exitCode = EXIT_FAILURE;
    }

    if (!context->onInitialized())
    {
        context->setState(P_CONTEXT_STATE_ERROR);
    }
    else
    {
        pLogDebug("Starting program main loop");
        context->setState(P_CONTEXT_STATE_RUNNING);
    }

    if (context->getState() == P_CONTEXT_STATE_ERROR)
    {
        exitCode = EXIT_FAILURE;
    }

    // The mainloop of window.
    window.run();

    // Right before destroy the context, user might have
    // something to do.
    context->onDestroy();

    context->destroy();
    
    // Destroy native window.
    window.destroy();

    // Destroy the activity
    pDelete(activity);

    // If debugger is present, a pause is required to keep the console output
    // visible. Otherwise the pause is automatic. 
    if (IsDebuggerPresent())
    {
        system("pause");
    }

    return exitCode;
}
