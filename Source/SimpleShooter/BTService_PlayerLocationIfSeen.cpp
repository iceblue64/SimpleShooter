/*****************************************************************//**
 * \file   BTService_PlayerLocationIfSeen.cpp
 * \brief  Retrieve the player pawn from the game world to update
 * the behavior tree's blackboard with the player's current location
 * if LineOfSightTo() logic succeeds.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BTService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerPawn == nullptr)
        return;

    if (OwnerComp.GetAIOwner() == nullptr)
        return;

    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
