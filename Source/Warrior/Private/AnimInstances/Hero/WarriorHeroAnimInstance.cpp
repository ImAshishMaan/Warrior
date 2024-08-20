#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

#include "Characters/WarriorHeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(OwningCharacter) {
		AWarriorHeroCharacter* HeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter);
		if(HeroCharacter) {
			bShouldEnterRelaxState = HeroCharacter->GetCharacterMovement()->IsFalling();
		}
	}
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds) {
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration) {
		IdleElapsedTime = 0.f;;
		bShouldEnterRelaxState = false;
	} else {
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
