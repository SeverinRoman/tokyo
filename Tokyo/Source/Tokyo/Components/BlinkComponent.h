#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/TweenEnums.h"
#include "BlinkComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UBlinkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBlinkComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	float Speed = 0.1f;
	
	UPROPERTY(EditDefaultsOnly)
	ETweenEaseType Easing = ETweenEaseType::EaseInOutCubic;

	UPROPERTY(EditDefaultsOnly)
	FVector2D Delay = FVector2D(1.f, 5.f);
	
	UPROPERTY(EditDefaultsOnly)
	FName Tag = "skeletal_mesh_component";

	UPROPERTY(EditDefaultsOnly)
	FName Morph = "Fcl_EYE_Close";

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY()
	FTimerHandle BlinkTimerHandle;	

private:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void Blink();
	
	UFUNCTION()
	void ScheduleNextBlink();

private:	
	virtual void BeginPlay() override;
	
};
