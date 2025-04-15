#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "InputCatcherComponent.generated.h"


class UEnhancedInputComponent;
class APlayerController;
class AController;
class UInputAction;
class UInputMappingContext;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMove, FInputActionInstance, InputActionInstance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputLook, FInputActionInstance, InputActionInstance);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputRun, FInputActionInstance, InputActionInstance, bool, IsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputInteract, FInputActionInstance, InputActionInstance, bool, IsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputCamera, FInputActionInstance, InputActionInstance, bool, IsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputPause, FInputActionInstance, InputActionInstance, bool, IsPressed);


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UInputCatcherComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputCatcherComponent();

public:
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UFUNCTION()
	void SetInput(bool bSetInput) { if (bSetInput == IsSetInput) return; bSetInput ? BindInputs() : UnBindInputs(); IsSetInput = bSetInput; };

	UFUNCTION()
	bool GetInput() { return IsSetInput; };

public:
	UPROPERTY(BlueprintAssignable)
	FOnInputMove OnInputMove;
	
	UPROPERTY(BlueprintAssignable)
	FOnInputLook OnInputLook;

	UPROPERTY(BlueprintAssignable)
	FOnInputRun OnInputRun;
	
	UPROPERTY(BlueprintAssignable)
	FOnInputInteract OnInputInteract;

	UPROPERTY(BlueprintAssignable)
	FOnInputCamera OnInputCamera;

	UPROPERTY(BlueprintAssignable)
	FOnInputPause OnInputPause;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly)
	int PlayerIndex = 0;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* CameraAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* PauseAction;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AController* Controller;

private:
	UPROPERTY(VisibleInstanceOnly)
	bool IsSetInput = true;
	
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;

private:
	UFUNCTION()
	void BindInputs();
	
	UFUNCTION()
	void UnBindInputs();

private:
	UFUNCTION()
	void OnInputMoveStarted(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};
	
	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};

	UFUNCTION()
	void OnInputMoveCompleted(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};

	
	UFUNCTION()
	void OnInputLookStarted(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};
	
	UFUNCTION()
	void OnInputLookTriggered(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};

	UFUNCTION()
	void OnInputLookCompleted(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};


	UFUNCTION()
	void OnInputRunStarted(const FInputActionInstance& InputActionInstance) { OnInputRun.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputRunCompleted(const FInputActionInstance& InputActionInstance) { OnInputRun.Broadcast(InputActionInstance, false);};

	
	UFUNCTION()
	void OnInputInteractStarted(const FInputActionInstance& InputActionInstance) { OnInputInteract.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputInteractCompleted(const FInputActionInstance& InputActionInstance) { OnInputInteract.Broadcast(InputActionInstance, false);};


	UFUNCTION()
	void OnInputCameraStarted(const FInputActionInstance& InputActionInstance) { OnInputCamera.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputCameraCompleted(const FInputActionInstance& InputActionInstance) { OnInputCamera.Broadcast(InputActionInstance, false);};


	UFUNCTION()
	void OnInputPauseStarted(const FInputActionInstance& InputActionInstance) { OnInputPause.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputPauseCompleted(const FInputActionInstance& InputActionInstance) { OnInputPause.Broadcast(InputActionInstance, false);};
	
private:
	virtual void BeginPlay() override;
	
};
