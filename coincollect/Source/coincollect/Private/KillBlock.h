#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h" 
#include "KillBlock.generated.h"

UCLASS()
class AKillBlock : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AKillBlock();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UBoxComponent* CollisionBox; // Collision box for detecting player overlap

private:
    float TimeElapsed;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
