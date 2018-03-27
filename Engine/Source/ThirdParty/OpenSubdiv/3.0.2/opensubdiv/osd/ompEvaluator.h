//
//   Copyright 2015 Pixar
//
//   Licensed under the Apache License, Version 2.0 (the "Apache License")
//   with the following modification; you may not use this file except in
//   compliance with the Apache License and the following modification to it:
//   Section 6. Trademarks. is deleted and replaced with:
//
//   6. Trademarks. This License does not grant permission to use the trade
//      names, trademarks, service marks, or product names of the Licensor
//      and its affiliates, except as required to comply with Section 4(c) of
//      the License and to reproduce the content of the NOTICE file.
//
//   You may obtain a copy of the Apache License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the Apache License with the above modification is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//   KIND, either express or implied. See the Apache License for the specific
//   language governing permissions and limitations under the Apache License.
//

#ifndef OPENSUBDIV3_OSD_OMP_EVALUATOR_H
#define OPENSUBDIV3_OSD_OMP_EVALUATOR_H

#include "../version.h"

#include <cstddef>
#include "../osd/types.h"
#include "../osd/bufferDescriptor.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

namespace Osd {

class OmpEvaluator {
public:
    /// ----------------------------------------------------------------------
    ///
    ///   Stencil evaluations with StencilTable
    ///
    /// ----------------------------------------------------------------------

    /// \brief Generic static eval stencils function. This function has a same
    ///        signature as other device kernels have so that it can be called
    ///        in the same way from OsdMesh template interface.
    ///
    /// @param srcBuffer      Input primvar buffer.
    ///                       must have BindCpuBuffer() method returning a
    ///                       const float pointer for read
    ///
    /// @param srcDesc        vertex buffer descriptor for the input buffer
    ///
    /// @param dstBuffer      Output primvar buffer
    ///                       must have BindCpuBuffer() method returning a
    ///                       float pointer for write
    ///
    /// @param dstDesc        vertex buffer descriptor for the output buffer
    ///
    /// @param stencilTable   Far::StencilTable or equivalent
    ///
    /// @param instance       not used in the omp kernel
    ///                       (declared as a typed pointer to prevent
    ///                        undesirable template resolution)
    ///
    /// @param deviceContext  not used in the omp kernel
    ///
    template <typename SRC_BUFFER, typename DST_BUFFER, typename STENCIL_TABLE>
    static bool EvalStencils(
        SRC_BUFFER *srcBuffer, BufferDescriptor const &srcDesc,
        DST_BUFFER *dstBuffer, BufferDescriptor const &dstDesc,
        STENCIL_TABLE const *stencilTable,
        const OmpEvaluator *instance = NULL,
        void * deviceContext = NULL) {

        (void)instance;       // unused
        (void)deviceContext;  // unused

        return EvalStencils(srcBuffer->BindCpuBuffer(), srcDesc,
                            dstBuffer->BindCpuBuffer(), dstDesc,
                            &stencilTable->GetSizes()[0],
                            &stencilTable->GetOffsets()[0],
                            &stencilTable->GetControlIndices()[0],
                            &stencilTable->GetWeights()[0],
                            /*start = */ 0,
                            /*end   = */ stencilTable->GetNumStencils());
    }

    /// \brief Static eval stencils function which takes raw CPU pointers for
    ///        input and output.
    ///
    /// @param src            Input primvar pointer. An offset of srcDesc
    ///                       will be applied internally (i.e. the pointer
    ///                       should not include the offset)
    ///
    /// @param srcDesc        vertex buffer descriptor for the input buffer
    ///
    /// @param dst            Output primvar pointer. An offset of dstDesc
    ///                       will be applied internally.
    ///
    /// @param dstDesc        vertex buffer descriptor for the output buffer
    ///
    /// @param sizes          pointer to the sizes buffer of the stencil table
    ///                       to apply for the range [start, end)
    ///
    /// @param offsets        pointer to the offsets buffer of the stencil table
    ///
    /// @param indices        pointer to the indices buffer of the stencil table
    ///
    /// @param weights        pointer to the weights buffer of the stencil table
    ///
    /// @param start          start index of stencil table
    ///
    /// @param end            end index of stencil table
    ///
    static bool EvalStencils(
        const float *src,  BufferDescriptor const &srcDesc,
        float *dst,        BufferDescriptor const &dstDesc,
        const int * sizes,
        const int * offsets,
        const int * indices,
        const float * weights,
        int start, int end);

