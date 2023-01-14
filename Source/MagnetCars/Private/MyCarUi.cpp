// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCarUi.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Logging/LogMacros.h"
#include "Logging/LogMacros.h"

void UMyCarUi::NativeConstruct()
{
	Super::NativeConstruct();
	if(this->StartMap)
	{
		this->StartMap->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->EndMap)
	{
		this->EndMap->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->Map)
	{
		this->Map->SetVisibility(ESlateVisibility::Hidden);
	}

	if(this->MapPositionPlayer1)
	{
		this->MapPositionPlayer1->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->MapPositionPlayer2)
	{
		this->MapPositionPlayer2->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->MapPositionPlayer3)
	{
		this->MapPositionPlayer3->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->MapPositionPlayer4)
	{
		this->MapPositionPlayer4->SetVisibility(ESlateVisibility::Hidden);
	}

	if(this->ClassementPlayer1)
	{
		this->ClassementPlayer1->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->ClassementPlayer2)
	{
		this->ClassementPlayer2->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->ClassementPlayer3)
	{
		this->ClassementPlayer3->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->ClassementPlayer4)
	{
		this->ClassementPlayer4->SetVisibility(ESlateVisibility::Hidden);
	}

	if(this->TextClassementPlayer1)
	{
		this->TextClassementPlayer1->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->TextClassementPlayer2)
	{
		this->TextClassementPlayer2->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->TextClassementPlayer3)
	{
		this->TextClassementPlayer3->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->TextClassementPlayer4)
	{
		this->TextClassementPlayer4->SetVisibility(ESlateVisibility::Hidden);
	}

	if(this->BehindPlayer2)
	{
		this->BehindPlayer2->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->BehindPlayer3)
	{
		this->BehindPlayer3->SetVisibility(ESlateVisibility::Hidden);
	}
	if(this->BehindPlayer4)
	{
		this->BehindPlayer4->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMyCarUi::SetUpClassementSetUpMap()
{
	if(ArrayPlayer.Num() == 0)return;
	/*if(this->StartMap)
	{
		this->StartMap->SetVisibility(ESlateVisibility::Visible);
	}
	if(this->EndMap)
	{
		this->EndMap->SetVisibility(ESlateVisibility::Visible);
	}*/
	if(this->Map)
	{
		this->Map->SetVisibility(ESlateVisibility::Visible);
	}
	switch (ArrayPlayer.Num())
	{
	case 1:
		default:
		if(MapPositionPlayer1 && this->ClassementPlayer1 && this->TextClassementPlayer1)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[0],this->MapPositionPlayer1);
			this->MapPositionPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[0],this->ClassementPlayer1);
			this->ClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer1->SetText(this->NamePlayer1);
			this->TextClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[0],this->TextClassementPlayer1);
		}
		break;
	case 2:
		if(MapPositionPlayer1 && this->ClassementPlayer1 && this->TextClassementPlayer1)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[0],this->MapPositionPlayer1);
			this->MapPositionPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[0],this->ClassementPlayer1);
			this->ClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer1->SetText(this->NamePlayer1);
			this->TextClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[0],this->TextClassementPlayer1);
		}
		if(MapPositionPlayer2 && this->ClassementPlayer2 && this->TextClassementPlayer2)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[1],this->MapPositionPlayer2);
			this->MapPositionPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[1],this->ClassementPlayer2);
			this->ClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer2->SetText(this->NamePlayer2);
			this->TextClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[1],this->TextClassementPlayer2);
		}
		break;
	case 3:
		if(MapPositionPlayer1 && this->ClassementPlayer1 && this->TextClassementPlayer1)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[0],this->MapPositionPlayer1);
			this->MapPositionPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[0],this->ClassementPlayer1);
			this->ClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer1->SetText(this->NamePlayer1);
			this->TextClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[0],this->TextClassementPlayer1);
		}
		if(MapPositionPlayer2 && this->ClassementPlayer2 && this->TextClassementPlayer2)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[1],this->MapPositionPlayer2);
			this->MapPositionPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[1],this->ClassementPlayer2);
			this->ClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer2->SetText(this->NamePlayer2);
			this->TextClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[1],this->TextClassementPlayer2);
		}
		if(MapPositionPlayer3 && this->ClassementPlayer3 && this->TextClassementPlayer3)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[2],this->MapPositionPlayer3);
			this->MapPositionPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[2],this->ClassementPlayer3);
			this->ClassementPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer3->SetText(this->NamePlayer3);
			this->TextClassementPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[2],this->TextClassementPlayer3);
		}
		break;
	case 4:
		if(MapPositionPlayer1 && this->ClassementPlayer1 && this->TextClassementPlayer1)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[0],this->MapPositionPlayer1);
			this->MapPositionPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[0],this->ClassementPlayer1);
			this->ClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer1->SetText(this->NamePlayer1);
			this->TextClassementPlayer1->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[0],this->TextClassementPlayer1);
		}
		if(MapPositionPlayer2 && this->ClassementPlayer2 && this->TextClassementPlayer2)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[1],this->MapPositionPlayer2);
			this->MapPositionPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[1],this->ClassementPlayer2);
			this->ClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer2->SetText(this->NamePlayer2);
			this->TextClassementPlayer2->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[1],this->TextClassementPlayer2);
		}
		if(MapPositionPlayer3 && this->ClassementPlayer3 && this->TextClassementPlayer3)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[2],this->MapPositionPlayer3);
			this->MapPositionPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[2],this->ClassementPlayer3);
			this->ClassementPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer3->SetText(this->NamePlayer3);
			this->TextClassementPlayer3->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[2],this->TextClassementPlayer3);
		}
		if(MapPositionPlayer4 && this->ClassementPlayer4 && this->TextClassementPlayer4)
		{
			this->MapImagePlayer.Add(this->ArrayPlayer[3],this->MapPositionPlayer4);
			this->MapPositionPlayer4->SetVisibility(ESlateVisibility::Visible);
			this->MapClassementPlayer.Add(this->ArrayPlayer[3],this->ClassementPlayer4);
			this->ClassementPlayer4->SetVisibility(ESlateVisibility::Visible);
			this->TextClassementPlayer4->SetText(this->NamePlayer4);
			this->TextClassementPlayer4->SetVisibility(ESlateVisibility::Visible);
			this->MapTextClassementPlayer.Add(this->ArrayPlayer[3],this->TextClassementPlayer4);
		}
		break;
	}
	this->PlayerPositionOnMap = this->PositionPlayerMap(this->ArrayPlayer);
	UpdateMap(this->PlayerPositionOnMap);
	UpdateClassement(this->PlayerPositionOnMap);
}

