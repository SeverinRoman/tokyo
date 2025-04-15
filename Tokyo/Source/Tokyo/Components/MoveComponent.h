#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/TweenEnums.h"
#include "MoveComponent.generated.h"


class UCharacterMovementComponent;
class UAnimationComponent;
class UStateComponent;

class UTweenFloat;


UENUM(BlueprintType)
enum class EMoveType : uint8
{
	NONE = 0,

	WALK = 1,
	RUN = 2,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveToLocationComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveToLocationFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeMove, EMoveType, NewMove);


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMoveComponent();

public:
	UFUNCTION(BlueprintCallable)
	void ToggleMontageRotation(bool bIsEnable);
	
	UFUNCTION()
	void ToggleRotation(bool bIsEnable);
	
	UFUNCTION()
	EMoveType GetMove() { return CurrentMove; };
	
	UFUNCTION()
	void MoveToLocation(FVector Location);

	UFUNCTION()
	FVector GetVelocity();

	UFUNCTION()
	float GetWalkSpeed() { return WalkSpeed; };

	UFUNCTION()
	float GetRunSpeed() { return RunSpeed; };

public:
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 337.5f;

	UPROPERTY(EditDefaultsOnly)
	float DistanceMoveToLocationComplete = 100.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMoveToLocationComplete OnMoveToLocationComplete;
	
	UPROPERTY(BlueprintAssignable)
	FOnMoveToLocationFailed OnMoveToLocationFailed;
	
	UPROPERTY(BlueprintAssignable)
	FOnChangeMove OnChangeMove;

public:
	UFUNCTION(BlueprintCallable)
	void Move(float X, float Y);
	
	UFUNCTION(BlueprintCallable)
	void Run();

	UFUNCTION(BlueprintCallable)
	void Walk();

private:
	UPROPERTY(EditDefaultsOnly)
	EMoveType StartMove = EMoveType::WALK;
	
	UPROPERTY(EditDefaultsOnly)
	float SmoothDuration = 0.6f;
	
	UPROPERTY(EditDefaultsOnly)
	ETweenEaseType SmoothEase = ETweenEaseType::EaseInOutSine;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY(VisibleInstanceOnly)
	EMoveType CurrentMove;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
	UPROPERTY()
	AController* Controller;
	
	UPROPERTY()
	bool IsEnableRotation = true;
	
	UPROPERTY()
	bool IsMoveToLocation = false;
	
	UPROPERTY()
	FRotator SaveRotationRate;
	
	UPROPERTY()
	FVector LocationToMove;
	
	UPROPERTY()
	UTweenFloat* SmoothTween;

private:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;

	UPROPERTY()
	UAnimationComponent* AnimationComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void StopStandBy();
	
	UFUNCTION()
	void SmoothChangeMaxWalkSpeed(float Value);

private:
	
	UFUNCTION()
	void StopAnimation();
	
	UFUNCTION()
	void CheckMoveToLocationComplete();
	
	UFUNCTION()
	void StopMoveToLocation();

private:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
