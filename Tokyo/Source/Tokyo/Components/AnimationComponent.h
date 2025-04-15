#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"


class USkeletalMeshComponent;

enum class EAnimationType: uint8;
enum class EAnimationStandByType: uint8;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAnimationComponent();

public:
	UFUNCTION(BlueprintCallable)
	void Play(UAnimMontage* AnimMontage);
	
	UFUNCTION(BlueprintCallable)
	void Pause();
	
	UFUNCTION(BlueprintCallable)
	void Stop(float Blend = 0.1f);
	
	UFUNCTION(BlueprintCallable)
	void ResetVRM();

public:
	UFUNCTION()
	void PlayBase(EAnimationType Animation);

	UFUNCTION()
	void PlayStandBy();

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EAnimationType, UAnimMontage*> Animations;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAnimationStandByType, UAnimMontage*> StandByAnimations;
	
	UPROPERTY(EditDefaultsOnly)
	FName TagSkeletalMesh = "skeletal_mesh";
	
private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY()
	TArray<UAnimInstance*> AnimInstances;

private:
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	
private:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void InitAnimInstances();
	
	UFUNCTION()
	void PlayAll(UAnimMontage* AnimMontage);
	
	UFUNCTION()
	void StopAll(float Blend);
	
	UFUNCTION()
	void PauseAll();
	
private:
	virtual void BeginPlay() override;
	
};
