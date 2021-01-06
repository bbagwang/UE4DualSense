// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WinDualSenseDevice.h"
#include <Kismet/KismetMathLibrary.h>

#pragma region Dual Sense [Input Device]
FWinDualSenseDevice::FWinDualSenseDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) : MessageHandler(InMessageHandler)
{
	//////////////////////////////////////////////////////////////////////////
	// Buttons
	//////////////////////////////////////////////////////////////////////////
	Buttons.Add(EDualSenseButtonType::TRIANGLE, FDualSenseButtonData(FGamepadKeyNames::FaceButtonTop));
	Buttons.Add(EDualSenseButtonType::CROSS, FDualSenseButtonData(FGamepadKeyNames::FaceButtonBottom));
	Buttons.Add(EDualSenseButtonType::SQUARE, FDualSenseButtonData(FGamepadKeyNames::FaceButtonLeft));
	Buttons.Add(EDualSenseButtonType::CIRCLE, FDualSenseButtonData(FGamepadKeyNames::FaceButtonRight));

	Buttons.Add(EDualSenseButtonType::DPAD_UP, FDualSenseButtonData(FGamepadKeyNames::DPadUp));
	Buttons.Add(EDualSenseButtonType::DPAD_DOWN, FDualSenseButtonData(FGamepadKeyNames::DPadDown));
	Buttons.Add(EDualSenseButtonType::DPAD_LEFT, FDualSenseButtonData(FGamepadKeyNames::DPadLeft));
	Buttons.Add(EDualSenseButtonType::DPAD_RIGHT, FDualSenseButtonData(FGamepadKeyNames::DPadRight));

	Buttons.Add(EDualSenseButtonType::BUMPER_LEFT, FDualSenseButtonData(FGamepadKeyNames::LeftShoulder));
	Buttons.Add(EDualSenseButtonType::BUMPER_RIGHT, FDualSenseButtonData(FGamepadKeyNames::RightShoulder));

	Buttons.Add(EDualSenseButtonType::TRIGGER_LEFT, FDualSenseButtonData(FGamepadKeyNames::LeftTriggerThreshold));
	Buttons.Add(EDualSenseButtonType::TRIGGER_RIGHT, FDualSenseButtonData(FGamepadKeyNames::RightTriggerThreshold));

	Buttons.Add(EDualSenseButtonType::LEFT_STICK_PUSH, FDualSenseButtonData(FGamepadKeyNames::LeftThumb));
	Buttons.Add(EDualSenseButtonType::RIGHT_STICK_PUSH, FDualSenseButtonData(FGamepadKeyNames::RightThumb));

	Buttons.Add(EDualSenseButtonType::SELECT, FDualSenseButtonData(FGamepadKeyNames::SpecialLeft));
	Buttons.Add(EDualSenseButtonType::MENU, FDualSenseButtonData(FGamepadKeyNames::SpecialRight));
	Buttons.Add(EDualSenseButtonType::PLAYSTATION_LOGO, FDualSenseButtonData(EKeys::PS4_Special));

	//TODO : Add More Buttons
	//Buttons.Add(EDualSenseButtonType::TOUCHPAD, FDualSenseButtonData();
	//Buttons.Add(EDualSenseButtonType::MIC, FDualSenseButtonData();

	//////////////////////////////////////////////////////////////////////////
	// Analogs
	//////////////////////////////////////////////////////////////////////////
	Analogs.Add(EDualSenseAnalogType::LEFT_STICK_X, FDualSenseAnalogData(FGamepadKeyNames::LeftAnalogX));
	Analogs.Add(EDualSenseAnalogType::LEFT_STICK_Y, FDualSenseAnalogData(FGamepadKeyNames::LeftAnalogY));
	Analogs.Add(EDualSenseAnalogType::RIGHT_STICK_X, FDualSenseAnalogData(FGamepadKeyNames::RightAnalogX));
	Analogs.Add(EDualSenseAnalogType::RIGHT_STICK_Y, FDualSenseAnalogData(FGamepadKeyNames::RightAnalogY));
	Analogs.Add(EDualSenseAnalogType::LEFT_TRIGGER, FDualSenseAnalogData(FGamepadKeyNames::LeftTriggerAnalog));
	Analogs.Add(EDualSenseAnalogType::RIGHT_TRIGGER, FDualSenseAnalogData(FGamepadKeyNames::RightTriggerAnalog));

	//////////////////////////////////////////////////////////////////////////
	// Vectors
	//////////////////////////////////////////////////////////////////////////
	Vectors.Add(EDualSenseVectorType::GYROSCOPE, FDualSenseVectorData(EKeys::Tilt));
	Vectors.Add(EDualSenseVectorType::ACCELERATION, FDualSenseVectorData(EKeys::Acceleration));

	//Initialize In/Out State Buffer
	ZeroMemory(&inState, sizeof(DS5W::DS5InputState));
	ZeroMemory(&outState, sizeof(DS5W::DS5OutputState));
}

