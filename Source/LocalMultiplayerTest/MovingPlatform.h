// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYERTEST_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
 
private:
  FVector v_global_start_location;
  FVector v_global_target_location;

  UPROPERTY(EditAnywhere)
  int activeTriggers = 1;

public :
  AMovingPlatform();

  virtual void BeginPlay() override;
  virtual void Tick(float deltatime) override;

  void AddActiveTrigger();
  void RemoveActiveTrigger();


  UPROPERTY(EditAnywhere)
  float speed = 20.0f;

  UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
  FVector targetLocation; 

  UPROPERTY(BlueprintReadWrite, EditAnywhere)
  bool canEdit;
  
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (EditCondition = canEdit))
  int Editme;

  UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
  float acceleration;

  UPROPERTY(EditAnywhere, meta = (UIMin = "-100.0", UIMax = "200.0"))
  float test;
};
