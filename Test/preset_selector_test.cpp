#include "pch.h"
#include <tuple>

#include "..\src\Domain\preset_selector.h"

using namespace fakeit;

class PresetSelectorTest : public ::testing::TestWithParam<std::tuple<int, int, int, int>> {
    protected:
        PresetSelector subject;
};

class PresetSelectorSegmentMinTest : public PresetSelectorTest {};
class PresetSelectorSegmentMaxTest : public PresetSelectorTest {};

TEST(PresetSelectorTest, LowestLevelOnStart) {
	PresetSelector subject;

    ASSERT_EQ(true, subject.IsLowestLevel());
}
