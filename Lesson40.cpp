/**************************************************************************

  File: Lesson40.cpp
  
  Based on Jeff Molofee's Basecode Example

  Modified by Erkin Tunca for nehe.gamedev.net

**************************************************************************/

#include <windows.h>														// Header File For Windows
#include "NeHeGL.h"															// Header File For NeHeGL

#include "..\View73\Graphics\View73GlInclude.h"
#include "..\View73\View73ApplicationRoot.h"
#include "..\Game\GameApplication.h"

#ifndef CDS_FULLSCREEN														// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4													// Compilers. By Defining It This Way,
#endif																		// We Can Avoid Errors

GL_Window*	g_window;
Keys*		g_keys;

using namespace Game;

BOOL Initialize (GL_Window* window, Keys* keys)								// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;
	g_keys		= keys;

	
	View73::ApplicationRoot::CreateInstance();
	View73::TApplicationAutoPtr app;
	GameApplication* newApp = new GameApplication((float)window->init.width,(float)window->init.height);
	newApp->InitializeGame(keys);
	app.reset(newApp);
	View73::gAppRoot->SetApplicationPtr(app);


	return TRUE;															// Return TRUE (Initialization Successful)
}

void Deinitialize (void)													// Any User DeInitialization Goes Here
{
	View73::ApplicationRoot::DestroyInstance();
}	

void Update (DWORD milliseconds)											// Perform Motion Updates Here
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)
	{
	}

	//if (g_keys->keyDown [VK_ESCAPE] == TRUE)								// Is ESC Being Pressed?
	//	TerminateApplication (g_window);									// Terminate The Program

	//if (g_keys->keyDown [VK_F1] == TRUE)									// Is F1 Being Pressed?
	//	ToggleFullscreen (g_window);										// Toggle Fullscreen Mode										// Create A Temporary Vector3D

	// Keys Are Used To Move The Rope
	//if (g_keys->keyDown [VK_RIGHT] == TRUE)									// Is The Right Arrow Being Pressed?
	//	ropeConnectionVel.x += 3.0f;										// Add Velocity In +X Direction

	//if (g_keys->keyDown [VK_LEFT] == TRUE)									// Is The Left Arrow Being Pressed?
	//	ropeConnectionVel.x -= 3.0f;										// Add Velocity In -X Direction

	//if (g_keys->keyDown [VK_UP] == TRUE)									// Is The Up Arrow Being Pressed?
	//	ropeConnectionVel.z -= 3.0f;										// Add Velocity In +Z Direction

	//if (g_keys->keyDown [VK_DOWN] == TRUE)									// Is The Down Arrow Being Pressed?
	//	ropeConnectionVel.z += 3.0f;										// Add Velocity In -Z Direction

	//if (g_keys->keyDown [VK_HOME] == TRUE)									// Is The Home Key Pressed?
	//	ropeConnectionVel.y += 3.0f;										// Add Velocity In +Y Direction

//	if (g_keys->keyDown [VK_END] == TRUE)									// Is The End Key Pressed?
//		ropeConnectionVel.y -= 3.0f;										// Add Velocity In -Y Direction
}

void Draw (void)
{
	View73::gAppRoot->Update();
	
	//g_BTest->Render();
	
	glFlush ();																// Flush The GL Rendering Pipeline
}
