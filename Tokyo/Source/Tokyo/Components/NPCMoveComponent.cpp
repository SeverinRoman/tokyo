#include "NPCMoveComponent.h"

#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"


UNPCMoveComponent::UNPCMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPCMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UNPCMoveComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();

	Character = Cast<ACharacter>(Owner);
	
	if (Character)
	{
		AController* Controller = Character->GetController();

		if (Controller)
		{
			AIController = Cast<AAIController>(Controller);
		}
	}

	if (TargetPoints.Num() != 0)
	{
		if (!IsMove) return;
		
		switch (MoveType)
		{
		case ENPCMoveType::NONE:
			break;
		case ENPCMoveType::LOOP:
			MoveLoop();
			break;
		case ENPCMoveType::RANDOM:
			MoveRandom();
			break;
		case ENPCMoveType::PING_PONG:
			break;
		}
	}
}

void UNPCMoveComponent::MoveLoop()
{
	if (!TargetPoints.IsValidIndex(CurrentTargetPoint)) return;
	if (!TargetPoints[CurrentTargetPoint]) return;

	if (AIController)
	{
		AIController->MoveToLocation(TargetPoints[CurrentTargetPoint]->GetActorLocation());

		AIController->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
		AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UNPCMoveComponent::MoveLoopEnd);
	}

	CurrentTargetPoint += 1;
}

void UNPCMoveComponent::MoveLoopEnd(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (TargetPoints.Num() == CurrentTargetPoint)
	{
		CurrentTargetPoint = 0;
	}
	
	if (!IsDelay)
	{
		MoveLoop();
	}
	else
	{
		if (World)
		{
			World->GetTimerManager().SetTimer(TimerHandleDelay, [this]()
			{
				MoveLoop();
			}, FMath::RandRange(DelayWait.X, DelayWait.Y), false);
		}
	}
}

void UNPCMoveComponent::MoveRandom()
{
	int32 TargetPointIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
	
	if (!TargetPoints.IsValidIndex(TargetPointIndex)) return;
	if (!TargetPoints[TargetPointIndex]) return;

	if (AIController)
	{
		AIController->MoveToLocation(TargetPoints[TargetPointIndex]->GetActorLocation());

		AIController->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
		AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UNPCMoveComponent::MoveRandomEnd);
	}
}

void UNPCMoveComponent::MoveRandomEnd(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (TargetPoints.Num() == CurrentTargetPoint)
	{
		CurrentTargetPoint = 0;
	}

	if (!IsDelay)
	{
		MoveRandom();
	}
	else
	{
		if (World)
		{
			World->GetTimerManager().SetTimer(TimerHandleDelay, [this]()
			{
				MoveRandom();
			}, FMath::RandRange(DelayWait.X, DelayWait.Y), false);
		}
	}
}

