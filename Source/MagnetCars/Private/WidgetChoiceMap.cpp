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
		this->MapChoice1->SetBackgroundColor(CanyonPartCirtcuit);
	}
	if(this->MapChoice2)
	{
		this->WhichPart2 = 0;
		this->MapChoice2->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton2Clicked);
		this->MapChoice2->SetBackgroundColor(CanyonPartCirtcuit);
	}
	if(this->MapChoice3)
	{
		this->WhichPart3 = 0;
		this->MapChoice3->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton3Clicked);
		this->MapChoice3->SetBackgroundColor(CanyonPartCirtcuit);
	}
	if(this->MapChoice4)
	{
		this->WhichPart4 = 0;
		this->MapChoice4->OnClicked.AddDynamic(this,&UWidgetChoiceMap::MapButton4Clicked);
		this->MapChoice4->SetBackgroundColor(CanyonPartCirtcuit);
	}
	if(this->MapGeneration)
	{
		this->MapGeneration->OnClicked.AddDynamic(this,&UWidgetChoiceMap::UWidgetChoiceMap::LaunchGenerationMap);
	}
}

void UWidgetChoiceMap::MapButtonInitialisation_Implementation()
{
	// This switch will update all the buttons at the start in case the player hit creation first
	switch (this->WhichBasePartCircuit)
	{
	case Sand:
	default:
		this->WhichPart1 = 0;
		this->WhichPart2 = 0;
		this->WhichPart3 = 0;
		this->WhichPart4 = 0;
		break;
	case City:
		this->WhichPart1 = 1;
		this->WhichPart2 = 1;
		this->WhichPart3 = 1;
		this->WhichPart4 = 1;
		break;
	case InnerCity:
		this->WhichPart1 = 2;
		this->WhichPart2 = 2;
		this->WhichPart3 = 2;
		this->WhichPart4 = 2;
		break;
	case Canyon:
		this->WhichPart1 = 3;
		this->WhichPart2 = 3;
		this->WhichPart3 = 3;
		this->WhichPart4 = 3;
		break;
	}
	switch (this->WhichPart1)
	{
	case 0:
	default:
	this->MapChoice1->SetBackgroundColor(SandPartCirtcuit);
		this->WhichPart1 = 1;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
		if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeSand;
		break;
	case 1:
		this->MapChoice1->SetBackgroundColor(CityPartCirtcuit);
		this->WhichPart1 = 2;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
		if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeCity;
		break;
	case 2:
		this->MapChoice1->SetBackgroundColor(InnerCityPartCirtcuit);
		this->WhichPart1 = 3;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
		if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeInnerCity;
		break;
	case 3:
		this->MapChoice1->SetBackgroundColor(CanyonPartCirtcuit);
		this->WhichPart1 = 0;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
		if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeCanyon;
		break;
	}
	switch (this->WhichPart2)
	{
	case 0:
	default:
	this->MapChoice2->SetBackgroundColor(SandPartCirtcuit);
		this->WhichPart2 = 1;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
		if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeSand;
		break;
	case 1:
		this->MapChoice2->SetBackgroundColor(CityPartCirtcuit);
		this->WhichPart2 = 2;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
		if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeCity;
		break;
	case 2:
		this->MapChoice2->SetBackgroundColor(InnerCityPartCirtcuit);
		this->WhichPart2 = 3;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
		if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeInnerCity;
		break;
	case 3:
		this->MapChoice2->SetBackgroundColor(CanyonPartCirtcuit);
		this->WhichPart2 = 0;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
		if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeCanyon;
		break;
	}
	switch (this->WhichPart3)
	{
	case 0:
	default:
	this->MapChoice3->SetBackgroundColor(SandPartCirtcuit);
		this->WhichPart3 = 1;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
		if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeSand;
		break;
	case 1:
		this->MapChoice3->SetBackgroundColor(CityPartCirtcuit);
		this->WhichPart3 = 2;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
		if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeCity;
		break;
	case 2:
		this->MapChoice3->SetBackgroundColor(InnerCityPartCirtcuit);
		this->WhichPart3 = 3;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
		if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeInnerCity;
		break;
	case 3:
		this->MapChoice3->SetBackgroundColor(CanyonPartCirtcuit);
		this->WhichPart3 = 0;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
		if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeCanyon;
		break;
	}
	switch (this->WhichPart4)
	{
	case 0:
	default:
		this->MapChoice4->SetBackgroundColor(SandPartCirtcuit);
		this->WhichPart4 = 1;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
		if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeSand;
		break;
	case 1:
		this->MapChoice4->SetBackgroundColor(CityPartCirtcuit);
		this->WhichPart4 = 2;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
		if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeCity;
		break;
	case 2:
		this->MapChoice4->SetBackgroundColor(InnerCityPartCirtcuit);
		this->WhichPart4 = 3;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
		if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeInnerCity;
		break;
	case 3:
		this->MapChoice4->SetBackgroundColor(CanyonPartCirtcuit);
		this->WhichPart4 = 0;
		if(LoadCircuit == nullptr) return;
		if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
		if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
		this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeCanyon;
		break;
	}
}



