#pragma once

#include "StateType.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"


class UCharacterMovementComponent;
class UMoveComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, EStateType, StateType);


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EStateType GetState() { return State; };

	UFUNCTION(BlueprintCallable)
	void SetState(EStateType NewState);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeed() { return Speed; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDirection() { return Direction; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetVelocity() { return Velocity; };

public:
	UPROPERTY(BlueprintAssignable)
	FOnStateChange OnStateChange;

private:
	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;
	
	UPROPERTY()
	UMoveComponent* MoveComponent;
	
private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	EStateType State;

	UPROPERTY()
	FVector Velocity;

	UPROPERTY()
	float Direction;

	UPROPERTY()
	float Speed;
	
	UPROPERTY()
	float WalkSpeed;
	
	UPROPERTY()
	float RunSpeed;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void ChangeState();
	
	UFUNCTION()
	void Update();

	UFUNCTION()
	void UpdateData();
	
	UFUNCTION()
	void UpdateState();
	
	UFUNCTION()
	void Debug();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
