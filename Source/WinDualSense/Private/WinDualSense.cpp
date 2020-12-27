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

#define LOCTEXT_NAMESPACE "FWinDualSenseModule"

#pragma region Dual Sense [Input Device]
FWinDualSense::FWinDualSense(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) : MessageHandler(InMessageHandler)
{

	DS5W::DeviceEnumInfo infos[16];
	unsigned int controllersCount = 0;
	DS5W_ReturnValue rv = DS5W::enumDevices(infos, 16, &controllersCount);

	UE_LOG(LogWinDualSense, Warning, TEXT("FWinDualSense"));
	
	// check size
	if (controllersCount == 0) {
		UE_LOG(LogWinDualSense, Error, TEXT("Can't Find Any DualSense Controller!"));
		return;
	}

	for (unsigned int i = 0; i < controllersCount; i++) {
		if (infos[i]._internal.connection == DS5W::DeviceConnection::BT) {
			UE_LOG(LogWinDualSense, Log, TEXT("Dual Sense #%d Connected : Bluetooth"));
		}
		else {
			UE_LOG(LogWinDualSense, Log, TEXT("Dual Sense #%d Connected : USB"));
		}
	}

	// Create first controller
	if (DS5W_SUCCESS(DS5W::initDeviceContext(&infos[0], &DualSenseController)))
	{
		UE_LOG(LogWinDualSense, Warning, TEXT("Dual Sense Controller Connected!!!"));

		ZeroMemory(&inState, sizeof(DS5W::DS5InputState));
		ZeroMemory(&outState, sizeof(DS5W::DS5OutputState));

		// Force
		rType = DS5W::TriggerEffectType::NoResitance;
		int btMul = DualSenseController._internal.connection == DS5W::DeviceConnection::BT ? 10 : 1;
	}
}

FWinDualSense::~FWinDualSense()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("~FWinDualSense"));
}

void FWinDualSense::Tick(float DeltaTime)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("Tick"));
}

