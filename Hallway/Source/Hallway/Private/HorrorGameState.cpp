// Fill out your copyright notice in the Description page of Project Settings.

#include "Hallway.h"
#include "Engine.h"
#include "HorrorGameState.h"


AHorrorGameState::AHorrorGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	EventTimer = 60.f;
	TimeUntilNextEvent = 20.f;
	TimeUntilNextSound = 10.f;
	EventTimerRunning = false;

	PrimaryActorTick.bCanEverTick = true;
}

bool AHorrorGameState::CallRandomEvent()
{
	if (Events.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No events to call"));
		return false;
	}

	TArray<AGameplayEvent*> ValidEvents;

	for(AGameplayEvent* Event : Events)
	{
		if (!Event || !Event->IsValidLowLevel())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Found invalid AGamplayEvent"));
			continue;
		}

		if (Event->CanExecuteEvent())
		{
			ValidEvents.Add(Event);
		}
	}

	if (ValidEvents.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No valid events found, skipping event tick"));
		return false;
	}

	AGameplayEvent* Event = ValidEvents[FMath::RandHelper(ValidEvents.Num())];
	Event->ExecuteEvent();
	return true;
}

bool AHorrorGameState::CallRandomSound()
{
	if (Sounds.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No sounds to call"));
		return false;
	}

	USoundBase* Sound = Sounds[FMath::RandHelper(Sounds.Num())];
	if (!Sound || !Sound->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid USoundBase in AHorrorGameState::Sounds array"));
		return false;
	}

	FVector Location = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector Offset = FVector(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), FMath::RandRange(-1, 1));
	Offset *= 1000;
	Location += Offset;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);

	return true;
}

bool AHorrorGameState::AddGameplayEvent(AGameplayEvent* Actor)
{
	if (!Actor || !Actor->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid UObject passed to AddGameplayEvent"));
		return false;
	}

	Events.Add(Actor);
	return true;
}

void AHorrorGameState::ContinueEventTimer(float Multiplier)
{
	TimeUntilNextEvent = FMath::RandRange(EventTimer, EventTimer * Multiplier);
	EventTimerRunning = true;
}

void AHorrorGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EventTimerRunning)
	{
		TimeUntilNextEvent -= DeltaTime;
		TimeUntilNextSound -= DeltaTime;
		if (TimeUntilNextEvent <= 0)
		{
			EventTimerRunning = false;
			if (!CallRandomEvent())
			{
				ContinueEventTimer(0.5f);
			}
		}

		if (TimeUntilNextSound <= 0 && TimeUntilNextEvent > 10.f)
		{
			CallRandomSound();
			TimeUntilNextSound = FMath::RandRange(EventTimer / 2.f, EventTimer + EventTimer / 2.f);
		}
	}
}