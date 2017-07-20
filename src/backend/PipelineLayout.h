// Copyright 2017 The NXT Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BACKEND_PIPELINELAYOUT_H_
#define BACKEND_PIPELINELAYOUT_H_

#include "backend/Forward.h"
#include "backend/Builder.h"
#include "backend/RefCounted.h"
#include "common/Constants.h"

#include "nxt/nxtcpp.h"

#include <array>
#include <bitset>

namespace backend {

    using BindGroupLayoutArray = std::array<Ref<BindGroupLayoutBase>, kMaxBindGroups>;

    class PipelineLayoutBase : public RefCounted {
        public:
            PipelineLayoutBase(PipelineLayoutBuilder* builder);

            const BindGroupLayoutBase* GetBindGroupLayout(size_t group) const;
            const std::bitset<kMaxBindGroups> GetBindGroupsLayoutMask() const;

            // Utility functions to compute inherited bind groups.
            // Returns the inherited bind groups as a mask
            std::bitset<kMaxBindGroups> InheritedGroupsMask(const PipelineLayoutBase* other) const;

            // Returns the index of the first incompatible bind group (in the range [1, kMaxBindGroups + 1])
            uint32_t GroupsInheritUpTo(const PipelineLayoutBase* other) const;

        protected:
            BindGroupLayoutArray bindGroupLayouts;
            std::bitset<kMaxBindGroups> mask;
    };

    class PipelineLayoutBuilder : public Builder<PipelineLayoutBase> {
        public:
            PipelineLayoutBuilder(DeviceBase* device);

            // NXT API
            void SetBindGroupLayout(uint32_t groupIndex, BindGroupLayoutBase* layout);

        private:
            friend class PipelineLayoutBase;

            PipelineLayoutBase* GetResultImpl() override;

            BindGroupLayoutArray bindGroupLayouts;
            std::bitset<kMaxBindGroups> mask;
    };

}

#endif // BACKEND_PIPELINELAYOUT_H_