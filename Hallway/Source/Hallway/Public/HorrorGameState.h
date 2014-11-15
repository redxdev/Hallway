// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "GameplayEvent.h"
#include "HorrorGameState.generated.h"


UCLASS()
class HALLWAY_API AHorrorGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay")
	TArray<UObject*> Events;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool CallRandomEvent();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool AddGameplayEvent(UObject* Object);
};
