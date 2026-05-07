#include "Player/MainPlayerState.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

AMainPlayerState::AMainPlayerState()
{
    SetNetUpdateFrequency(100.f);

    AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}