FWinDualSenseDevice::~FWinDualSenseDevice()
{
	UE_LOG(LogWinDualSense, Warning, TEXT("~FWinDualSense"));
}

void FWinDualSenseDevice::Tick(float DeltaTime)
{

}

void FWinDualSenseDevice::SendControllerEvents()
{
	// Get input state
	if (DS5W_SUCCESS(DS5W::getDeviceInputState(&DualSenseController, &inState))) {
		UpdateInputs();
		UpdateOutputs();
	}
	else {
		DS5W::enumDevices(infos, 16, &controllersCount);
		DS5W::initDeviceContext(&infos[0], &DualSenseController);
		DS5W::reconnectDevice(&DualSenseController);
	}
}

void FWinDualSenseDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SetMessageHandler"));
	MessageHandler = InMessageHandler;
}

bool FWinDualSenseDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	UE_LOG(LogWinDualSense, Warning, TEXT("Exec"));
	return true;
}

void FWinDualSenseDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SetChannelValue"));
}

void FWinDualSenseDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SetChannelValues"));
}

bool FWinDualSenseDevice::SupportsForceFeedback(int32 ControllerId)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SupportsForceFeedback"));
	return true;
}

void FWinDualSenseDevice::SetLightColor(int32 ControllerId, FColor Color)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SetLightColor"));
}

void FWinDualSenseDevice::ResetLightColor(int32 ControllerId)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("ResetLightColor"));
}

void FWinDualSenseDevice::SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property)
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("SetDeviceProperty"));
}

class IHapticDevice* FWinDualSenseDevice::GetHapticDevice()
{
	//UE_LOG(LogWinDualSense, Warning, TEXT("GetHapticDevice"));
	return nullptr;
}

bool FWinDualSenseDevice::IsGamepadAttached() const
{
	return true;
}

void FWinDualSenseDevice::UpdateInputs()
{
	UpdateButtons();
	UpdateAnalogs();
	UpdateVectors();
	//DEBUG_Inputs();
}

void FWinDualSenseDevice::UpdateButtons()
{
	for (TPair<EDualSenseButtonType, FDualSenseButtonData>& ButtonIterator : Buttons)
	{
		FDualSenseButtonData& ButtonData = ButtonIterator.Value;

		switch (ButtonIterator.Key)
		{
		case EDualSenseButtonType::TRIANGLE:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_BTX_TRIANGLE);
			break;
		case EDualSenseButtonType::CROSS:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_BTX_CROSS);
			break;
		case EDualSenseButtonType::SQUARE:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_BTX_SQUARE);
			break;
		case EDualSenseButtonType::CIRCLE:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_BTX_CIRCLE);
			break;
		case EDualSenseButtonType::DPAD_UP:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_UP);
			break;
		case EDualSenseButtonType::DPAD_DOWN:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_DOWN);
			break;
		case EDualSenseButtonType::DPAD_LEFT:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_LEFT);
			break;
		case EDualSenseButtonType::DPAD_RIGHT:
			ButtonData.UpdateButtonState(inState.buttonsAndDpad & DS5W_ISTATE_DPAD_RIGHT);
			break;
		case EDualSenseButtonType::BUMPER_LEFT:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_BUMPER);
			break;
		case EDualSenseButtonType::BUMPER_RIGHT:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_BUMPER);
			break;
		case EDualSenseButtonType::TRIGGER_LEFT:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_TRIGGER);
			break;
		case EDualSenseButtonType::TRIGGER_RIGHT:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_TRIGGER);
			break;
		case EDualSenseButtonType::LEFT_STICK_PUSH:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_STICK);
			break;
		case EDualSenseButtonType::RIGHT_STICK_PUSH:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_STICK);
			break;
		case EDualSenseButtonType::SELECT:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_SELECT);
			break;
		case EDualSenseButtonType::MENU:
			ButtonData.UpdateButtonState(inState.buttonsA & DS5W_ISTATE_BTN_A_MENU);
			break;
		case EDualSenseButtonType::PLAYSTATION_LOGO:
			ButtonData.UpdateButtonState(inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO);
			break;
		case EDualSenseButtonType::TOUCHPAD:
			ButtonData.UpdateButtonState(inState.buttonsB & DS5W_ISTATE_BTN_B_PAD_BUTTON);
			break;
		case EDualSenseButtonType::MIC:
			ButtonData.UpdateButtonState(inState.buttonsB & DS5W_ISTATE_BTN_B_MIC_BUTTON);
			break;

		case EDualSenseButtonType::MAX_COUNT:
		default:
			break;
		}

		switch (ButtonData.ButtonState)
		{
		case EDualSenseButtonState::PRESS:
			MessageHandler->OnControllerButtonPressed(ButtonData.Key.GetFName(), 0, false);
			break;
		case EDualSenseButtonState::REPEAT:
			MessageHandler->OnControllerButtonPressed(ButtonData.Key.GetFName(), 0, true);
			break;
		case EDualSenseButtonState::RELEASE:
			MessageHandler->OnControllerButtonReleased(ButtonData.Key.GetFName(), 0, false);
			break;

		case EDualSenseButtonState::NONE:
		default:
			break;
		}
	}
}

