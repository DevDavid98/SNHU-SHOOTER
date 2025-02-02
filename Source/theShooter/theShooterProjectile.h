// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "theShooterProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class AtheShooterProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;



	// CREATES A componenet for the BP called ballMesh and is able to be edited in the components editor in unreal
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh;


	// Create the BASE MATERIAL OF THE COMP
	UPROPERTY(EditAnywhere)
		UMaterial* baseMat;

	// Creates a variable called randColor
	UPROPERTY(EditAnywhere)
		FLinearColor randColor;


	// Adds the ability to add different materials to the projectile
	UPROPERTY(EditAnywhere)
		UMaterialInterface* projMat;

	// Changes the material to a color 
	UPROPERTY(EditAnywhere)
		UMaterialInstanceDynamic* dmiMat;



	UPROPERTY(EditAnywhere)
		UNiagaraSystem* colorP;



public:
	AtheShooterProjectile();


protected:
	virtual void BeginPlay();


public:

	// called when projectile hits something and is a function
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	// Returns CollisionComp subobject
	USphereComponent* GetCollisionComp() const { return CollisionComp; }


	// Returns ProjectileMovement subobject
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

