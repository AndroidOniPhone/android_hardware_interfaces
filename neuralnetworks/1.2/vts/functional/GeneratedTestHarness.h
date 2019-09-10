/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_NEURALNETWORKS_V1_2_GENERATED_TEST_HARNESS_H
#define ANDROID_HARDWARE_NEURALNETWORKS_V1_2_GENERATED_TEST_HARNESS_H

#include <android/hardware/neuralnetworks/1.2/IDevice.h>
#include <android/hardware/neuralnetworks/1.2/IPreparedModel.h>
#include <android/hardware/neuralnetworks/1.2/types.h>
#include <functional>
#include <vector>
#include "TestHarness.h"
#include "VtsHalNeuralnetworks.h"

namespace android::hardware::neuralnetworks::V1_2::vts::functional {

class GeneratedTestBase
    : public NeuralnetworksHidlTest,
      public ::testing::WithParamInterface<test_helper::TestModelManager::TestParam> {
  protected:
    void SetUp() override {
        NeuralnetworksHidlTest::SetUp();
        ASSERT_NE(mTestModel, nullptr);
    }

    const test_helper::TestModel* mTestModel = GetParam().second;
};

#define INSTANTIATE_GENERATED_TEST(TestSuite, filter)                                          \
    INSTANTIATE_TEST_SUITE_P(                                                                  \
            TestGenerated, TestSuite,                                                          \
            ::testing::ValuesIn(::test_helper::TestModelManager::get().getTestModels(filter)), \
            [](const auto& info) { return info.param.first; })

// Tag for the validation tests, instantiated in VtsHalNeuralnetworks.cpp.
// TODO: Clean up the hierarchy for ValidationTest.
class ValidationTest : public GeneratedTestBase {
  protected:
    void validateEverything(const Model& model, const V1_0::Request& request);
    void validateFailure(const Model& model, const V1_0::Request& request);

  private:
    void validateModel(const Model& model);
    void validateRequest(const sp<IPreparedModel>& preparedModel, const V1_0::Request& request);
    void validateRequestFailure(const sp<IPreparedModel>& preparedModel,
                                const V1_0::Request& request);
    void validateBurst(const sp<IPreparedModel>& preparedModel, const V1_0::Request& request);
};

Model createModel(const ::test_helper::TestModel& testModel);

void PrepareModel(const sp<IDevice>& device, const Model& model, sp<IPreparedModel>* preparedModel);

void EvaluatePreparedModel(const sp<IPreparedModel>& preparedModel,
                           const ::test_helper::TestModel& testModel, bool testDynamicOutputShape);

}  // namespace android::hardware::neuralnetworks::V1_2::vts::functional

#endif  // ANDROID_HARDWARE_NEURALNETWORKS_V1_2_GENERATED_TEST_HARNESS_H