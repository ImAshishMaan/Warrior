#include "WarriorTypes/WarriorStructTypes.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const {
	return AbilityToGrant && InputTag.IsValid();
}
