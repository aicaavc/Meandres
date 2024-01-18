#include "SlowdownArea.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASlowdownArea::ASlowdownArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASlowdownArea::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASlowdownArea::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASlowdownArea::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowdownArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		OverlapCharacter = Cast<APlayerCharacter>(OtherActor);
		OverlapCharacter->GetCharacterMovement()->MaxWalkSpeed = SlowedMovementSpeed;
	}
}

void ASlowdownArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlapCharacter)
	{
		OverlapCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginalMovementSpeed;
		OverlapCharacter = nullptr;
	}
}