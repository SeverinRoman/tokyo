#include "BlinkComponent.h"


UBlinkComponent::UBlinkComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlinkComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBlinkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

