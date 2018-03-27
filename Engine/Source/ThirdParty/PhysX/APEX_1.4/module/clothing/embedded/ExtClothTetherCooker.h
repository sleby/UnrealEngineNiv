/*
 * Copyright (c) 2008-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  


#ifndef PX_PHYSICS_EXTENSIONS_CLOTH_TETHER_COOKER_H
#define PX_PHYSICS_EXTENSIONS_CLOTH_TETHER_COOKER_H

#include "ExtClothConfig.h"
#include "PxClothMeshDesc.h"

#if PX_DOXYGEN == 0
namespace nvidia
{
#endif
	
struct PxClothSimpleTetherCookerImpl;

class PxClothSimpleTetherCooker
{
public:
	/**
	\brief Compute tether data from PxClothMeshDesc with simple distance measure.
	\details The tether constraint in PxCloth requires rest distance and anchor index to be precomputed during cooking time.
	This cooker computes a simple Euclidean distance to closest anchor point.
	The Euclidean distance measure works reasonably for flat cloth and flags and computation time is very fast.
	With this cooker, there is only one tether anchor point per particle.
	\see PxClothTetherGeodesicCooker for more accurate distance estimation.
	\param desc The cloth mesh descriptor prepared for cooking
	*/
	PxClothSimpleTetherCooker(const PxClothMeshDesc &desc);
	~PxClothSimpleTetherCooker();

	/**
	\brief Returns cooker status
	\details This function returns cooker status after cooker computation is done.
	A non-zero return value indicates a failure.
	*/
	uint32_t getCookerStatus() const;

    /** 
	\brief Returns computed tether data.
	\details This function returns anchor indices for each particle as well as desired distance between the tether anchor and the particle.
	The user buffers should be at least as large as number of particles.
	*/
    void getTetherData(uint32_t* userTetherAnchors, float* userTetherLengths) const;

private:
	PxClothSimpleTetherCookerImpl* mImpl;

};


struct PxClothGeodesicTetherCookerImpl;

class PxClothGeodesicTetherCooker
{
public:
	/**
	\brief Compute tether data from PxClothMeshDesc using geodesic distance.
	\details The tether constraint in PxCloth requires rest distance and anchor index to be precomputed during cooking time.
	The provided tether cooker computes optimal tether distance with geodesic distance computation.
	For curved and complex meshes, geodesic distance provides the best behavior for tether constraints.
	But the cooking time is slower than the simple cooker.
	\see PxClothSimpleTetherCooker
	\param desc The cloth mesh descriptor prepared for cooking
	\note The geodesic distance is optimized to work for intended use in tether constraint.  
	This is by no means a general purpose geodesic computation code for arbitrary meshes.
	\note The geodesic cooker does not work with non-manifold input such as edges having more than two incident triangles, 
	or adjacent triangles following inconsitent winding order (e.g. clockwise vs counter-clockwise). 
	*/
	PxClothGeodesicTetherCooker(const PxClothMeshDesc &desc);
	~PxClothGeodesicTetherCooker();

	/**
	\brief Returns cooker status
	\details This function returns cooker status after cooker computation is done.
	A non-zero return value indicates a failure, 1 for non-manifold and 2 for inconsistent winding.
	*/
	uint32_t getCookerStatus() const;

	/**
	\brief Returns number of tether anchors per particle
	\note Returned number indicates the maximum anchors.  
	If some particles are assigned fewer anchors, the anchor indices will be uint32_t(-1) 
	\note If there is no attached point in the input mesh descriptor, this will return 0 and no tether data will be generated.
	*/
	uint32_t getNbTethersPerParticle() const;

    /** 
	\brief Returns computed tether data.
	\details This function returns anchor indices for each particle as well as desired distance between the tether anchor and the particle.
	The user buffers should be at least as large as number of particles * number of tethers per particle.
	\see getNbTethersPerParticle()
	*/
    void getTetherData(uint32_t* userTetherAnchors, float* userTetherLengths) const;

private:
	PxClothGeodesicTetherCookerImpl* mImpl;

};


#if PX_DOXYGEN == 0
} // namespace nvidia
#endif

#endif // PX_PHYSICS_EXTENSIONS_CLOTH_TETHER_COOKER_H
