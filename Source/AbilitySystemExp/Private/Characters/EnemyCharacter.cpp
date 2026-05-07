#include "Characters/EnemyCharacter.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!IsValid(GetAbilitySystemComponent())) return;

    GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
    OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

    if (!HasAuthority()) return;

    GiveStartupAbilites();
    InitializeAttributes();
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAttributeSet* AEnemyCharacter::GetAttributeSet() const
{
    return AttributeSet;
}