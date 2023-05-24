/*****************************************************************//**
 * \file   ShooterPlayerController.h
 * \brief  Header file for win/lose state logic and variables.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass; // TSubclassOf = a variable that holds a ref to a class + its subclasses

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5;

	UPROPERTY(EditAnywhere)
		UUserWidget* HUD;

	FTimerHandle RestartTimer;
};
