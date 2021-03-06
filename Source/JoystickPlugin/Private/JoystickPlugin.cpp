/*
*
* Copyright (C) <2014> samiljan <Sam Persson>, tsky <thomas.kollakowksy@w-hs.de>
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the BSD license.  See the LICENSE file for details.
*/

#include "JoystickPlugin.h"

#include "Core.h"
#include <Engine.h>

#if WITH_EDITOR
	#include "InputSettingsCustomization.h"
#endif

IMPLEMENT_MODULE(FJoystickPlugin, JoystickPlugin)

#define LOCTEXT_NAMESPACE "JoystickPlugin"


void FJoystickPlugin::StartupModule()
{
	IJoystickPlugin::StartupModule();
	FString sdlDir("Plugins/JoystickPlugin/Source/ThirdParty/SDL2-2.0.10/lib/x64/SDL2.dll");
	FString DllRelativePath = FPaths::ProjectDir() + sdlDir;
	FString DllPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*DllRelativePath);
	void* DLLHandle = FPlatformProcess::GetDllHandle(*DllPath);
	JoystickDevice = MakeShareable(new ::FJoystickDevice());
	//return;

#if WITH_EDITOR
	// Replace parts of the input settings widget to make them wide enough to fit long joystick names
	FInputActionMappingCustomizationExtended::Register();
	FInputAxisMappingCustomizationExtended::Register();
#endif
}

#undef LOCTEXT_NAMESPACE