TArray<AMyPawnCar*> UMyCarUi::PositionPlayerMap(TArray<AMyPawnCar*> PlayerArray)
{
	TArray<AMyPawnCar*> PositionPlayer;
	PositionPlayer.SetNum(PlayerArray.Num());

	TMap<AMyPawnCar*,float> MapPlayerDistanceEndLine;

	for (AMyPawnCar* Player : PlayerArray)
	{
		if(Player == __nullptr)continue;
		MapPlayerDistanceEndLine.Add(Player, FVector::Distance(Player->GetActorLocation(),EndLine));
	}

	for (AMyPawnCar* Player : PlayerArray)
	{
		if(Player == __nullptr)continue;
		int Position = 0;
		for (auto PlayerMap : MapPlayerDistanceEndLine)
		{
			if(MapPlayerDistanceEndLine[Player] > PlayerMap.Value && Player != PlayerMap.Key)
			{
				Position++;
			}
		}
		if(PositionPlayer.Num() -1 < Position)continue;
		PositionPlayer[Position] = Player;
	}
	return PositionPlayer;
}

void UMyCarUi::UpdateMap(TArray<AMyPawnCar*> PlayerArray)
{
	TObjectPtr<UPanelSlot> StartMapSlot;
	TObjectPtr<UPanelSlot> EndMapSlot;
	StartMapSlot = this->StartMap->Slot;
	EndMapSlot = this->EndMap->Slot;

	UCanvasPanelSlot* StartMapPanel = Cast<UCanvasPanelSlot>(StartMapSlot);
	UCanvasPanelSlot* EndMapPannel = Cast<UCanvasPanelSlot>(EndMapSlot);
	for(int i = 0; i < PlayerArray.Num(); i++)
	{
		if(true)
		{
			TObjectPtr<UPanelSlot> PlayerImageMapUpdate;
			PlayerImageMapUpdate = MapImagePlayer[PlayerArray[i]]->Slot;
			UCanvasPanelSlot* PlayerImageMapUpdatePanel = Cast<UCanvasPanelSlot>(PlayerImageMapUpdate);
			if(PlayerImageMapUpdatePanel == __nullptr)continue;
			float DistanceCircuit = FVector::Distance(this->StartLine,this->EndLine);
			float DistancePlayer = FVector::Distance(PlayerArray[i]->GetActorLocation(),this->EndLine);
			float PositionOnMap = FMath::Lerp(EndMapPannel->GetPosition().Y,StartMapPanel->GetPosition().Y, DistanceCircuit / DistancePlayer	);
			PlayerImageMapUpdatePanel->SetPosition(FVector2D(StartMapPanel->GetPosition().X,PositionOnMap));
		}
		else
		{
			if(StartMapPanel == __nullptr || EndMapPannel == __nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("Connard"));
				continue;
			}
			float DistancePlayer = FVector::Distance(PlayerArray[i]->GetActorLocation(),PlayerArray[0]->GetActorLocation());
			float PositionOnMap = FMath::Lerp(StartMapPanel->GetPosition().Y,EndMapPannel->GetPosition().Y,DistancePlayer/this->DistanceMap);
			TObjectPtr<UPanelSlot> PlayerImageMapUpdate;
			PlayerImageMapUpdate = MapImagePlayer[PlayerArray[i]]->Slot;
			UCanvasPanelSlot* PlayerImageMapUpdatePanel = Cast<UCanvasPanelSlot>(PlayerImageMapUpdate);
			if(PlayerImageMapUpdatePanel == __nullptr)continue;
			PlayerImageMapUpdatePanel->SetPosition(FVector2D(StartMapPanel->GetPosition().X,PositionOnMap));
		}
	}
}

