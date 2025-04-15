#pragma once

#include "Engine/EngineTypes.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


class UCameraComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();

public:
	UFUNCTION()
	void Interact();

private:
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_Visibility;;

	UPROPERTY(EditDefaultsOnly)
	float Distance = 31.f;
	
	UPROPERTY(EditDefaultsOnly)
	float Radius = 31.f;
	
	UPROPERTY(EditDefaultsOnly)
	float HalfHeight = 88.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
private:
	UPROPERTY()
	UCameraComponent* CameraComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void CheckInteract();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
