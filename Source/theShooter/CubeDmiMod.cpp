// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMOD.h"
#include "theShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ACubeDMIMOD::ACubeDMIMOD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");


	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

	boxArrow = CreateDefaultSubobject<UArrowComponent>("Cube Arrow");
	boxArrow->SetupAttachment(cubeMesh);

}

// Called when the game starts or when spawned
void ACubeDMIMOD::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMOD::OnOverlapBegin);
	if (baseMAT)
	{
		dmiMAT = UMaterialInstanceDynamic::Create(baseMAT, this);

	}

	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMAT);
	}

}

// Called every frame
void ACubeDMIMOD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACubeDMIMOD::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AtheShooterCharacter* overlappedActor = Cast<AtheShooterCharacter>(OtherActor);

	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);


		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.f);
		if (dmiMAT)
		{
			dmiMAT->SetVectorParameterValue("Color", randColor);
			dmiMAT->SetScalarParameterValue("Darkness", ranNumX);
		}

	}


}