void UMyCarUi::UpdateClassement(TArray<AMyPawnCar*> PlayerArray)
{
	for(int i = 0; i < PlayerArray.Num(); i++)
	{
		TObjectPtr<UPanelSlot> PlayerClassementMapUpdate;
		PlayerClassementMapUpdate = this->MapClassementPlayer[PlayerArray[i]]->Slot;
		UCanvasPanelSlot* PlayerClassementUpdatePanel = Cast<UCanvasPanelSlot>(PlayerClassementMapUpdate);
		TObjectPtr<UPanelSlot> PlayerTextClassementMapUpdate;
		PlayerTextClassementMapUpdate = this->MapTextClassementPlayer[PlayerArray[i]]->Slot;
		UCanvasPanelSlot* PlayerTextClassementUpdatePanel = Cast<UCanvasPanelSlot>(PlayerTextClassementMapUpdate);
		if(PlayerClassementUpdatePanel == __nullptr)continue;
		if(PlayerTextClassementUpdatePanel == __nullptr)continue;
		if(i == 0)
		{
			PlayerClassementUpdatePanel->SetPosition(FVector2D(this->PositionClassement1.X,this->PositionClassement1.Y));
			PlayerTextClassementUpdatePanel->SetPosition(FVector2D(this->TextClassement1.X,this->TextClassement1.Y));
		}else if( i == 1)
		{
			PlayerClassementUpdatePanel->SetPosition(FVector2D(this->PositionClassement2.X,this->PositionClassement2.Y));
			PlayerTextClassementUpdatePanel->SetPosition(FVector2D(this->TextClassement2.X,this->TextClassement2.Y));
		}else if( i == 2)
		{
			PlayerClassementUpdatePanel->SetPosition(FVector2D(this->PositionClassement3.X,this->PositionClassement3.Y));
			PlayerTextClassementUpdatePanel->SetPosition(FVector2D(this->TextClassement3.X,this->TextClassement3.Y));
		}else if( i == 3)
		{
			PlayerClassementUpdatePanel->SetPosition(FVector2D(this->PositionClassement4.X,this->PositionClassement4.Y));
			PlayerTextClassementUpdatePanel->SetPosition(FVector2D(this->TextClassement4.X,this->TextClassement4.Y));
		}
	}
}

