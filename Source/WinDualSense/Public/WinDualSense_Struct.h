// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WinDualSense_Enum.h"
#include "WinDualSense_Struct.generated.h"

USTRUCT(BlueprintType)
struct FDualSenseButtonData
{
	GENERATED_BODY()

		FDualSenseButtonData()
	{
		ButtonState = EDualSenseButtonState::NONE;
		bIsPressed = false;
	}

	FDualSenseButtonData(FKey _Key)
	{
		Key = _Key;
		ButtonState = EDualSenseButtonState::NONE;
		bIsPressed = false;
	}

	void UpdateButtonState(bool _bIsPressed)
	{
		bIsPressed = _bIsPressed;

		if (bIsPressed)
		{
			switch (ButtonState)
			{
			case EDualSenseButtonState::NONE:
			case EDualSenseButtonState::RELEASE:
			{
				ButtonState = EDualSenseButtonState::PRESS;
			}
			break;
			case EDualSenseButtonState::PRESS:
			{
				ButtonState = EDualSenseButtonState::REPEAT;
			}
			break;
			case EDualSenseButtonState::REPEAT:
				break;
			default:
				break;
			}
		}
		else
		{
			switch (ButtonState)
			{
			case EDualSenseButtonState::PRESS:
			case EDualSenseButtonState::REPEAT:
			{
				ButtonState = EDualSenseButtonState::RELEASE;
			}
			break;
			case EDualSenseButtonState::RELEASE:
			{
				ButtonState = EDualSenseButtonState::NONE;
			}
			break;
			default:
				break;
			}
		}
	}

	FKey Key;
	EDualSenseButtonState ButtonState;
	bool bIsPressed;
};

USTRUCT(BlueprintType)
struct FDualSenseAnalogData
{
	GENERATED_BODY()

		FDualSenseAnalogData()
	{
		Ratio = 0.f;
		DeadZoneRatio = 0.25f;
	}

	FDualSenseAnalogData(FKey _Key)
	{
		Key = _Key;
		Ratio = 0.f;
		DeadZoneRatio = 0.25f;
	}

	FORCEINLINE void UpdateAnalogState(float _Weight)
	{
		//Check Something
		if (FMath::IsWithinInclusive(_Weight, -DeadZoneRatio, DeadZoneRatio))
		{
			Ratio = 0.f;
		}
		else
		{
			Ratio = _Weight;
		}
	}

	FORCEINLINE void UpdateDeadZoneRatio(float _DeadZoneRatio)
	{
		DeadZoneRatio = _DeadZoneRatio;
	}

	FKey Key;
	float Ratio;
	float DeadZoneRatio;
};

USTRUCT(BlueprintType)
struct FDualSenseVectorData
{
	GENERATED_BODY()

		FDualSenseVectorData()
	{
		Vector = FVector::ZeroVector;
	}

	FDualSenseVectorData(FKey _Key)
	{
		Key = _Key;
		Vector = FVector::ZeroVector;
	}

	void UpdateVectorState(FVector _Vector)
	{
		//Check Something
		Vector = _Vector;
	}

	FKey Key;
	FVector Vector;
};