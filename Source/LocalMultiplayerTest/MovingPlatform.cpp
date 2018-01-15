// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
  // Enable actor ticking
  PrimaryActorTick.bCanEverTick = true;

  // allow the actor to move
  SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
  Super::BeginPlay();
  // Returns true is self is server
  // Returns false is self is client

  // set whether this actor replicates to network client
  // If this changes on the sever all the clients will be aware
  // we cannot set replicates on client should only be on the server

  if(HasAuthority())
  {
    SetReplicates(true);
  // sets whether this actor's movement replicates to network clients
    SetReplicateMovement(true);
  }

  v_global_start_location = GetActorLocation();
  v_global_target_location = GetTransform().TransformPosition(targetLocation);
}

void AMovingPlatform::Tick(float deltatime)
{
  Super::Tick(deltatime);

  if(activeTriggers > 0)
  {
    // Store actors locations
    if (HasAuthority())
    {
      // this is in local space
      auto currentLocation = GetActorLocation();
      float movementLength = (v_global_target_location - v_global_start_location).Size();
      float movementTraveled = (currentLocation - v_global_start_location).Size();

      if (movementTraveled > movementLength)
      {
        const FVector temp = v_global_start_location;
        v_global_start_location = v_global_target_location;
        v_global_target_location = temp;
      }

      auto direction = (v_global_target_location - v_global_start_location).GetSafeNormal();
      currentLocation += speed * deltatime * direction;
      SetActorLocation(currentLocation);
    }
  }
}

void AMovingPlatform::AddActiveTrigger()
{
  activeTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
  if (activeTriggers > 0)
    activeTriggers--;
}
