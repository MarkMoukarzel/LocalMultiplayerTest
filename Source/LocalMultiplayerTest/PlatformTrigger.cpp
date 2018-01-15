// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  _trigger_volume_ = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));

  if (!ensure(_trigger_volume_ != nullptr)) return;
    RootComponent = _trigger_volume_;


}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

  _trigger_volume_->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
  _trigger_volume_->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  //UE_LOG(LogTemp, Warning, TEXT("Activated"));
  for(AMovingPlatform * mvplatform : _platforms_to_trigger_)
  {
    mvplatform->AddActiveTrigger();
  }
}


void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  UE_LOG(LogTemp, Warning, TEXT("Deactivated"));

  // Other Actor is the actor that triggered the event. Check that is not ourself.  
  /*if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
  {
  }*/
  for(AMovingPlatform * mvplatform : _platforms_to_trigger_)
  {
    mvplatform->RemoveActiveTrigger();
  }
}