void UMyCarUi::UpdateLap()
{
	if(this->NumberOfLapText)
	{
		this->NumberOfLapText->SetText(FText::AsNumber(this->NumberOfLap));
	}
}

void UMyCarUi::UpdateSpeed()
{
	AMyPawnCar* MyPlayerCar = Cast<AMyPawnCar>(this->GetOwningPlayerPawn());
	if(MyPlayerCar == __nullptr) return;
	const float ActualSpeed = MyPlayerCar->CarCollision->GetPhysicsLinearVelocity().Length();
	if(this->SpeedMeterText)
	{
		this->SpeedMeterText->SetText(FText::AsNumber( FMath::CeilToInt(ActualSpeed / this->DivsionSpeedForUI)));
	}
	if(this->SpeedMeterImage)
	{
		
	}
}

void UMyCarUi::UpdateArrow()
{
	AMyPawnCar* MyPlayerCar = Cast<AMyPawnCar>(this->GetOwningPlayerPawn());
	if(MyPlayerCar == __nullptr) return;
	int i = -1;
	for (auto Element : ArrayPlayer)
	{
		i++;
		if(Element == __nullptr)continue;
		if(Element == MyPlayerCar)
		{
			i--;
			continue;
		}
		if(FVector::Distance(Element->GetActorLocation(),MyPlayerCar->GetActorLocation()) <= this->MinDistanceForArrowToSpawn)
		{
			switch (i)
			{
			case 0:
			default:
			this->BehindPlayer2->SetVisibility(ESlateVisibility::Visible);
				if(FVector::DotProduct(Element->GetActorUpVector(),MyPlayerCar->GetActorUpVector()) >= 0)
				{
					this->BehindPlayer2->SetBrushTintColor(this->ColorSameGravity);
				}
				UE_LOG(LogTemp,Warning,TEXT("test ,%f"),FMath::Acos(FVector::DotProduct(Element->GetActorForwardVector(),MyPlayerCar->GetActorForwardVector())));
				this->BehindPlayer2->SetRenderTransformAngle(FMath::Acos(FVector::DotProduct(Element->GetActorForwardVector(),MyPlayerCar->GetActorForwardVector())));
				break;
			case 1:
				this->BehindPlayer3->SetVisibility(ESlateVisibility::Visible);
				if(FVector::DotProduct(Element->GetActorUpVector(),MyPlayerCar->GetActorUpVector()) >= 0)
				{
					this->BehindPlayer3->SetBrushTintColor(this->ColorSameGravity);
				}
				this->BehindPlayer3->SetRenderTransformAngle(FMath::Acos(FVector::DotProduct(Element->GetActorForwardVector(),MyPlayerCar->GetActorForwardVector())));
				break;
			case 2:
				this->BehindPlayer4->SetVisibility(ESlateVisibility::Visible);
				if(FVector::DotProduct(Element->GetActorUpVector(),MyPlayerCar->GetActorUpVector()) >= 0)
				{
					this->BehindPlayer4->SetBrushTintColor(this->ColorSameGravity);
				}
				this->BehindPlayer4->SetRenderTransformAngle(FMath::Acos(FVector::DotProduct(Element->GetActorForwardVector(),MyPlayerCar->GetActorForwardVector())));
				break;
			}
		}
		else
		{
			switch (i)
			{
			case 0:
			default:
			this->BehindPlayer2->SetVisibility(ESlateVisibility::Hidden);
				break;
			case 1:
				this->BehindPlayer3->SetVisibility(ESlateVisibility::Hidden);
				break;
			case 2:
				this->BehindPlayer4->SetVisibility(ESlateVisibility::Hidden);
				break;
			}
		}
	}
}