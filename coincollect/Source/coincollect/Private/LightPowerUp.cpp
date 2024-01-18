#include "LightPowerUp.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ALightPowerUp::ALightPowerUp()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	// Create the point light components
	Light1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light1"));
	Light1->SetupAttachment(RootComponent);
	Light2 = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light2"));
	Light2->SetupAttachment(RootComponent);
	Light3 = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light3"));
	Light3->SetupAttachment(RootComponent);

	// Set the collision component to overlap with the player
	CollisionComponent->SetCollisionProfileName("OverlapAllDynamic");

	// Set up a notification for when this actor overlaps with something
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightPowerUp::OnPlayerOverlap);

	Light1->SetLightColor(FLinearColor(0.0f, 0.302f, 0.0f, 1.0f)); 
	Light1->SetIntensity(100.0f);

	Light2->SetLightColor(FLinearColor(0.0f, 0.302f, 0.0f, 1.0f));
	Light2->SetIntensity(100.0f);

	Light3->SetLightColor(FLinearColor(0.0f, 0.302f, 0.0f, 1.0f));
	Light3->SetIntensity(100.0f);
}

// Called when the game starts or when spawned
void ALightPowerUp::BeginPlay()
{
	Super::BeginPlay();

	// Initially set the point lights to be visible
	Light1->SetVisibility(false);
	Light2->SetVisibility(false);
	Light3->SetVisibility(false);
}

void ALightPowerUp::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is the player character
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		// Get the current light state
		bool bIsLightOn = Light1->IsVisible();

		// Toggle the light state
		Light1->SetVisibility(!bIsLightOn);
		Light2->SetVisibility(!bIsLightOn);
		Light3->SetVisibility(!bIsLightOn);
	}
}