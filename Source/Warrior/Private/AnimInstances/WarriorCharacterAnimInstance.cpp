#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());
	if(OwningCharacter) {
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
	
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds) {
	if(!OwningCharacter || !OwningMovementComponent) {
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().Size() > 0.f;
	
}
