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

TEST_P(PresetSelectorSegmentMinTest, ShouldMatch) {
	int first_selected_segment = std::get<1>(GetParam());
	int second_selected_segment = std::get<2>(GetParam());
	int segment = std::get<3>(GetParam());
	int expected = std::get<0>(GetParam());

    if (first_selected_segment == -1 && second_selected_segment != -1) 
        throw std::runtime_error("bad test case");

    if (first_selected_segment > -1) {
        subject.Expand(first_selected_segment);
    }
    if (second_selected_segment > -1) {
        subject.Expand(second_selected_segment);
    }

    ASSERT_EQ(expected, subject.MinForSegment(segment));
}

INSTANTIATE_TEST_CASE_P(
    Run,
    PresetSelectorSegmentMinTest,
    ::testing::Values(
        std::make_tuple(0, -1, -1, 0),
        std::make_tuple(37, -1, -1, 1),
        std::make_tuple(74, -1, -1, 2),
        std::make_tuple(481, -1, -1, 13),

        // Expand segment 0 (first button): 0-36
        std::make_tuple(0, 0, -1, 0),
        std::make_tuple(3, 0, -1, 1),
        std::make_tuple(6, 0, -1, 2),
        std::make_tuple(36, 0, -1, 12),
        std::make_tuple(-1, 0, -1, 13),

        // Expand segment 2: 74-110
        std::make_tuple(74, 2, -1, 0),
        std::make_tuple(77, 2, -1, 1),
        std::make_tuple(80, 2, -1, 2),
        std::make_tuple(110, 2, -1, 12),
        std::make_tuple(-1, 2, -1, 13),
        
        // Expand segment 13: 481-511
        std::make_tuple(481, 13, -1, 0),
        std::make_tuple(484, 13, -1, 1),
        std::make_tuple(487, 13, -1, 2),
        std::make_tuple(511, 13, -1, 10),
        std::make_tuple(-1, 13, -1, 11),

        // Expand segment 0, then 0
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(1, 0, 0, 1),
        std::make_tuple(2, 0, 0, 2),
        std::make_tuple(-1, 0, 0, 3),

        // Expand segment 13, then 10
        std::make_tuple(511, 13, 10, 0),
        std::make_tuple(-1, 13, 10, 1)
    ));

TEST_P(PresetSelectorSegmentMaxTest, ShouldMatch) {
	int first_selected_segment = std::get<1>(GetParam());
	int second_selected_segment = std::get<2>(GetParam());
	int segment = std::get<3>(GetParam());
	int expected = std::get<0>(GetParam());

    if (first_selected_segment == -1 && second_selected_segment != -1) 
        throw std::runtime_error("bad test case");
        
    if (first_selected_segment > -1) {
        subject.Expand(first_selected_segment);
    }
    if (second_selected_segment > -1) {
        subject.Expand(second_selected_segment);
    }

    ASSERT_EQ(expected, subject.MaxForSegment(segment));
}

INSTANTIATE_TEST_CASE_P(
    Run,
    PresetSelectorSegmentMaxTest,
    ::testing::Values(
        std::make_tuple(36, -1, -1, 0),
        std::make_tuple(73, -1, -1, 1),
        std::make_tuple(110, -1, -1, 2),
        std::make_tuple(511, -1, -1, 13),

        // Expand segment 0 (first button): 0-36
        std::make_tuple(2, 0, -1, 0),
        std::make_tuple(5, 0, -1, 1),
        std::make_tuple(8, 0, -1, 2),
        std::make_tuple(36, 0, -1, 12),
        std::make_tuple(-1, 0, -1, 13),

        // Expand segment 2: 74-110
        std::make_tuple(76, 2, -1, 0),
        std::make_tuple(79, 2, -1, 1),
        std::make_tuple(82, 2, -1, 2),
        std::make_tuple(110, 2, -1, 12),
        std::make_tuple(-1, 2, -1, 13),

        // Expand segment 13: 481-511
        std::make_tuple(483, 13, -1, 0),
        std::make_tuple(486, 13, -1, 1),
        std::make_tuple(489, 13, -1, 2),
        std::make_tuple(511, 13, -1, 10),
        std::make_tuple(-1, 13, -1, 11),

        // Expand segment 0, then 0
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(1, 0, 0, 1),
        std::make_tuple(2, 0, 0, 2),
        std::make_tuple(-1, 0, 0, 3),

        // Expand segment 13, then 10
        std::make_tuple(511, 13, 10, 0),
        std::make_tuple(-1, 13, 10, 1)
    ));
