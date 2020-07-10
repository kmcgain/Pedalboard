#include "pch.h"

#include "..\Domain\tape.h"
#include "..\Domain\maybe.h"

TEST(TapeTest, ShouldReadFromStart) {
	Tape<int, 3> tape = Tape<int, 3>();
	tape.Add(1);
	tape.Add(2);

	Maybe<int> item = tape.ReadFromStart(0);
	EXPECT_TRUE(item.IsSome());
	EXPECT_EQ(item.Value(), 1);
}

TEST(TapeTest, ShouldReadFromStartSkipN) {
	Tape<int, 3> tape = Tape<int, 3>();
	tape.Add(1);
	tape.Add(2);
	tape.Add(3);

	Maybe<int> item = tape.ReadFromStart(1);
	EXPECT_TRUE(item.IsSome());
	EXPECT_EQ(item.Value(), 2);
}

TEST(TapeTest, ShouldReadFromStartWhenWrapping) {
	Tape<int, 3> tape = Tape<int, 3>();
	tape.Add(1);
	tape.Add(2);
	tape.Add(3);
	tape.Add(4);
	tape.Add(5);
	tape.Add(6);

	Maybe<int> item = tape.ReadFromStart(1);
	EXPECT_TRUE(item.IsSome());
	EXPECT_EQ(item.Value(), 5);
}

TEST(TapeTest, ShouldTakeFromStart) {
	Tape<int, 3> tape = Tape<int, 3>();
	tape.Add(1);
	tape.Add(2);
	tape.Add(3);

	Maybe<int> item = tape.TakeFromStart();
	EXPECT_TRUE(item.IsSome());
	EXPECT_EQ(item.Value(), 1);

	Maybe<int> itemAfterTake = tape.ReadFromStart(0);
	EXPECT_TRUE(itemAfterTake.IsSome());
	EXPECT_EQ(itemAfterTake.Value(), 2);
}
