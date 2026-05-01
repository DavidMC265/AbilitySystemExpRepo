#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MainGameplayAbility.h"
#include "HitReactAbility.generated.h"

UCLASS()
class ABILITYSYSTEMEXP_API UHitReactAbility : public UMainGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FVector ToInstigator;
};