void FWinDualSenseDevice::UpdateAnalogs()
{
	for (TPair<EDualSenseAnalogType, FDualSenseAnalogData>& AnalogIterator : Analogs)
	{
		FDualSenseAnalogData& AnalogData = AnalogIterator.Value;

		switch (AnalogIterator.Key)
		{
		case EDualSenseAnalogType::LEFT_STICK_X:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.leftStick.x), -128.f, 127.f, -1.f, 1.f));
			break;
		case EDualSenseAnalogType::LEFT_STICK_Y:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.leftStick.y), -128.f, 127.f, -1.f, 1.f));
			break;
		case EDualSenseAnalogType::RIGHT_STICK_X:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.rightStick.x), -128.f, 127.f, -1.f, 1.f));
			break;
		case EDualSenseAnalogType::RIGHT_STICK_Y:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.rightStick.y), -128.f, 127.f, -1.f, 1.f));
			break;
		case EDualSenseAnalogType::LEFT_TRIGGER:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.leftTrigger), 0.f, 255.f, 0.f, 1.f));
			break;
		case EDualSenseAnalogType::RIGHT_TRIGGER:
			AnalogData.UpdateAnalogState(UKismetMathLibrary::MapRangeClamped(static_cast<float>((int)inState.rightTrigger), 0.f, 255.f, 0.f, 1.f));
			break;
		default:
			break;
		}

		MessageHandler->OnControllerAnalog(AnalogData.Key.GetFName(), 0, AnalogData.Ratio);
	}
}

void FWinDualSenseDevice::UpdateVectors()
{
	for (TPair<EDualSenseVectorType, FDualSenseVectorData>& VectorIterator : Vectors)
	{
		FDualSenseVectorData& VectorData = VectorIterator.Value;

		switch (VectorIterator.Key)
		{
		case EDualSenseVectorType::GYROSCOPE:
			VectorData.UpdateVectorState(FVector(inState.gyroscope.x, inState.gyroscope.y, inState.gyroscope.z));
			break;
		case EDualSenseVectorType::ACCELERATION:
			VectorData.UpdateVectorState(FVector(inState.accelerometer.x, inState.accelerometer.y, inState.accelerometer.z));
			break;
		default:
			break;
		}

		//MessageHandler->OnControllerAnalog(VectorData.Key.GetFName(), 0, AnalogData.Ratio);
	}
}

