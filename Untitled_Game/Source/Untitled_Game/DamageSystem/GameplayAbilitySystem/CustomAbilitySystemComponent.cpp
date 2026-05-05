// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAbilitySystemComponent.h"

#include "PlayerCharacter.h"


// Sets default values for this component's properties
UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCustomAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (!PlayerCharacter)
	{
		return;
	}
	//Maybe needed
}


// Called every frame
void UCustomAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

