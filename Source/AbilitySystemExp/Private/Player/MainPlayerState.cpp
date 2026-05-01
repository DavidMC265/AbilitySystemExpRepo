#include "Player/MainPlayerState.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"

AMainPlayerState::AMainPlayerState()
{
    SetNetUpdateFrequency(100.f);

    AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}