void FWinDualSenseDevice::DEBUG_Inputs()
{
	//Left Stick Update
	UE_LOG(LogWinDualSense, Warning, TEXT("Left Stick [X : %d] | [Y : %d] | %s"), (int)inState.leftStick.x, (int)inState.leftStick.y, (inState.buttonsA & DS5W_ISTATE_BTN_A_LEFT_STICK) ? TEXT("[PUSHED!]") : TEXT(""));
	//Right Stick Update
	UE_LOG(LogWinDualSense, Warning, TEXT("Right Stick [X : %d] | [Y : %d] | %s"), (int)inState.rightStick.x, (int)inState.rightStick.y, (inState.buttonsA & DS5W_ISTATE_BTN_A_RIGHT_STICK) ? TEXT("[PUSHED!]") : TEXT(""));

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
	UE_LOG(LogWinDualSense, Warning, TEXT("TouchPad Button | [%s]"), (inState.buttonsB & DS5W_ISTATE_BTN_B_PAD_BUTTON) ? TEXT("[PUSHED!]") : TEXT(""));

	//Left TouchPad Finger
	UE_LOG(LogWinDualSense, Warning, TEXT("Finger Left | [X : %d] | [Y : %d]"), inState.touchPoint1.x, inState.touchPoint1.y);
	//Right TouchPad Finger
	UE_LOG(LogWinDualSense, Warning, TEXT("Finger Right | [X : %d] | [Y : %d]"), inState.touchPoint2.x, inState.touchPoint2.y);

	//Battery
	UE_LOG(LogWinDualSense, Warning, TEXT("Battery | [LEVEL : %d] | %s | %s"), inState.battery.level,
		inState.battery.chargin ? TEXT("[CHARGING]") : TEXT(""),
		inState.battery.fullyCharged ? TEXT("[FULLY CHARGED]") : TEXT(""));

	//Playstation Button
	UE_LOG(LogWinDualSense, Warning, TEXT("Play Station Button : %s"), (inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO) ? TEXT("[PUSHED!]") : TEXT(""));

	//Mic Button
	UE_LOG(LogWinDualSense, Warning, TEXT("Mic Button : %s"), (inState.buttonsB & DS5W_ISTATE_BTN_B_MIC_BUTTON) ? TEXT("[PUSHED!]") : TEXT(""));

	//GyroScope
	UE_LOG(LogWinDualSense, Warning, TEXT("GyroScope : [X : %hd] | [Y : %hd] | [Z : %hd]"), inState.gyroscope.x, inState.gyroscope.y, inState.gyroscope.z);

	//Acceleration
	UE_LOG(LogWinDualSense, Warning, TEXT("Acceleration : [X : %hd] | [Y : %hd] | [Z : %hd]"), inState.accelerometer.x, inState.accelerometer.y, inState.accelerometer.z);

}

FORCEINLINE void FWinDualSenseDevice::UpdateOutputs()
{
	//Bluetooth Multifly
	btMul = DualSenseController._internal.connection == DS5W::DeviceConnection::BT ? 10 : 1;

	//Rumble
	LeftRumble = max(LeftRumble - 0x200 / btMul, 0);
	RightRumble = max(RightRumble - 0x100 / btMul, 0);

	outState.leftRumble = (LeftRumble & 0xFF00) >> 8UL;
	outState.rightRumble = (RightRumble & 0xFF00) >> 8UL;

	//Light Bar
	/*outState.lightbar = DS5W::color_R8G8B8_UCHAR_A32_FLOAT(255, 0, 0, intensity);
	intensity -= 0.0025f / btMul;*/
	if (Intensity_LED <= 0.0f) {
		Intensity_LED = 1.0f;

		LeftRumble = 0xFF00;
		RightRumble = 0xFF00;
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

	//Set Left Adaptive Trigger Force
	if (inState.leftTrigger == 0xFF) {
		LeftTriggerEffectType = DS5W::TriggerEffectType::ContinuousResitance;
	}
	else if (inState.leftTrigger == 0x00) {
		LeftTriggerEffectType = DS5W::TriggerEffectType::NoResitance;
	}

	//Set Right Adaptive Trigger Force
	if (inState.rightTrigger == 0xFF) {
		RightTriggerEffectType = DS5W::TriggerEffectType::ContinuousResitance;
	}
	else if (inState.rightTrigger == 0x00) {
		RightTriggerEffectType = DS5W::TriggerEffectType::NoResitance;
	}

	// Mic led
	if (inState.buttonsB & DS5W_ISTATE_BTN_B_MIC_BUTTON) {
		outState.microphoneLed = DS5W::MicLed::ON;
	}
	else if (inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO) {
		outState.microphoneLed = DS5W::MicLed::OFF;
	}

	outState.leftTriggerEffect.effectType = LeftTriggerEffectType;
	outState.leftTriggerEffect.Section.startPosition = 0x00;
	outState.leftTriggerEffect.Section.endPosition = 0x60;

	outState.rightTriggerEffect.effectType = RightTriggerEffectType;
	outState.rightTriggerEffect.Continuous.force = 0xFF;
	outState.rightTriggerEffect.Continuous.startPosition = 0x00;

	DS5W::setDeviceOutputState(&DualSenseController, &outState);
}

#pragma endregion