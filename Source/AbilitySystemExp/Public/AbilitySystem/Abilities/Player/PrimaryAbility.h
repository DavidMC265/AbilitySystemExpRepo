#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MainGameplayAbility.h"
#include "PrimaryAbility.generated.h"

UCLASS()
class ABILITYSYSTEMEXP_API UPrimaryAbility : public UMainGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SendHitReactEventToActors(const TArray<AActor*> ActorsHit);

private:
	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Abilities")
	float HitBoxRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float HitBoxForwardOffset = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float HitBoxElevationOffset = 20.0f;
};
