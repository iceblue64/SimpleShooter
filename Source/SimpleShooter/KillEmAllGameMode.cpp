/*****************************************************************//**
 * \file   KillEmAllGameMode.cpp
 * \brief  Logic for ending the game and determining the winner
 * based on the status of player and AI-controlled characters.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
    // If the cast is successful, the killed pawn's controller belongs to the player
    if (PlayerController != nullptr)
    {
        EndGame(false); // Player is not winner (false)
    }

    // Loop over all ShooterAI instances in world
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        // If not dead
        if (!Controller->IsDead())
            return;
    }
    EndGame(true); // Player is winner (true)
}

// Iterate over actors in the level
void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    // Return a range object that iterates over all world controllers
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        // bIsWinner evals to true or false based upon PawnKilled() logic
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner; 
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); 
    }
}
