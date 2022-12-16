// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChoiceMap.h"
#include "Components/Button.h"


void UWidgetChoiceMap::NativeConstruct()
{
	Super::NativeConstruct();
	if(this->MapChoice1)
	{
		this->WhichPart1 = 0;
		this->MapChoice1->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton1Clicked);
		this->MapChoice1->SetBackgroundColor(SnowPartCirtcuit);
	}
	if(this->MapChoice2)
	{
		this->WhichPart2 = 0;
		this->MapChoice2->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton2Clicked);
		this->MapChoice2->SetBackgroundColor(SnowPartCirtcuit);
	}
	if(this->MapChoice3)
	{
		this->WhichPart3 = 0;
		this->MapChoice3->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton3Clicked);
		this->MapChoice3->SetBackgroundColor(SnowPartCirtcuit);
	}
	if(this->MapChoice4)
	{
		this->WhichPart4 = 0;
		this->MapChoice4->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton4Clicked);
		this->MapChoice4->SetBackgroundColor(SnowPartCirtcuit);
	}
	if(this->MapGeneration)
	{
		this->MapGeneration->OnClicked.AddDynamic(this,&UWidgetChoiceMap::UWidgetChoiceMap::LaunchGenerationMap);
	}
}

void UWidgetChoiceMap::MapButtonEffect_Implementation(UButton* WhichButton)
{
	if(WhichButton == this->MapChoice1)
	{
		switch (this->WhichPart1)
		{
		case 0:
			default:
			this->MapChoice1->SetBackgroundColor(SandPartCirtcuit);
			this->WhichPart1 = 1;
			break;
		case 1:
			this->MapChoice1->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart1 = 2;
			break;
		case 2:
			this->MapChoice1->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart1 = 3;
			break;
		case 3:
			this->MapChoice1->SetBackgroundColor(SnowPartCirtcuit);
			this->WhichPart1 = 0;
			break;
		}
	}else if (WhichButton == this->MapChoice2)
	{
		switch (this->WhichPart2)
		{
		case 0:
		default:
		this->MapChoice2->SetBackgroundColor(SandPartCirtcuit);
			this->WhichPart2 = 1;
			break;
		case 1:
			this->MapChoice2->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart2 = 2;
			break;
		case 2:
			this->MapChoice2->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart2 = 3;
			break;
		case 3:
			this->MapChoice2->SetBackgroundColor(SnowPartCirtcuit);
			this->WhichPart2 = 0;
			break;
		}
	}else if (WhichButton == this->MapChoice3)
	{
		switch (this->WhichPart3)
		{
		case 0:
		default:
		this->MapChoice3->SetBackgroundColor(SandPartCirtcuit);
			this->WhichPart3 = 1;
			break;
		case 1:
			this->MapChoice3->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart3 = 2;
			break;
		case 2:
			this->MapChoice3->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart3 = 3;
			break;
		case 3:
			this->MapChoice3->SetBackgroundColor(SnowPartCirtcuit);
			this->WhichPart3 = 0;
			break;
		}
	}else if (WhichButton == this->MapChoice4)
	{
		switch (this->WhichPart4)
		{
		case 0:
		default:
			this->MapChoice4->SetBackgroundColor(SandPartCirtcuit);
			this->WhichPart4 = 1;
			break;
		case 1:
			this->MapChoice4->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart4 = 2;
			break;
		case 2:
			this->MapChoice4->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart4 = 3;
			break;
		case 3:
			this->MapChoice4->SetBackgroundColor(SnowPartCirtcuit);
			this->WhichPart4 = 0;
			break;
		}
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

void UWidgetChoiceMap::LaunchGenerationMap_Implementation()
{
	if(this->MapGeneration == nullptr) return;
	if(this->LoadCircuit == nullptr) return;
	this->LoadCircuit->LoadCircuit();
}

