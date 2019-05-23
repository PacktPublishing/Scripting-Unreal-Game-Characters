// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class CUSTOM_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* FirstPersonArms;

	bool bIsInFirstPerson;

	void ToggleView();

	void BeginSprint();
	void EndSprint();

	void Reload();

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ReloadAnimation;

	void MoveForward(float Value);
	void MoveRight(float Value);
};
