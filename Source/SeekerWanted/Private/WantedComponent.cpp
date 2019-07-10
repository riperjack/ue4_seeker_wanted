#include "WantedComponent.h"
#include "GameFramework/Actor.h"

UWantedComponent::UWantedComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWantedComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWantedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWantedComponent::SetDetected(bool isDetected, float distance)
{
	DistanceToSeeker = distance;
	bIsDetected = isDetected;
}

void UWantedComponent::SetClosest(bool isClosest) {
	bIsClosest = isClosest;
}

void UWantedComponent::SetMostDistant(bool isMostDistant) {
	bIsIsMostDistant = isMostDistant;
}