// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom.h"
#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	FirstPersonArms = CreateDefaultSubobject<USkeletalMeshComponent>("FPArms");
	FirstPersonArms->SetVisibility(false);

	bIsInFirstPerson = false;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	FirstPersonArms->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	FirstPersonArms->SetRelativeLocation(FVector(0.f, -15.f, -155.f));

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::EndSprint);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::Reload);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ToggleView", IE_Pressed, this, &AMyCharacter::ToggleView);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AMyCharacter::ToggleView()
{
	bIsInFirstPerson = !bIsInFirstPerson;

	if (bIsInFirstPerson)
	{
		SpringArm->TargetArmLength = 0.f;
		GetMesh()->SetVisibility(false);
		FirstPersonArms->SetVisibility(true);
	}
	else
	{
		SpringArm->TargetArmLength = 300.f;
		GetMesh()->SetVisibility(true);
		FirstPersonArms->SetVisibility(false);
	}

}

void AMyCharacter::BeginSprint()
{
	GLog->Log("Begin sprint");
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void AMyCharacter::EndSprint()
{
	GLog->Log("End sprint");
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMyCharacter::Reload()
{

	if (ReloadAnimation)
	{
		PlayAnimMontage(ReloadAnimation);
	}

}

void AMyCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FVector MoveDirection = Controller->GetActorForwardVector();
		AddMovementInput(MoveDirection, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FVector MoveDirection = Controller->GetActorRightVector();
		AddMovementInput(MoveDirection, Value);
	}
}