    /// \brief Generic static eval stencils function with derivatives.
    ///        This function has a same signature as other device kernels
    ///        have so that it can be called in the same way from OsdMesh
    ///        template interface.
    ///
    /// @param srcBuffer      Input primvar buffer.
    ///                       must have BindCpuBuffer() method returning a
    ///                       const float pointer for read
    ///
    /// @param srcDesc        vertex buffer descriptor for the input buffer
    ///
    /// @param dstBuffer      Output primvar buffer
    ///                       must have BindCpuBuffer() method returning a
    ///                       float pointer for write
    ///
    /// @param dstDesc        vertex buffer descriptor for the output buffer
    ///
    /// @param duBuffer       Output U-derivative buffer
    ///                       must have BindCpuBuffer() method returning a
    ///                       float pointer for write
    ///
    /// @param duDesc         vertex buffer descriptor for the output buffer
    ///
    /// @param dvBuffer       Output V-derivative buffer
    ///                       must have BindCpuBuffer() method returning a
    ///                       float pointer for write
    ///
    /// @param dvDesc         vertex buffer descriptor for the output buffer
    ///
    /// @param stencilTable   Far::StencilTable or equivalent
    ///
    /// @param instance       not used in the omp kernel
    ///                       (declared as a typed pointer to prevent
    ///                        undesirable template resolution)
    ///
    /// @param deviceContext  not used in the omp kernel
    ///
    template <typename SRC_BUFFER, typename DST_BUFFER, typename STENCIL_TABLE>
    static bool EvalStencils(
        SRC_BUFFER *srcBuffer, BufferDescriptor const &srcDesc,
        DST_BUFFER *dstBuffer, BufferDescriptor const &dstDesc,
        DST_BUFFER *duBuffer,  BufferDescriptor const &duDesc,
        DST_BUFFER *dvBuffer,  BufferDescriptor const &dvDesc,
        STENCIL_TABLE const *stencilTable,
        const OmpEvaluator *instance = NULL,
        void * deviceContext = NULL) {

        (void)instance;       // unused
        (void)deviceContext;  // unused

        return EvalStencils(srcBuffer->BindCpuBuffer(), srcDesc,
                            dstBuffer->BindCpuBuffer(), dstDesc,
                            duBuffer->BindCpuBuffer(),  duDesc,
                            dvBuffer->BindCpuBuffer(),  dvDesc,
                            &stencilTable->GetSizes()[0],
                            &stencilTable->GetOffsets()[0],
                            &stencilTable->GetControlIndices()[0],
                            &stencilTable->GetWeights()[0],
                            &stencilTable->GetDuWeights()[0],
                            &stencilTable->GetDvWeights()[0],
                            /*start = */ 0,
                            /*end   = */ stencilTable->GetNumStencils());
    }

    /// \brief Static eval stencils function with derivatives, which takes
    ///        raw CPU pointers for input and output.
    ///
    /// @param src            Input primvar pointer. An offset of srcDesc
    ///                       will be applied internally (i.e. the pointer
    ///                       should not include the offset)
    ///
    /// @param srcDesc        vertex buffer descriptor for the input buffer
    ///
    /// @param dst            Output primvar pointer. An offset of dstDesc
    ///                       will be applied internally.
    ///
    /// @param dstDesc        vertex buffer descriptor for the output buffer
    ///
    /// @param du             Output U-derivatives pointer. An offset of
    ///                       duDesc will be applied internally.
    ///
    /// @param duDesc         vertex buffer descriptor for the output buffer
    ///
    /// @param dv             Output V-derivatives pointer. An offset of
    ///                       dvDesc will be applied internally.
    ///
    /// @param dvDesc         vertex buffer descriptor for the output buffer
    ///
    /// @param sizes          pointer to the sizes buffer of the stencil table
    ///
    /// @param offsets        pointer to the offsets buffer of the stencil table
    ///
    /// @param indices        pointer to the indices buffer of the stencil table
    ///
    /// @param weights        pointer to the weights buffer of the stencil table
    ///
    /// @param duWeights      pointer to the du-weights buffer of the stencil table
    ///
    /// @param dvWeights      pointer to the dv-weights buffer of the stencil table
    ///
    /// @param start          start index of stencil table
    ///
    /// @param end            end index of stencil table
    ///
    static bool EvalStencils(
        const float *src, BufferDescriptor const &srcDesc,
        float *dst,       BufferDescriptor const &dstDesc,
        float *du,        BufferDescriptor const &duDesc,
        float *dv,        BufferDescriptor const &dvDesc,
        const int * sizes,
        const int * offsets,
        const int * indices,
        const float * weights,
        const float * duWeights,
        const float * dvWeights,
        int start, int end);

