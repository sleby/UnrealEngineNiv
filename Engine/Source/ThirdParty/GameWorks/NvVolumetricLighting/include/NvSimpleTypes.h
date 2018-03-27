// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2014 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.

#ifndef NV_NVFOUNDATION_NVSIMPLETYPES_H
#define NV_NVFOUNDATION_NVSIMPLETYPES_H

/** \addtogroup foundation
  @{
*/

// Platform specific types:
// Design note: Its OK to use int for general loop variables and temps.

#include "NvPreprocessor.h"
#if NV_VC
#pragma warning(push)
#pragma warning(disable : 4668) // suppressing warning generated by Microsoft Visual Studio when including this standard
// header
#endif

#if NV_LINUX
#define __STDC_LIMIT_MACROS
#endif

#include <stdint.h>
#if NV_VC
#pragma warning(pop)
#endif
// Type ranges

// These are here because we sometimes have non-IEEE compliant platforms to deal with.
// Removal is under consideration (issue GWSD-34)

#define NV_MAX_F32 3.4028234663852885981170418348452e+38F
// maximum possible float value
#define NV_MAX_F64 DBL_MAX // maximum possible double value

#define NV_EPS_F32 FLT_EPSILON // maximum relative error of float rounding
#define NV_EPS_F64 DBL_EPSILON // maximum relative error of double rounding

#define NV_MAX_REAL NV_MAX_F32
#define NV_EPS_REAL NV_EPS_F32
#define NV_NORMALIZATION_EPSILON float(1e-20f)

/** @} */
#endif // #ifndef NV_NVFOUNDATION_NVSIMPLETYPES_H
