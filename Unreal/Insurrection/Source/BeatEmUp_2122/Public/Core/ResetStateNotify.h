// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ResetStateNotify.generated.h"

/**
 * 
 */
UCLASS()
class BEATEMUP_2122_API UResetStateNotify : public UAnimNotify
{
  GENERATED_BODY()

  public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};