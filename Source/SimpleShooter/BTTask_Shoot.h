/*****************************************************************//**
 * \file   BTTask_Shoot.h
 * \brief  Header file for overriden ExecuteTask() to allow AI to
 * perform shooting logic.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
