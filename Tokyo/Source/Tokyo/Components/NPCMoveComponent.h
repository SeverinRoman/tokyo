#pragma once

// #include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCMoveComponent.generated.h"


class ATargetPoint;
class AAIController;


namespace EPathFollowingResult { enum Type : int; }


struct FPathFollowingResult;


UENUM(BlueprintType)
enum class ENPCMoveType : uint8
{
	NONE = 0,

	LOOP = 1,
	RANDOM = 2,
	PING_PONG = 3,
};


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UNPCMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNPCMoveComponent();
	
public:	
	UPROPERTY(EditInstanceOnly)
	TArray<ATargetPoint*> TargetPoints;

	UPROPERTY(EditAnywhere)
	bool IsDelay = true;

	UPROPERTY(EditAnywhere, meta= (EditCondition = "IsDelay", EditConditionHides))
	FVector2D DelayWait = FVector2D(0.f, 1.f);

	UPROPERTY(EditAnywhere)
	ENPCMoveType MoveType = ENPCMoveType::LOOP;
	
	UPROPERTY(EditAnywhere)
	bool IsMove = true;

	UPROPERTY(EditAnywhere)
	bool IsDebug = false;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
	UPROPERTY()
	AAIController* AIController;

	UPROPERTY()
	int32 CurrentTargetPoint = 0;
	
	UPROPERTY()
	FTimerHandle TimerHandleDelay;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void MoveLoop();
	
	// UFUNCTION()
	void MoveLoopEnd(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION()
	void MoveRandom();
	
	// UFUNCTION()
	void MoveRandomEnd(FAIRequestID RequestID, const FPathFollowingResult& Result);

private:
	virtual void BeginPlay() override;
		
};
