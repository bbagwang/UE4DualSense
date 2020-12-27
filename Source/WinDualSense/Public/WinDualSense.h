// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "Misc/ConfigCacheIni.h"
#include "WinDualSenseLibrary/ds5w.h"

DEFINE_LOG_CATEGORY_STATIC(LogWinDualSense, Log, All);

//USTRUCT(BlueprintType)
//struct FDualSenseInputState
//{
//};

#pragma region Dual Sense [Input Device]
class FWinDualSense : public IInputDevice
{

public:
	FWinDualSense(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
	~FWinDualSense();

	void Tick(float DeltaTime) override;
	void SendControllerEvents() override;
	void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values) override;
	bool SupportsForceFeedback(int32 ControllerId) override;
	void SetLightColor(int32 ControllerId, FColor Color) override;
	void ResetLightColor(int32 ControllerId) override;
	void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;
	class IHapticDevice* GetHapticDevice() override;
	bool IsGamepadAttached() const override;

public:
	DS5W::DeviceContext DualSenseController;
	DS5W::DS5InputState inState;
	DS5W::DS5OutputState outState;
	DS5W::TriggerEffectType rType = DS5W::TriggerEffectType::NoResitance;

	float intensity = 1.0f;
	uint16_t lrmbl = 0.0;
	uint16_t rrmbl = 0.0;

private:
	// handler to send all messages to
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};
#pragma endregion

#pragma region Dual Sense [Plugin]
class FWinDualSensePlugin : public IInputDeviceModule
{
public:

	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override
	{
		UE_LOG(LogWinDualSense, Log, TEXT("DualSense Input Device Created"));
		return TSharedPtr< class IInputDevice >(new FWinDualSense(InMessageHandler));
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void AddInput(FString InputName, FString InputText, uint8 keyFlags, FName MenuCategory, FString UniqueStringIdentifier);
	void RegisterInputs();

private:
	/** Handle to the test dll we will load */
	void* WinDualSenseLibraryHandle;

};
#pragma endregion