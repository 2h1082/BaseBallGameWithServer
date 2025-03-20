// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBallGameFunction.h"
#include "Containers/Set.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Map.h"


int32 UBaseBallGameFunction::GenerateUniqueThreeDigitNumber()
{
	TArray<int32> Numbers={1,2,3,4,5,6,7,8,9};//선택 가능한 수들
	TArray<int32> GeneratedNumber;//선택된 수를 저장할 배열
	//3개의 중복되지 않는 수 선택
	for (int32 i=0;i<3;i++)
	{
		// 랜덤으로 인덱스 선택 및 해당 인덱스의 수 리스트에서 제거
		int32 RandomIndex=UKismetMathLibrary::RandomIntegerInRange(0,Numbers.Num()-1);
		GeneratedNumber.Add(Numbers[RandomIndex]);
		Numbers.RemoveAt(RandomIndex);
	}
	// 선택된 수를 조합하여 3자리 수로 변환
	int32 Result=GeneratedNumber[0]*100+GeneratedNumber[1]*10+GeneratedNumber[2];
	return Result;
}

FString UBaseBallGameFunction::ResultJudgment(int32 Server, FString Client)
{
	// '/' 문자 삭제
	Client.RemoveAt(0);
	// 잘못된 입력 예외 처리
	if (!Client.IsNumeric())
	{
		return TEXT("OUT");
	}
	// 문자열 숫자로 변환
	int32 Input=FCString::Atoi(*Client);
	//범위 체크
	if (Input<100||Input>999)
	{
		return TEXT("OUT");
	}
	UE_LOG(LogTemp, Display, TEXT("%d"), Input);
	TMap<int32,int32> Count;
	int32 Strike=0,Ball=0;
	TArray<int32> ServerNumber;
	TArray<int32> PlayerNumber;
	FString Result;
	//Server 자리수 분리
	ServerNumber.Add(Server/100);
	ServerNumber.Add((Server/10)%10);
	ServerNumber.Add(Server%10);
	//Player 자리수 분리
	PlayerNumber.Add(Input/100);
	PlayerNumber.Add((Input/10)%10);
	PlayerNumber.Add(Input%10);
	
	TSet<int32> ServerNumSet;
	for (int32 i=0;i<3;i++)
	{
		UE_LOG(LogTemp, Display, TEXT("%d : %d"), ServerNumber[i], PlayerNumber[i]);
		if (ServerNumber[i]==PlayerNumber[i])
		{
			Strike++;
		}
		else //일치하지 않는 수는 Set에 추가
		{
			ServerNumSet.Add(ServerNumber[i]);
		}
		Count.Add(PlayerNumber[i]);
		[]
	}
	if (Count.Num()<3) return TEXT("OUT"); // 플레이어의 입력에 중복 숫자가 존재하면 OUT
	
	for (int32 i:PlayerNumber)
	{
		if (ServerNumSet.Contains(i)) //Set을 이용하여 자리수 상관없이 수 비교하여 볼 판정
		{
			Ball++;
		}
	}
	// 판정 문자열 생성
	if (!Ball&&!Strike)
	{
		Result=TEXT("OUT");
	}
	else
	{
		Result=FString::Printf(TEXT("%dS,%dB\n"),Strike,Ball);
	}
	return Result;
}