void FWinDualSense::SendControllerEvents()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SendControllerEvent"));

	// Get input state
	if (DS5W_SUCCESS(DS5W::getDeviceInputState(&DualSenseController, &inState))) {
		
		//Left Stick
		UE_LOG(LogWinDualSense, Warning, TEXT("Left Stick [X : %d] | [Y : %d] | %s"),(int)inState.leftStick.x, (int)inState.leftStick.y,(inState.buttonsA&DS5W_ISTATE_BTN_A_LEFT_STICK)?TEXT("[PUSHED!]"):TEXT(""));
		//Right Stick
		UE_LOG(LogWinDualSense, Warning, TEXT("Right Stick [X : %d] | [Y : %d] | %s"),(int)inState.rightStick.x, (int)inState.rightStick.y,(inState.buttonsA&DS5W_ISTATE_BTN_A_RIGHT_STICK)?TEXT("[PUSHED!]"):TEXT(""));

		//Left Trigger
		UE_LOG(LogWinDualSense, Warning, TEXT("Left Trigger [Weight : %d] | %s"), (int)inState.leftTrigger, (inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_TRIGGER) ? TEXT("[TRIGGERED!]") : TEXT(""));
		//Right Trigger
		UE_LOG(LogWinDualSense, Warning, TEXT("Right Trigger [Weight : %d] | %s"), (int)inState.rightTrigger, (inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_TRIGGER) ? TEXT("[TRIGGERED!]") : TEXT(""));

		//Left Bumper
		UE_LOG(LogWinDualSense, Warning, TEXT("Left Bumper | %s"), (inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_BUMPER) ? TEXT("[PUSHED!]") : TEXT(""));
		//Right Bumper
		UE_LOG(LogWinDualSense, Warning, TEXT("Right Bumper | %s"), (inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_BUMPER) ? TEXT("[PUSHED!]") : TEXT(""));

		//DPAD
		UE_LOG(LogWinDualSense, Warning, TEXT("DPAD | UP [%s] | DOWN [%s] | LEFT [%s] | RIGHT | [%s]"),
			(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_UP) ? TEXT("O") : TEXT("X"), (inState.buttonsAndDpad & DS5W_ISTATE_DPAD_DOWN) ? TEXT("O") : TEXT("X"),
			(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_LEFT) ? TEXT("O") : TEXT("X"), (inState.buttonsAndDpad & DS5W_ISTATE_DPAD_RIGHT) ? TEXT("O") : TEXT("X"));
		
		//PS Primitive Buttons
		UE_LOG(LogWinDualSense, Warning, TEXT("Primitive Buttons | TRIANGLE [%s] | CROSS [%s] | SQUARE [%s] | CIRCLE | [%s]"),
			(inState.buttonsAndDpad & DS5W_ISTATE_BTX_TRIANGLE) ? TEXT("O") : TEXT("X"), (inState.buttonsAndDpad & DS5W_ISTATE_BTX_CROSS) ? TEXT("O") : TEXT("X"),
			(inState.buttonsAndDpad & DS5W_ISTATE_BTX_SQUARE) ? TEXT("O") : TEXT("X"), (inState.buttonsAndDpad & DS5W_ISTATE_BTX_CIRCLE) ? TEXT("O") : TEXT("X"));
		
		//Menu Button
		UE_LOG(LogWinDualSense, Warning, TEXT("Menu Button | %s"), (inState.buttonsA & DS5W_ISTATE_BTN_A_MENU) ? TEXT("[PUSHED!]") : TEXT(""));
		//Select Button
		UE_LOG(LogWinDualSense, Warning, TEXT("Select Button | %s"), (inState.buttonsA & DS5W_ISTATE_BTN_A_SELECT) ? TEXT("[PUSHED!]") : TEXT(""));

		//Trigger Feedback
		UE_LOG(LogWinDualSense, Warning, TEXT("Trigger Feedback | Left [Weight : %d] | Right [Weight : %d]"), (int)inState.leftTriggerFeedback, (int)inState.rightTriggerFeedback);
		
		//TouchPad Button
		UE_LOG(LogWinDualSense, Warning, TEXT("TouchPad Button | [%s]"), (inState.buttonsB & DS5W_ISTATE_BTN_B_PAD_BUTTON)?TEXT("[PUSHED!]"):TEXT(""));

		//Left TouchPad Finger
		UE_LOG(LogWinDualSense, Warning, TEXT("Finger Left | [X : %d] | [Y : %d]"), inState.touchPoint1.x,inState.touchPoint1.y);
		//Right TouchPad Finger
		UE_LOG(LogWinDualSense, Warning, TEXT("Finger Right | [X : %d] | [Y : %d]"), inState.touchPoint2.x, inState.touchPoint2.y);

		//Battery
		UE_LOG(LogWinDualSense, Warning, TEXT("Battery | [LEVEL : %d] | %s | %s"), inState.battery.level,
		inState.battery.chargin?TEXT("[CHARGING]"):TEXT(""),
		inState.battery.fullyCharged ? TEXT("[FULLY CHARGED]") : TEXT(""));

		//Playstation Button
		UE_LOG(LogWinDualSense, Warning, TEXT("Play Station Button : %s"), (inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO) ? TEXT("[PUSHED!]") : TEXT(""));
		
		//Mic Button
		UE_LOG(LogWinDualSense, Warning, TEXT("Mic Button : %s"), (inState.buttonsB & DS5W_ISTATE_BTN_B_MIC_BUTTON) ? TEXT("[PUSHED!]") : TEXT(""));

		//Bluetooth Multifly
		int btMul = DualSenseController._internal.connection == DS5W::DeviceConnection::BT ? 10 : 1;
		// Rumbel
		lrmbl = max(lrmbl - 0x200 / btMul, 0);
		rrmbl = max(rrmbl - 0x100 / btMul, 0);

		outState.leftRumble = (lrmbl & 0xFF00) >> 8UL;
		outState.rightRumble = (rrmbl & 0xFF00) >> 8UL;

		//Light Bar
		/*outState.lightbar = DS5W::color_R8G8B8_UCHAR_A32_FLOAT(255, 0, 0, intensity);
		intensity -= 0.0025f / btMul;*/
		if (intensity <= 0.0f) {
			intensity = 1.0f;

			lrmbl = 0xFF00;
			rrmbl = 0xFF00;
		}

		//Player LED
		if (outState.rightRumble) {
			outState.playerLeds.playerLedFade = true;
			outState.playerLeds.bitmask = DS5W_OSTATE_PLAYER_LED_MIDDLE;
			outState.playerLeds.brightness = DS5W::LedBrightness::HIGH;
		}
		else {
			outState.playerLeds.bitmask = 0;
		}

		//Set Adaptive Trigger Force
		if (inState.rightTrigger == 0xFF) {
			rType = DS5W::TriggerEffectType::ContinuousResitance;
		}
		else if (inState.rightTrigger == 0x00) {
			rType = DS5W::TriggerEffectType::NoResitance;
		}

		// Mic led
		if (inState.buttonsB & DS5W_ISTATE_BTN_B_MIC_BUTTON) {
			outState.microphoneLed = DS5W::MicLed::ON;
		}
		else if (inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO) {
			outState.microphoneLed = DS5W::MicLed::OFF;
		}

		//Left Trigger Clicky And Section
		outState.leftTriggerEffect.effectType = DS5W::TriggerEffectType::SectionResitance;
		outState.leftTriggerEffect.Section.startPosition = 0x00;
		outState.leftTriggerEffect.Section.endPosition = 0x60;

		//Right Trigger Forcy
		outState.rightTriggerEffect.effectType = rType;
		outState.rightTriggerEffect.Continuous.force = 0xFF;
		outState.rightTriggerEffect.Continuous.startPosition = 0x00;

		DS5W::setDeviceOutputState(&DualSenseController, &outState);
	}
	else {
		// Device disconnected show error and try to reconnect
		UE_LOG(LogWinDualSense, Error, TEXT("DEVICE REMOVED or NOT DETECTED!"));
		DS5W::reconnectDevice(&DualSenseController);
	}
}

