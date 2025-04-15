#include "InputManagerComponent.h"

#include "CameraLengthComponent.h"
#include "InputCatcherComponent.h"
#include "InteractComponent.h"
#include "MoveComponent.h"
#include "StateComponent.h"

#include "Enums/StateType.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UInputManagerComponent::UInputManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInputManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UInputManagerComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex);
	
	if (!Owner) return;
	
	Character = Cast<ACharacter>(Owner);

	InputCatcherComponent = Owner->GetComponentByClass<UInputCatcherComponent>();
	MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
	InteractComponent = Owner->GetComponentByClass<UInteractComponent>();
	CameraLengthComponent= Owner->GetComponentByClass<UCameraLengthComponent>();
	StateComponent = Owner->GetComponentByClass<UStateComponent>();

	if (InputCatcherComponent)
	{
		InputCatcherComponent->OnInputMove.AddDynamic(this, &UInputManagerComponent::OnInputMove);
		InputCatcherComponent->OnInputLook.AddDynamic(this, &UInputManagerComponent::OnInputLook);

		InputCatcherComponent->OnInputRun.AddDynamic(this, &UInputManagerComponent::OnInputRun);
		InputCatcherComponent->OnInputInteract.AddDynamic(this, &UInputManagerComponent::OnInputInteract);
		InputCatcherComponent->OnInputCamera.AddDynamic(this, &UInputManagerComponent::OnInputCamera);

		InputCatcherComponent->OnInputPause.AddDynamic(this, &UInputManagerComponent::OnInputPause);
	}
}

void UInputManagerComponent::OnInputMove(const FInputActionInstance InputActionInstance)
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;
	
	if (MoveComponent)
	{
		MoveComponent->Move(X, Y);
	}
}

void UInputManagerComponent::OnInputLook(const FInputActionInstance InputActionInstance) 
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;

	if (StateComponent)
	{
		EStateType State = StateComponent->GetState();
		if (State != EStateType::IDLE && State != EStateType::WALK && State != EStateType::RUN && State != EStateType::STANDBY) return;
	}

	if (Character)
	{
		Character->AddControllerYawInput(X);
		Character->AddControllerPitchInput(Y);
	}
}

void UInputManagerComponent::OnInputInteract(const FInputActionInstance InputActionInstance, bool IsPressed) 
{
	if (IsPressed)
	{
		if (InteractComponent)
		{
			InteractComponent->Interact(); 
		}
	}
}

void UInputManagerComponent::OnInputRun(const FInputActionInstance InputActionInstance, bool IsPressed) 
{
	if (!MoveComponent) return;
	
	IsPressed ? MoveComponent->Run() : MoveComponent->Walk();
}

void UInputManagerComponent::OnInputCamera(const FInputActionInstance InputActionInstance, bool IsPressed)
{
	if (!CameraLengthComponent) return;
	
	CameraLengthComponent->Change();
}

void UInputManagerComponent::OnInputPause(const FInputActionInstance InputActionInstance, bool IsPressed)
{
	// if (!World || !UIIComponent) return;
	//
	// if (IsPressed)
	// {
	// 	if (StateComponent && DialogueComponent)
	// 	{
	// 		if (StateComponent->GetState() == EStateType::DIALOGUE)
	// 		{
	// 			DialogueComponent->Exit();
	// 			return;
	// 		}
	// 	}
	// 	
	// 	bool bIsPaused = UGameplayStatics::IsGamePaused(World);
	//
	// 	UGameplayStatics::SetGamePaused(World, !bIsPaused);
	//
	// 	bIsPaused ? UIIComponent->UnPause() : UIIComponent->Pause();
	//
	// 	if (IsDebug)
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("UInputManagerComponent::OnInputPause"));
	// 	}
	// }
}
