// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayEvent.generated.h"

UINTERFACE(MinimalAPI)
class UGameplayEvent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGameplayEvent
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Gameplay", meta = (FriendlyName="Execute Event"))
	void ExecuteEvent();
};