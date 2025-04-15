#pragma once

#include "StateType.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	NONE = 0,

	IDLE = 1,
	
	FALLING = 4,
	STANDBY = 5,

	DIALOGUE = 6,

	WALK = 10,
	RUN = 11,
};