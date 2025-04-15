#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};
class TOKYO_API IInteractInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor *Actor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckInteract();
};