    /// ----------------------------------------------------------------------
    ///
    ///   Limit evaluations with PatchTable
    ///
    /// ----------------------------------------------------------------------

    /// \brief Generic limit eval function. This function has a same
    ///        signature as other device kernels have so that it can be called
    ///        in the same way.
    ///
    /// @param srcBuffer        Input primvar buffer.
    ///                         must have BindCpuBuffer() method returning a
    ///                         const float pointer for read
    ///
    /// @param srcDesc          vertex buffer descriptor for the input buffer
    ///
    /// @param dstBuffer        Output primvar buffer
    ///                         must have BindCpuBuffer() method returning a
    ///                         float pointer for write
    ///
    /// @param dstDesc          vertex buffer descriptor for the output buffer
    ///
    /// @param numPatchCoords   number of patchCoords.
    ///
    /// @param patchCoords      array of locations to be evaluated.
    ///
    /// @param patchTable       CpuPatchTable or equivalent
    ///                         XXX: currently Far::PatchTable can't be used
    ///                              due to interface mismatch
    ///
    /// @param instance         not used in the omp evaluator
    ///
    /// @param deviceContext    not used in the omp evaluator
    ///
    template <typename SRC_BUFFER, typename DST_BUFFER,
              typename PATCHCOORD_BUFFER, typename PATCH_TABLE>
    static bool EvalPatches(
        SRC_BUFFER *srcBuffer, BufferDescriptor const &srcDesc,
        DST_BUFFER *dstBuffer, BufferDescriptor const &dstDesc,
        int numPatchCoords,
        PATCHCOORD_BUFFER *patchCoords,
        PATCH_TABLE *patchTable,
        OmpEvaluator const *instance = NULL,
        void * deviceContext = NULL) {

        (void)instance;       // unused
        (void)deviceContext;  // unused

        return EvalPatches(srcBuffer->BindCpuBuffer(), srcDesc,
                           dstBuffer->BindCpuBuffer(), dstDesc,
                           numPatchCoords,
                           (const PatchCoord*)patchCoords->BindCpuBuffer(),
                           patchTable->GetPatchArrayBuffer(),
                           patchTable->GetPatchIndexBuffer(),
                           patchTable->GetPatchParamBuffer());
    }

    /// \brief Generic limit eval function with derivatives. This function has
    ///        a same signature as other device kernels have so that it can be
    ///        called in the same way.
    ///
    /// @param srcBuffer        Input primvar buffer.
    ///                         must have BindCpuBuffer() method returning a
    ///                         const float pointer for read
    ///
    /// @param srcDesc          vertex buffer descriptor for the input buffer
    ///
    /// @param dstBuffer        Output primvar buffer
    ///                         must have BindCpuBuffer() method returning a
    ///                         float pointer for write
    ///
    /// @param dstDesc          vertex buffer descriptor for the output buffer
    ///
    /// @param duBuffer         Output U-derivatives buffer
    ///                         must have BindCpuBuffer() method returning a
    ///                         float pointer for write
    ///
    /// @param duDesc           vertex buffer descriptor for the duBuffer
    ///
    /// @param dvBuffer         Output V-derivatives buffer
    ///                         must have BindCpuBuffer() method returning a
    ///                         float pointer for write
    ///
    /// @param dvDesc           vertex buffer descriptor for the dvBuffer
    ///
    /// @param numPatchCoords   number of patchCoords.
    ///
    /// @param patchCoords      array of locations to be evaluated.
    ///
    /// @param patchTable       CpuPatchTable or equivalent
    ///                         XXX: currently Far::PatchTable can't be used
    ///                              due to interface mismatch
    ///
    /// @param instance         not used in the omp evaluator
    ///
    /// @param deviceContext    not used in the omp evaluator
    ///
    template <typename SRC_BUFFER, typename DST_BUFFER,
              typename PATCHCOORD_BUFFER, typename PATCH_TABLE>
    static bool EvalPatches(
        SRC_BUFFER *srcBuffer, BufferDescriptor const &srcDesc,
        DST_BUFFER *dstBuffer, BufferDescriptor const &dstDesc,
        DST_BUFFER *duBuffer,  BufferDescriptor const &duDesc,
        DST_BUFFER *dvBuffer,  BufferDescriptor const &dvDesc,
        int numPatchCoords,
        PATCHCOORD_BUFFER *patchCoords,
        PATCH_TABLE *patchTable,
        OmpEvaluator const *instance = NULL,
        void * deviceContext = NULL) {
        (void)instance;       // unused
        (void)deviceContext;  // unused

        // XXX: PatchCoords is somewhat abusing vertex primvar buffer interop.
        //      ideally all buffer classes should have templated by datatype
        //      so that downcast isn't needed there.
        //      (e.g. Osd::CpuBuffer<PatchCoord> )
        //
        return EvalPatches(srcBuffer->BindCpuBuffer(), srcDesc,
                           dstBuffer->BindCpuBuffer(), dstDesc,
                           duBuffer->BindCpuBuffer(),  duDesc,
                           dvBuffer->BindCpuBuffer(),  dvDesc,
                           numPatchCoords,
                           (const PatchCoord*)patchCoords->BindCpuBuffer(),
                           patchTable->GetPatchArrayBuffer(),
                           patchTable->GetPatchIndexBuffer(),
                           patchTable->GetPatchParamBuffer());
    }

