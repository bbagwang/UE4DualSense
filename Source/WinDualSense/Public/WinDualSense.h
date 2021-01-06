// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WinDualSensePCH.h"
#include "WinDualSenseDevice.h"
#include "Modules/ModuleManager.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "Misc/ConfigCacheIni.h"
#include "WinDualSenseLibrary/ds5w.h"

#pragma region Dual Sense [Plugin]
class FWinDualSensePlugin : public IInputDeviceModule
{
public:

	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override
	{
		UE_LOG(LogWinDualSense, Log, TEXT("DualSense Input Device Created"));
		return TSharedPtr< class IInputDevice >(new FWinDualSenseDevice(InMessageHandler));
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void AddInput(FString InputName, uint8 keyFlags);
	void RegisterInputs();

private:
	void* WinDualSenseLibraryHandle;

};
#pragma endregion