void UWidgetChoiceMap::MapButtonEffect_Implementation(UButton* WhichButton)
{
	// This switch will update the button clicked with the color of the new part chosen
	if(WhichButton == this->MapChoice1)
	{
		switch (this->WhichPart1)
		{
		case 0:
			default:
			this->MapChoice1->SetBackgroundColor(SandPartCirtcuit);
			this->WhichPart1 = 1;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
			if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeSand;
			break;
		case 1:
			this->MapChoice1->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart1 = 2;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
			if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeCity;
			break;
		case 2:
			this->MapChoice1->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart1 = 3;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
			if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeInnerCity;
			break;
		case 3:
			this->MapChoice1->SetBackgroundColor(CanyonPartCirtcuit);
			this->WhichPart1 = 0;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif0) return;
			if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif0] = this->LoadCircuit->PartCircuitTypeCanyon;
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
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
			if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeSand;
			break;
		case 1:
			this->MapChoice2->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart2 = 2;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
			if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeCity;
			break;
		case 2:
			this->MapChoice2->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart2 = 3;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
			if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeInnerCity;
			break;
		case 3:
			this->MapChoice2->SetBackgroundColor(CanyonPartCirtcuit);
			this->WhichPart2 = 0;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif1) return;
			if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif1] = this->LoadCircuit->PartCircuitTypeCanyon;
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
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
			if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeSand;
			break;
		case 1:
			this->MapChoice3->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart3 = 2;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
			if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeCity;
			break;
		case 2:
			this->MapChoice3->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart3 = 3;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
			if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeInnerCity;
			break;
		case 3:
			this->MapChoice3->SetBackgroundColor(CanyonPartCirtcuit);
			this->WhichPart3 = 0;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif2) return;
			if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif2] = this->LoadCircuit->PartCircuitTypeCanyon;
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
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
			if(this->LoadCircuit->PartCircuitTypeSand == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeSand;
			break;
		case 1:
			this->MapChoice4->SetBackgroundColor(CityPartCirtcuit);
			this->WhichPart4 = 2;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
			if(this->LoadCircuit->PartCircuitTypeCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeCity;
			break;
		case 2:
			this->MapChoice4->SetBackgroundColor(InnerCityPartCirtcuit);
			this->WhichPart4 = 3;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
			if(this->LoadCircuit->PartCircuitTypeInnerCity == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeInnerCity;
			break;
		case 3:
			this->MapChoice4->SetBackgroundColor(CanyonPartCirtcuit);
			this->WhichPart4 = 0;
			if(LoadCircuit == nullptr) return;
			if(LoadCircuit->OrderPartCircuit.Num() < this->WhichPartYouCanModif3) return;
			if(this->LoadCircuit->PartCircuitTypeCanyon == nullptr) return;
			this->LoadCircuit->OrderPartCircuit[this->WhichPartYouCanModif3] = this->LoadCircuit->PartCircuitTypeCanyon;
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
	this->MapChoice1->SetIsEnabled(false);
	this->MapChoice2->SetIsEnabled(false);
	this->MapChoice3->SetIsEnabled(false);
	this->MapChoice4->SetIsEnabled(false);
	this->MapGeneration->SetIsEnabled(false);
	this->MapChoice1->SetVisibility(ESlateVisibility::Hidden);
	this->MapChoice2->SetVisibility(ESlateVisibility::Hidden);
	this->MapChoice3->SetVisibility(ESlateVisibility::Hidden);
	this->MapChoice4->SetVisibility(ESlateVisibility::Hidden);
	this->MapGeneration->SetVisibility(ESlateVisibility::Hidden);
}

