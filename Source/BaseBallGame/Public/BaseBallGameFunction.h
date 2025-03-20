// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseBallGameFunction.generated.h"

/**
 * 
 */
UCLASS()
class BASEBALLGAME_API UBaseBallGameFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "BaseBallGameFunction")
	static int32 GenerateUniqueThreeDigitNumber();
	UFUNCTION(BlueprintCallable, Category = "BaseBallGameFunction")
	static FString ResultJudgment(int32 Server, FString Client);
	
};
