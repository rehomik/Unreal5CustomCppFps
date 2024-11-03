// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AEngineDic1CppCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponDrop, AEngineDic1CppCharacter*, DropCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponSwap, UTP_WeaponComponent*, PreviousWeapon, AEngineDic1CppCharacter*, SwapCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponReload, int, MaxBullet);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENGINEDIC1CPP_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditAnyWhere, Category=Projectile)
	TSubclassOf<class AEngineDic1CppProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* WeaponDropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnWeaponDrop OnWeaponDrop;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnWeaponSwap OnWeaponSwap;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnWeaponReload OnWeaponReload;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	int bulletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxBulletCount;

public :

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(AEngineDic1CppCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool DetachWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void setCurrentBulletCount(int count);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	void Drop();

	void SwapWeapon(UTP_WeaponComponent* previousWeapon);

	void Reload();

protected:
	/** Called when the game starts */
	UFUNCTION()
	virtual void BeginPlay() override;

	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AEngineDic1CppCharacter* Character;
};
