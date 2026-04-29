#include "Player/MainPlayerState.h"
#include "AbilitySystemComponent.h"

AMainPlayerState::AMainPlayerState()
{
    SetNetUpdateFrequency(100.f);

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}