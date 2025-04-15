#include "ThirdPersonCharacter.h"

#include "InputCatcherComponent.h"


AThirdPersonCharacter::AThirdPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputCatcherComponent = FindComponentByClass<UInputCatcherComponent>();

	if (InputCatcherComponent)
	{
		InputCatcherComponent->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

void AThirdPersonCharacter::Init()
{
	
}

