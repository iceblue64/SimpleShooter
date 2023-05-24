/*****************************************************************//**
 * \file   BTTask_Shoot.cpp
 * \brief  Retrieve the AI controller from the behavior tree, 
 * casts to an AShooterCharacter, and calls the Shoot function.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Get ahold of the AI controller
    if (OwnerComp.GetAIOwner() == nullptr)
        return EBTNodeResult::Failed;

    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (Character == nullptr)
        return EBTNodeResult::Failed;

    Character->Shoot();

    return EBTNodeResult::Succeeded;
}
