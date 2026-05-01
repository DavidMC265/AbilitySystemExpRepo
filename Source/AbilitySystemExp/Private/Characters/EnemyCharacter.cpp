#include "Characters/EnemyCharacter.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!IsValid(GetAbilitySystemComponent())) return;

    GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

    if (!HasAuthority()) return;

    GiveStartupAbilites();
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}