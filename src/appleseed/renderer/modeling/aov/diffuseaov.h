
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2017 Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_MODELING_AOV_DIFFUSEAOV_H
#define APPLESEED_RENDERER_MODELING_AOV_DIFFUSEAOV_H

// appleseed.renderer headers.
#include "renderer/modeling/aov/iaovfactory.h"

// appleseed.foundation headers.
#include "foundation/utility/autoreleaseptr.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Forward declarations.
namespace foundation    { class Dictionary; }
namespace foundation    { class DictionaryArray; }
namespace renderer      { class AOV; }
namespace renderer      { class ParamArray; }

namespace renderer
{

//
// A factory for diffuse AOVs.
//

class APPLESEED_DLLSYMBOL DiffuseAOVFactory
  : public IAOVFactory
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying this AOV model.
    const char* get_model() const override;

    // Return metadata for this AOV model.
    foundation::Dictionary get_model_metadata() const override;

    // Return metadata for the inputs of this AOV model.
    foundation::DictionaryArray get_input_metadata() const override;

    // Create a new AOV instance.
    foundation::auto_release_ptr<AOV> create(
        const ParamArray&   params) const override;
};


//
// A factory for direct diffuse AOVs.
//

class APPLESEED_DLLSYMBOL DirectDiffuseAOVFactory
  : public IAOVFactory
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying this AOV model.
    const char* get_model() const override;

    // Return metadata for this AOV model.
    foundation::Dictionary get_model_metadata() const override;

    // Return metadata for the inputs of this AOV model.
    foundation::DictionaryArray get_input_metadata() const override;

    // Create a new AOV instance.
    foundation::auto_release_ptr<AOV> create(
        const ParamArray&   params) const override;
};


//
// A factory for indirect diffuse AOVs.
//

class APPLESEED_DLLSYMBOL IndirectDiffuseAOVFactory
  : public IAOVFactory
{
  public:
    // Delete this instance.
    void release() override;

    // Return a string identifying this AOV model.
    const char* get_model() const override;

    // Return metadata for this AOV model.
    foundation::Dictionary get_model_metadata() const override;

    // Return metadata for the inputs of this AOV model.
    foundation::DictionaryArray get_input_metadata() const override;

    // Create a new AOV instance.
    foundation::auto_release_ptr<AOV> create(
        const ParamArray&   params) const override;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_AOV_DIFFUSEAOV_H
