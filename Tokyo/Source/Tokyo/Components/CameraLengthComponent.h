#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/TweenEnums.h"
#include "CameraLengthComponent.generated.h"


class USpringArmComponent;
class UTweenFloat;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UCameraLengthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCameraLengthComponent();

public:
	UFUNCTION()
	void Change();
	
private:
	UPROPERTY(EditDefaultsOnly)
	ETweenEaseType TweenEase = ETweenEaseType::Linear;
	
	UPROPERTY(EditDefaultsOnly)
	float Duration = 0.25f;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<float> TargetArmLengths;

	UPROPERTY(EditDefaultsOnly)
	int StartLengths = 1;

private:
	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	int CurrentLengths = 0;
	
	UPROPERTY()
	UTweenFloat* TweenFloat;

private:
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void TweenChange(float Value);

private:
	virtual void BeginPlay() override;
};
