#include "Door.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ADoor::ADoor() :
	bOpenDoor(false),
	MovingSpeed(5.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter && CollisionBox->IsOverlappingActor(PlayerCharacter))
	{
		bOpenDoor = true;
	}
	else
	{
		bOpenDoor = false;
	}

	if (bOpenDoor)
	{
		OpenDoor(StaticMesh, OpenedLocation, DeltaTime, MovingSpeed);
	}
	else
	{
		CloseDoor(StaticMesh, DeltaTime, MovingSpeed);
	}
}

void ADoor::OpenDoor(UStaticMeshComponent* Actor, FVector TargetLocation, float DeltaTime, float InterpSpeed)
{
	FVector CurrentLocation = Actor->GetRelativeLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
	Actor->SetRelativeLocation(NewLocation);
}

void ADoor::CloseDoor(UStaticMeshComponent* Actor, float DeltaTime, float InterpSpeed)
{
	FVector CurrentLocation = Actor->GetRelativeLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, FVector(0, 0, 0), DeltaTime, InterpSpeed);
	Actor->SetRelativeLocation(NewLocation);
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		bOpenDoor = true;
	}
}
