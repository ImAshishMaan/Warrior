#include "Components/Combat/HeroCombatComponent.h"

#include "WarriorDebugHelper.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const {
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor) {
	//Super::OnHitTargetActor(HitActor);
	Debug::Print(GetOwningPawn()->GetName() + " hit " + HitActor->GetName());
}

void UHeroCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor) {
	//Super::OnPulledFromTargetActor(InteractedActor);
	Debug::Print(GetOwningPawn()->GetName() + " pulled from " + InteractedActor->GetName());
}
