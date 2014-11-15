// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameplayEvent.generated.h"

UCLASS(Blueprintable)
class AGameplayEvent : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay", meta = (FriendlyName = "Execute Event"))
	void ExecuteEvent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay", meta = (FriendlyName = "Can Execute Event"))
	bool CanExecuteEvent();
};