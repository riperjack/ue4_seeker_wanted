#include "SeekerComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include <limits>

USeekerComponent::USeekerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USeekerComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void USeekerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Seek();
}

void USeekerComponent::Seek()
{
	// Reset wanteds array while keeping memory allocation
	Wanteds.Reset(0);

	float MaxDistance = std::numeric_limits<float>::min();
	float MinDistance = std::numeric_limits<float>::max();

	// Iterate over all actors with wanted component
	for (TObjectIterator<UWantedComponent> Itr; Itr; ++Itr)
	{
		UWantedComponent *WantedComponent = *Itr;		
		AActor *WantedActor = WantedComponent->GetOwner();

		// Skip actors that are not initialized
		if (WantedActor == nullptr || WantedComponent->GetWorld() != this->GetWorld()) continue;

		// Reset most distant and closest wanteds
		WantedComponent->SetClosest(false);
		WantedComponent->SetMostDistant(false);

		AActor *Owner = GetOwner();

		// Check distance between seeker and wanted
		float distance = (Owner->GetActorLocation() - WantedActor->GetActorLocation()).Size();

		if (distance > MaxSeekDistance) {
			WantedComponent->SetDetected(false);
			continue;
		}

		// Raytrace logic start
		FHitResult OutHit;
		FVector Start = Owner->GetActorLocation();
		FVector ForwardVector = Owner->GetActorForwardVector();
		FVector End = WantedActor->GetActorLocation();
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Owner);

		// If raytrace between seeker and wanted is blocked, then wanted cannot be detected
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams)) {
			DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Green);
			DrawDebugLine(GetWorld(), OutHit.Location, End, FColor::Red);
			WantedComponent->SetDetected(false);
		}
		// Otherwise wanted is detected
		else {
			DrawDebugLine(GetWorld(), Start, End, FColor::Green);
			WantedComponent->SetDetected(true, distance);
			Wanteds.Add(WantedComponent);

			// Check if min or max distance
			if (distance > MaxDistance) {
				MaxDistance = distance;
				MostDistantWanted = WantedComponent;
			}
			if (distance < MinDistance) {
				MinDistance = distance;
				ClosestWanted = WantedComponent;
			}
		}
	}

	// Set closest and most distant wanteds
	if (MostDistantWanted != nullptr) MostDistantWanted->SetMostDistant(true);
	if (ClosestWanted != nullptr) ClosestWanted->SetClosest(true);
}

TArray<UWantedComponent*> USeekerComponent::GetWanteds()
{
	TArray<UWantedComponent*> Result = Wanteds;

	Result.Sort([](const UWantedComponent& Left, const UWantedComponent& Right) { return Left.DistanceToSeeker> Right.DistanceToSeeker; });

	return Result;
}