void FWinDualSense::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SetMessageHandler"));
	MessageHandler=InMessageHandler;
}

bool FWinDualSense::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("Exec"));
	return true;
}

void FWinDualSense::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SetChannelValue"));
}

void FWinDualSense::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SetChannelValues"));
}

bool FWinDualSense::SupportsForceFeedback(int32 ControllerId)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SupportsForceFeedback"));
	return true;
}

void FWinDualSense::SetLightColor(int32 ControllerId, FColor Color)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SetLightColor"));
}

void FWinDualSense::ResetLightColor(int32 ControllerId)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("ResetLightColor"));
}

void FWinDualSense::SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("SetDeviceProperty"));
}

class IHapticDevice* FWinDualSense::GetHapticDevice()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("GetHapticDevice"));
	return nullptr;
}

bool FWinDualSense::IsGamepadAttached() const
{
	UE_LOG(LogWinDualSense, Warning, TEXT("IsGamepadAttached"));
	return true;
}

#pragma endregion

#pragma region Dual Sense [Plugin]
void FWinDualSensePlugin::StartupModule()
{
	IInputDeviceModule::StartupModule();
	UE_LOG(LogWinDualSense, Warning, TEXT("StartupModule"));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("WinDualSense")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/WinDualSenseLibrary/Win64/ds5w_x64.dll"));

	WinDualSenseLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!WinDualSenseLibraryHandle)
	{
		return;
	}
	
	// Call the test function in the third party library that opens a message box
	//ExampleLibraryFunction();

	DS5W::DeviceEnumInfo infos[16];
	unsigned int controllersCount = 0;
	DS5W_ReturnValue rv = DS5W::enumDevices(infos, 16, &controllersCount);

	// check size
	if (controllersCount == 0) {
		UE_LOG(LogWinDualSense,Error,TEXT("Can't Find Any DualSense Controller!"));
		return;
	}

	/*const UInputSettings* InputSettings = GetDefault<UInputSettings>();
	if (InputSettings != nullptr)
	{
		TArray<FName> ActionNames;
		InputSettings->GetActionNames(ActionNames);
		for (const FName ActionName : ActionNames)
		{
		UE_LOG(LogWinDualSense,Warning,TEXT("%s"),ActionName);
		}
	}*/
}

void FWinDualSensePlugin::ShutdownModule()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("ShutdownModule"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(WinDualSenseLibraryHandle);
	WinDualSenseLibraryHandle = nullptr;
}

void FWinDualSensePlugin::AddInput(FString InputName, FString InputText, uint8 keyFlags, FName MenuCategory, FString UniqueStringIdentifier)
{
	FKey Key = FKey(FName(*InputName));

	FFormatNamedArguments arguments;
	FText a = FText::FromName(FName(*InputName));
	FText b = FText::FromName(FName(*InputText));
	arguments.Add(TEXT("item"), a);
	arguments.Add(TEXT("target"), b);
	EKeys::AddKey(FKeyDetails(Key, FText::Format(LOCTEXT("{item}", "{target}"), arguments), keyFlags, MenuCategory));
}

void FWinDualSensePlugin::RegisterInputs()
{

}

#pragma endregion
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWinDualSensePlugin, WinDualSense)