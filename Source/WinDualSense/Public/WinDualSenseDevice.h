// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WinDualSensePCH.h"
#include "Modules/ModuleManager.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "WinDualSenseLibrary/ds5w.h"

#pragma region Dual Sense [Input Device]
class FWinDualSenseDevice : public IInputDevice
{
public:
	FWinDualSenseDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
	~FWinDualSenseDevice();

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

	FORCEINLINE void UpdateInputs();
	void UpdateButtons();
	void UpdateAnalogs();
	void UpdateVectors();
	
	//DEBUG PRINTING
	void DEBUG_Inputs();

	//TODO
	FORCEINLINE void UpdateOutputs();

	/*void UpdateRumble();
	void UpdateLED();
	void UpdateAdaptiveTrigger();
	void UpdateAdaptiveTriggerEffect();
	void UpdateMicrophone();*/

public:
	DS5W::DeviceEnumInfo infos[16];
	unsigned int controllersCount = 0;
	DS5W::DeviceContext DualSenseController;
	DS5W::DS5InputState inState;
	DS5W::DS5OutputState outState;

	DS5W::TriggerEffectType LeftTriggerEffectType = DS5W::TriggerEffectType::NoResitance;
	DS5W::TriggerEffectType RightTriggerEffectType = DS5W::TriggerEffectType::NoResitance;

	float Intensity_LED = 1.0f;
	
	uint16_t LeftRumble = 0.0;
	uint16_t RightRumble = 0.0;

	int btMul = 0;

	UPROPERTY()
	TMap<EDualSenseButtonType, FDualSenseButtonData> Buttons;

	UPROPERTY()
	TMap<EDualSenseAnalogType, FDualSenseAnalogData> Analogs;

	UPROPERTY()
	TMap<EDualSenseVectorType, FDualSenseVectorData> Vectors;

private:
	// handler to send all messages to
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};
#pragma endregion