    /// \brief Static limit eval function. It takes an array of PatchCoord
    ///        and evaluate limit values on given PatchTable.
    ///
    /// @param src              Input primvar pointer. An offset of srcDesc
    ///                         will be applied internally (i.e. the pointer
    ///                         should not include the offset)
    ///
    /// @param srcDesc          vertex buffer descriptor for the input buffer
    ///
    /// @param dst              Output primvar pointer. An offset of dstDesc
    ///                         will be applied internally.
    ///
    /// @param dstDesc          vertex buffer descriptor for the output buffer
    ///
    /// @param numPatchCoords   number of patchCoords.
    ///
    /// @param patchCoords      array of locations to be evaluated.
    ///
    /// @param patchArrays      an array of Osd::PatchArray struct
    ///                         indexed by PatchCoord::arrayIndex
    ///
    /// @param patchIndexBuffer an array of patch indices
    ///                         indexed by PatchCoord::vertIndex
    ///
    /// @param patchParamBuffer an array of Osd::PatchParam struct
    ///                         indexed by PatchCoord::patchIndex
    ///
    static bool EvalPatches(
        const float *src, BufferDescriptor const &srcDesc,
        float *dst,       BufferDescriptor const &dstDesc,
        int numPatchCoords,
        const PatchCoord *patchCoords,
        const PatchArray *patchArrays,
        const int *patchIndexBuffer,
        const PatchParam *patchParamBuffer);

    /// \brief Static limit eval function. It takes an array of PatchCoord
    ///        and evaluate limit values on given PatchTable.
    ///
    /// @param src              Input primvar pointer. An offset of srcDesc
    ///                         will be applied internally (i.e. the pointer
    ///                         should not include the offset)
    ///
    /// @param srcDesc          vertex buffer descriptor for the input buffer
    ///
    /// @param dst              Output primvar pointer. An offset of dstDesc
    ///                         will be applied internally.
    ///
    /// @param dstDesc          vertex buffer descriptor for the output buffer
    ///
    /// @param du               Output U-derivatives pointer. An offset of
    ///                         duDesc will be applied internally.
    ///
    /// @param duDesc           vertex buffer descriptor for the du buffer
    ///
    /// @param dv               Output V-derivatives pointer. An offset of
    ///                         dvDesc will be applied internally.
    ///
    /// @param dvDesc           vertex buffer descriptor for the dv buffer
    ///
    /// @param numPatchCoords   number of patchCoords.
    ///
    /// @param patchCoords      array of locations to be evaluated.
    ///
    /// @param patchArrays      an array of Osd::PatchArray struct
    ///                         indexed by PatchCoord::arrayIndex
    ///
    /// @param patchIndexBuffer an array of patch indices
    ///                         indexed by PatchCoord::vertIndex
    ///
    /// @param patchParamBuffer an array of Osd::PatchParam struct
    ///                         indexed by PatchCoord::patchIndex
    ///
    static bool EvalPatches(
        const float *src, BufferDescriptor const &srcDesc,
        float *dst,       BufferDescriptor const &dstDesc,
        float *du,        BufferDescriptor const &duDesc,
        float *dv,        BufferDescriptor const &dvDesc,
        int numPatchCoords,
        PatchCoord const *patchCoords,
        PatchArray const *patchArrays,
        const int *patchIndexBuffer,
        PatchParam const *patchParamBuffer);

    /// ----------------------------------------------------------------------
    ///
    ///   Other methods
    ///
    /// ----------------------------------------------------------------------

    static void Synchronize(void *deviceContext = NULL);

    static void SetNumThreads(int numThreads);
};


}  // end namespace Osd

}  // end namespace OPENSUBDIV_VERSION
using namespace OPENSUBDIV_VERSION;

}  // end namespace OpenSubdiv


#endif  // OPENSUBDIV3_OSD_OMP_EVALUATOR_H
