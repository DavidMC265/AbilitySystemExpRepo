#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract) // Abstract used to make object to not be instantiated from in the editor, it is only used for inheritance for other classes
class ABILITYSYSTEMEXP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

};
