#include "Gameplay Tags/MainTags.h"

namespace MainTags
{
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "MainTags.Abilities.ActivateOnGiven", "Tag for the Abilities that should activate immediately once given");

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "MainTags.Abilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "MainTags.Abilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "MainTags.Abilities.Tertiary", "Tag for the Tertiary Ability");

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "MainTags.Abilities.Death", "Tag for the Death Ability");
	}

	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "MainTags.Events.Enemy.KillScored", "Tag for the enemy KillScored Event");

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "MainTags.Events.Enemy.HitReact", "Tag for the enemy HitReact Event");
		}
	}
}