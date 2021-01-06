// Copyright Epic Games, Inc. All Rights Reserved.

#include "WinDualSense.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "InputCoreTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include "GenericPlatform/GenericApplication.h"
#include <GameFramework/InputSettings.h>
#include <Windows.h>

//#define LOCTEXT_NAMESPACE "InputKeys"
//const FKey EKeys::PS5_Logo("PS5_Logo");
//const FKey EKeys::PS5_Mic("PS5_Mic");
//#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "FWinDualSenseModule"

#pragma region Dual Sense [Plugin]
void FWinDualSensePlugin::StartupModule()
{
	IInputDeviceModule::StartupModule();
	
	//Binding Additional Keys
	EKeys::AddMenuCategoryDisplayInfo("PS5", LOCTEXT("PS5SubCategory", "PS5"), TEXT("GraphEditor.PadEvent_16x"));
	RegisterInputs();

	UE_LOG(LogWinDualSense, Warning, TEXT("StartupModule"));
	FString BaseDir = IPluginManager::Get().FindPlugin("WinDualSense")->GetBaseDir();
	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/WinDualSenseLibrary/Win64/ds5w_x64.dll"));

	WinDualSenseLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!WinDualSenseLibraryHandle)
		return;
	
	DS5W::DeviceEnumInfo infos[16];
	unsigned int controllersCount = 0;
	DS5W_ReturnValue rv = DS5W::enumDevices(infos, 16, &controllersCount);

	// check size
	if (controllersCount == 0) {
		UE_LOG(LogWinDualSense,Error,TEXT("Can't Find Any DualSense Controller!"));
		return;
	}

}

void FWinDualSensePlugin::ShutdownModule()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("ShutdownModule"));
	
	FPlatformProcess::FreeDllHandle(WinDualSenseLibraryHandle);
	WinDualSenseLibraryHandle = nullptr;
}

void FWinDualSensePlugin::AddInput(FString InputName, uint8 keyFlags)
{
	//FName MenuCategory(TEXT("PS5"));
	//FKey Key = FKey(FName(*InputName));

	//EKeys::AddKey(FKeyDetails(Key, InputName, keyFlags, MenuCategory));
}

void FWinDualSensePlugin::RegisterInputs()
{
	/*AddKey(FKeyDetails(EKeys::PS4_Special, LOCTEXT("PS4_Special", "PS4_Special"), FKeyDetails::NotBlueprintBindableKey | FKeyDetails::NotActionBindableKey, "PS4"));
	AddKey(FKeyDetails(EKeys::Gamepad_Special_Left_X, LOCTEXT("PS4_Gamepad_Special_Left_X", "PS4 Touchpad Button X Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, "PS4"));
	AddKey(FKeyDetails(EKeys::Gamepad_Special_Left_Y, LOCTEXT("PS4_Gamepad_Special_Left_Y", "PS4 Touchpad Button Y Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D, "PS4"));*/

	//AddInput(TEXT("PS5 Logo"),FKeyDetails::GamepadKey);
	//AddInput(TEXT("PS5 Mic"),FKeyDetails::GamepadKey);

	//AddInput(TEXT("TouchPad First"), FKeyDetails::Touch);
	//AddInput(TEXT("TouchPad Second"), FKeyDetails::Touch);
}
#pragma endregion
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWinDualSensePlugin, WinDualSense)