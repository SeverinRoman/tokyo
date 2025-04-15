#include "InputCatcherComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


UInputCatcherComponent::UInputCatcherComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInputCatcherComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInputCatcherComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	World = GetWorld();
	Owner = GetOwner();

	if (Owner)
	{
		ACharacter* Character = Cast<ACharacter>(Owner);

		if (Character)
		{
			APlayerController* PlayerControllerr = Cast<APlayerController>(Character->GetController());

			if (PlayerControllerr)
			{
				UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerr->GetLocalPlayer());
				
				if (EnhancedInputLocalPlayerSubsystem && PlayerInputComponent)
				{
					EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
					EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputMapping, PlayerIndex);

					EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

					BindInputs();
				}
			}
		}
	}
}

void UInputCatcherComponent::BindInputs()
{
	if (!EnhancedInputComponent) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputMoveStarted);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UInputCatcherComponent::OnInputMoveTriggered);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputMoveCompleted);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputLookStarted);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputCatcherComponent::OnInputLookTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputLookCompleted);

	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputRunStarted);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputRunCompleted);

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputInteractStarted);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputInteractCompleted);

	EnhancedInputComponent->BindAction(CameraAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputCameraStarted);
	EnhancedInputComponent->BindAction(CameraAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputCameraCompleted);

	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputPauseStarted);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputPauseCompleted);
}

void UInputCatcherComponent::UnBindInputs()
{
	if (!EnhancedInputComponent) return;
	
	EnhancedInputComponent->ClearActionBindings();
}

