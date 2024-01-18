#include "KillBlock.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AKillBlock::AKillBlock()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create root component 
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
   

    // Create collision box
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetCollisionProfileName("Trigger");

    // Bind overlap event
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AKillBlock::OnOverlapBegin);
}

void AKillBlock::BeginPlay()
{
    Super::BeginPlay();
}

void AKillBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;

    // Check if the player is overlapping with the block
    if (CollisionBox->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        // Kill the player if player on block for 5 seconds
        if (TimeElapsed > 5.0f)
        {
            // Set player's health to 0
            APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            PlayerCharacter->Health = 0.0f;

            // Destroy the block itself
            Destroy();
        }
    }
}

void AKillBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Reset the timer when the player overlaps with the block
    TimeElapsed = 0.0f;
}
