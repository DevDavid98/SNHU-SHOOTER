// Copyright Epic Games, Inc. All Rights Reserved.

#include "theShooterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "PerlinProcTerrain.h"

AtheShooterProjectile::AtheShooterProjectile() 
{
	// Creates the sphere collision component
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);


	// Puts the collision componenton the projectile
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	// detects if the component is hit by something
	CollisionComp->OnComponentHit.AddDynamic(this, &AtheShooterProjectile::OnHit);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Sets the root component
	RootComponent = CollisionComp;

	// Creates the attributes of the projectile
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Lifespan of the projectile
	InitialLifeSpan = 4.0f;

	// Sets up the ball mesh component and the root comp of the ball
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");
	RootComponent = CollisionComp;
	ballMesh->SetupAttachment(CollisionComp);

}

void AtheShooterProjectile::BeginPlay()
{
	// Soon as the game starts 
	Super::BeginPlay();

	//Picks a random color and assigns the coloe to randColor
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	// Creates the matieral in the editor
	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);

	// Sets the matieral to the randColor color
	if (dmiMat)
	{
		ballMesh->SetMaterial(0, dmiMat);
		dmiMat->SetVectorParameterValue("ProjColor", randColor);
	}

	// if the color is not assigned throw off an error message
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SMI MAT not applied in details panel"));
		return;
	}
	
}


void AtheShooterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if it is hit 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	if (OtherActor != nullptr)
	{

		if (colorP){
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(-20.f,0.f,0.f),FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
			particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), randColor);
			ballMesh->DestroyComponent();
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}


		// chooses which image to use in the 2x2 decal
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);

		
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);

		// CAST BALL TO TERRAIN
		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);

		// IF procTerrain CALL ALTERMESH at the impactpoint
		if (procTerrain)
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}

		Decal->SetLifeSpan(5.0f);

		
	}
}