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

#include "../osd/hlslPatchShaderSource.h"
#include "../far/error.h"

#include <sstream>
#include <string>

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

namespace Osd {

static const char *commonShaderSource =
#include "hlslPatchCommon.gen.h"
;
static const char *bsplineShaderSource =
#include "hlslPatchBSpline.gen.h"
;
static const char *gregoryShaderSource =
#include "hlslPatchGregory.gen.h"
;
static const char *gregoryBasisShaderSource =
#include "hlslPatchGregoryBasis.gen.h"
;

/*static*/
std::string
HLSLPatchShaderSource::GetCommonShaderSource() {
    return std::string(commonShaderSource);
}

/*static*/
std::string
HLSLPatchShaderSource::GetVertexShaderSource(Far::PatchDescriptor::Type type) {
    switch (type) {
    case Far::PatchDescriptor::REGULAR:
        return bsplineShaderSource;
    case Far::PatchDescriptor::GREGORY:
        return gregoryShaderSource;
    case Far::PatchDescriptor::GREGORY_BOUNDARY:
        return std::string("#define OSD_PATCH_GREGORY_BOUNDRY\n")
             + std::string(gregoryShaderSource);
    case Far::PatchDescriptor::GREGORY_BASIS:
        return gregoryBasisShaderSource;
    default:
        break;  // returns empty (points, lines, quads, ...)
    }
    return std::string();
}

/*static*/
std::string
HLSLPatchShaderSource::GetHullShaderSource(Far::PatchDescriptor::Type type) {
    switch (type) {
    case Far::PatchDescriptor::REGULAR:
        return bsplineShaderSource;
    case Far::PatchDescriptor::GREGORY:
        return gregoryShaderSource;
    case Far::PatchDescriptor::GREGORY_BOUNDARY:
        return std::string("#define OSD_PATCH_GREGORY_BOUNDRY\n")
             + std::string(gregoryShaderSource);
    case Far::PatchDescriptor::GREGORY_BASIS:
        return gregoryBasisShaderSource;
    default:
        break;  // returns empty (points, lines, quads, ...)
    }
    return std::string();
}

/*static*/
std::string
HLSLPatchShaderSource::GetDomainShaderSource(Far::PatchDescriptor::Type type) {
    switch (type) {
    case Far::PatchDescriptor::REGULAR:
        return bsplineShaderSource;
    case Far::PatchDescriptor::GREGORY:
        return gregoryShaderSource;
    case Far::PatchDescriptor::GREGORY_BOUNDARY:
        return std::string("#define OSD_PATCH_GREGORY_BOUNDRY\n")
             + std::string(gregoryShaderSource);
    case Far::PatchDescriptor::GREGORY_BASIS:
        return gregoryBasisShaderSource;
    default:
        break;  // returns empty (points, lines, quads, ...)
    }
    return std::string();
}

}  // end namespace Osd

}  // end namespace OPENSUBDIV_VERSION
} // end namespace OpenSubdiv
