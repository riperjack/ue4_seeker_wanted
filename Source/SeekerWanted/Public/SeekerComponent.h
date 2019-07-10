// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "WantedComponent.h"
#include "SeekerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEEKERWANTED_API USeekerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USeekerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "General")
	TArray<UWantedComponent*> GetWanteds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	float MaxSeekDistance = 1000;

protected:
	virtual void BeginPlay() override;

private:
	void Seek();

	TArray<UWantedComponent*> Wanteds;
	UWantedComponent* ClosestWanted;
	UWantedComponent* MostDistantWanted;
};
