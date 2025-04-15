#pragma once

#include "AnimationType.generated.h"

UENUM(BlueprintType)
enum class EAnimationType : uint8
{
	NONE = 0,

	JUMP = 1,
	DODGE = 2,
};