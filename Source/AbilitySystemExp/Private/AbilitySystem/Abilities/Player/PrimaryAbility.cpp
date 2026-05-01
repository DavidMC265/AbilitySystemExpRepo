#include "AbilitySystem/Abilities/Player/PrimaryAbility.h"
#include "Engine/OverlapResult.h"
#include "Gameplay Tags/MainTags.h"
#include "AbilitySystemBlueprintLibrary.h"


TArray<AActor*> UPrimaryAbility::HitBoxOverlapTest()
{
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

    // Ensure that the overlap test ignores the Avatar Actor
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActors(ActorsToIgnore);

    FCollisionResponseParams ResponseParams;
    ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
    ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

    TArray<FOverlapResult> OverlapResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
    
    const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
    const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.0f, 0.0f, HitBoxElevationOffset);

    GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);

    TArray<AActor*> ActorsHit;
    for (const FOverlapResult& Result : OverlapResults)
    {
        if (!IsValid(Result.GetActor())) continue;
        ActorsHit.AddUnique(Result.GetActor());
    }

    if (bDrawDebugs)
    {
        DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
    }

    return ActorsHit;
}

void UPrimaryAbility::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
    DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);

    for (const FOverlapResult& Result : OverlapResults)
    {
        if (IsValid(Result.GetActor()))
        {
            FVector DebugLocation = Result.GetActor()->GetActorLocation();
            DebugLocation.Z += 100.0f;
            DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
        }
    }
}

void UPrimaryAbility::SendHitReactEventToActors(const TArray<AActor*> ActorsHit)
{
    for (AActor* HitActor: ActorsHit)
    {
        FGameplayEventData Payload;
        Payload.Instigator = GetAvatarActorFromActorInfo();
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, MainTags::Events::Enemy::HitReact, Payload);
    }
}

