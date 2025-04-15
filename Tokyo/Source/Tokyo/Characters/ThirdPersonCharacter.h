
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharacter.generated.h"


class UInputCatcherComponent;


UCLASS()
class TOKYO_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AThirdPersonCharacter();

private:
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;

private:
	UFUNCTION()
	void Init();
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
