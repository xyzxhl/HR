// Fill out your copyright notice in the Description page of Project Settings.


#include "Miscellaneous/HRWorldUserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Components/SizeBox.h>


void UHRWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Project enemy's world location to viewport.
	/* 将敌人在世界中的位置投影到屏幕上 */
	if (!IsValid(ActorToAttach))
	{
		RemoveFromParent();

		UE_LOG(LogTemp, Warning, TEXT("Actor is no longer valid."));
		return;
	}

	FVector2D ScreenPosition;

	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), ActorToAttach->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
