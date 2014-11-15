// Fill out your copyright notice in the Description page of Project Settings.

#include "Hallway.h"
#include "GameplayEvent.h"

AGameplayEvent::AGameplayEvent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AGameplayEvent::ExecuteEvent_Implementation()
{
}

bool AGameplayEvent::CanExecuteEvent_Implementation()
{
	return false;
}