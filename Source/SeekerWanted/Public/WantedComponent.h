#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WantedComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEEKERWANTED_API UWantedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWantedComponent();

	UPROPERTY(BlueprintReadOnly, Category = "General")
	float DistanceToSeeker;

	UPROPERTY(BlueprintReadOnly, Category = "General")
	bool bIsDetected;

	UPROPERTY(BlueprintReadOnly, Category = "General")
	bool bIsClosest;

	UPROPERTY(BlueprintReadOnly, Category = "General")
	bool bIsIsMostDistant;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDetected(bool isDetected, float distance = -1);
	void SetClosest(bool isClosest);
	void SetMostDistant(bool isMostDistant);
};
