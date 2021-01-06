// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDualSenseButtonState : uint8
{
	//NO INPUT
	NONE,
	//ON PRESS BUTTON
	PRESS,
	//WHILE HOLDING THE PRESS BUTTON
	REPEAT,
	//ON RELEASE BUTTON
	RELEASE
};

UENUM(BlueprintType)
enum class EDualSenseButtonType : uint8
{
	TRIANGLE,
	CROSS,
	SQUARE,
	CIRCLE,

	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,

	BUMPER_LEFT,
	BUMPER_RIGHT,

	TRIGGER_LEFT,
	TRIGGER_RIGHT,

	LEFT_STICK_PUSH,
	/*LEFT_STICK_UP,
	LEFT_STICK_DOWN,
	LEFT_STICK_LEFT,
	LEFT_STICK_RIGHT,*/

	RIGHT_STICK_PUSH,
	/*RIGHT_STICK_UP,
	RIGHT_STICK_DOWN,
	RIGHT_STICK_LEFT,
	RIGHT_STICK_RIGHT,*/

	SELECT,
	MENU,
	PLAYSTATION_LOGO,
	TOUCHPAD,
	MIC,

	MAX_COUNT
};

UENUM(BlueprintType)
enum class EDualSenseAnalogType : uint8
{
	LEFT_STICK_X,
	LEFT_STICK_Y,

	RIGHT_STICK_X,
	RIGHT_STICK_Y,

	LEFT_TRIGGER,
	RIGHT_TRIGGER
};

UENUM(BlueprintType)
enum class EDualSenseVectorType : uint8
{
	GYROSCOPE,
	ACCELERATION
};

UENUM(BlueprintType)
enum class EDualSense2DType : uint8
{
	TOUCHPOINT_FIRST,
	TOUCHPOINT_SECOND
};