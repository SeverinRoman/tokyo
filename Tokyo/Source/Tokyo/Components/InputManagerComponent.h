#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"


class UInputCatcherComponent;
class UStateComponent;
class UInteractComponent;
class UMoveComponent;
class UCameraLengthComponent;
class ACharacter;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputManagerComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	int PlayerIndex = 0;
	
	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
private:
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;
	
	UPROPERTY()
	UMoveComponent* MoveComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;
	
	UPROPERTY()
	UInteractComponent* InteractComponent;
	
	UPROPERTY()
	UCameraLengthComponent* CameraLengthComponent;

private:
	UFUNCTION()
	void Init();

private:
	UFUNCTION()
	void OnInputMove(const FInputActionInstance InputActionInstance);

	UFUNCTION()
	void OnInputLook(const FInputActionInstance InputActionInstance);

	UFUNCTION()
	void OnInputRun(const FInputActionInstance InputActionInstance, bool IsPressed);

	UFUNCTION()
	void OnInputInteract(const FInputActionInstance InputActionInstance, bool IsPressed);

	UFUNCTION()
	void OnInputCamera(const FInputActionInstance InputActionInstance, bool IsPressed);

	UFUNCTION()
	void OnInputPause(const FInputActionInstance InputActionInstance, bool IsPressed);

private:
	virtual void BeginPlay() override;
		
};
