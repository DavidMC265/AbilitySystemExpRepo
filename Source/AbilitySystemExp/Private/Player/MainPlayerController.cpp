#include "Player/MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

void AMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    if (!IsValid(InputSubsystem)) return;

    for (UInputMappingContext* Context : InputMappingContexts)
    {
        InputSubsystem->AddMappingContext(Context, 0);
    }

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!IsValid(EnhancedInputComponent)) return;

    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

    EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::Primary);
}

void AMainPlayerController::Jump()
{
    if (!IsValid(GetCharacter())) return;

    GetCharacter()->Jump();
}

void AMainPlayerController::StopJumping()
{
    if (!IsValid(GetCharacter())) return;

    GetCharacter()->StopJumping();
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
    if (!IsValid(GetPawn())) return;

    const FVector2D MovementVector = Value.Get<FVector2D>();
    // Find which way is forward
    const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
    GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AMainPlayerController::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddYawInput(LookAxisVector.X);
    AddPitchInput(LookAxisVector.Y);
}

void AMainPlayerController::Primary()
{
    UE_LOG(LogTemp, Warning, TEXT("Primary Action Triggered!"));
}

