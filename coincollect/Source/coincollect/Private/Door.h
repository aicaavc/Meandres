// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox; // Collision box for detecting player overlap

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bOpenDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AStats", Meta = (MakeEditWidget = true))
	FVector OpenedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AStats")
	float MovingSpeed;

private:
	void OpenDoor(UStaticMeshComponent* Actor, FVector TargetLocation, float DeltaTime, float InterpSpeed);
	void CloseDoor(UStaticMeshComponent* Actor, float DeltaTime, float InterpSpeed);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};