// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoiceMap.h"
#include "Components/Button.h"


void UWidgetChoiceMap::NativeConstruct()
{
	Super::NativeConstruct();
	if(MapChoice1)
	{
		MapChoice1->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton1Clicked);
	}
	if(MapChoice2)
	{
		MapChoice2->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton2Clicked);
	}
	if(MapChoice3)
	{
		MapChoice3->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton3Clicked);
	}
	if(MapChoice4)
	{
		MapChoice4->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton4Clicked);
	}
}

void UWidgetChoiceMap::MapButtonEffect_Implementation(UButton* WhichButton)
{
	if(WhichButton == this->MapChoice1)
	{
		UE_LOG(LogTemp,Warning,TEXT("Gne?"));
		MapChoice1->SetBackgroundColor(FLinearColor::Black);
	}else if (WhichButton== this->MapChoice2)
	{
		MapChoice2->SetBackgroundColor(FLinearColor::Black);
	}else if (WhichButton== this->MapChoice3)
	{
		MapChoice3->SetBackgroundColor(FLinearColor::Black);
	}else if (WhichButton == this->MapChoice4)
	{
		MapChoice4->SetBackgroundColor(FLinearColor::Black);
	}
}

void UWidgetChoiceMap::MapButton1Clicked_Implementation()
{
	if(this->MapChoice1 == nullptr) return;
	MapButtonEffect(this->MapChoice1);
}

void UWidgetChoiceMap::MapButton2Clicked_Implementation()
{
	if(this->MapChoice1 == nullptr) return;
	MapButtonEffect(this->MapChoice2);
}

void UWidgetChoiceMap::MapButton3Clicked_Implementation()
{
	if(this->MapChoice1 == nullptr) return;
	MapButtonEffect(this->MapChoice3);
}

void UWidgetChoiceMap::MapButton4Clicked_Implementation()
{
	if(this->MapChoice1 == nullptr) return;
	MapButtonEffect(this->MapChoice4);
}