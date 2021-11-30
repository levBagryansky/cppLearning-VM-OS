#include <gtest/gtest.h>
#include <iostream>
#include "QueueOnStack-impl.h"
#include "QueueOnList-impl.h"

#ifdef USING_ON_STACK
	using namespace OnStack;
#else
	using namespace OnList;
#endif

TEST(Queue, GetSize){
	Queue<int> ints;
	for (int i = 0; i < 2e4; ++i) {
		ints.push(i);
	}
	ASSERT_EQ(ints.GetSize(), 2e4);

	for (int i = 0; i < 1e4; ++i) {
		ints.pop();
	}
	ASSERT_EQ(ints.GetSize(), 1e4);

	Queue<double> doubles;
	for (int i = 0; i < 2e4; ++i) {
		doubles.push(static_cast<double>(i % 2));
	}
	ASSERT_EQ(doubles.GetSize(), 2e4);

	for (int i = 0; i < 1e4; ++i) {
		doubles.pop();
	}
	ASSERT_EQ(doubles.GetSize(), 1e4);
}

TEST(Queue, IsEmpty){
	Queue<int> ints;
	ASSERT_TRUE(ints.IsEmpty());
	for (int i = 0; i < 2e4; ++i) {
		ints.push(i);
	}
	ASSERT_FALSE(ints.IsEmpty());
	for (int i = 0; i < 2e4; ++i) {
		ints.pop();
	}
	ASSERT_TRUE(ints.IsEmpty());
}

TEST(Queue, PushAndBack){
	Queue<int> ints;
	for (int i = 0; i < 1e5; ++i) {
		ints.push(i);
		ASSERT_EQ(i, ints.back());
	}

	Queue<double> doubles;
	for (int i = 0; i < 1e6; ++i) {
		doubles.push(static_cast<double>(i % 6));
		double b = doubles.back();
		ASSERT_EQ(static_cast<double>(i % 6), b);
	}
}

TEST(Queue, PopAndFront){
	Queue<int> ints;
	for (int i = 0; i < 1e5; ++i) {
		ints.push(i);
	}

	for (int i = 0; i < 1e5; ++i) {
		ASSERT_EQ(i, ints.front());
		ints.pop();
	}

	Queue<double> doubles;
	for (int i = 0; i < 1e5; ++i) {
		doubles.push(static_cast<double>(i)/7);
	}

	for (int i = 0; i < 1e5; ++i) {
		ASSERT_DOUBLE_EQ(static_cast<double>(i)/7, doubles.front());
		doubles.pop();
	}
}

TEST(Queue, Equal){
	Queue<int> ints1;
	Queue<int> ints2;
	ASSERT_TRUE(ints1 == ints2);

	Queue<double> doubles1;
	Queue<double> doubles2;
	ASSERT_TRUE(doubles1 == doubles2);

	for (int i = 0; i < 900; ++i) {
		ints1.push(i);
	}

	for (int i = 0; i < 900; ++i) {
		ints2.push(i);
	}
	ASSERT_TRUE(ints1 == ints2);

	ints1.push(9);
	ASSERT_FALSE(ints1 == ints2);

	doubles1 = {};
	doubles2 = {};
	std::vector<double> v_doubles(100000);
	for (int i = 0; i < 100000; ++i) {
		v_doubles.push_back(static_cast<double>(rand() % 2 == 1));
	}
	for (double item : v_doubles) {
		doubles1.push(item);
		doubles2.push(item);
	}
	ASSERT_TRUE(doubles1 == doubles2);

	doubles1.pop();
	ASSERT_FALSE(doubles1 == doubles2);

}

TEST(Queue, Swap){
;	Queue<int> ints1;
	Queue<int> ints2;
	Queue<int> ints1_buf;
	Queue<int> ints2_buf;
	ints1.push(1);
	ints1.push(2);
	ints1.push(3);
	ints2.push(9);
	ints1_buf = ints1;
	ints2_buf = ints2;
	ints1.swap(ints2);
	ASSERT_TRUE(ints1 == ints2_buf);
	ASSERT_TRUE(ints2 == ints1_buf);

	for (int i = 0; i < 1e4; ++i) {
		ints1.push(i);
		ints2.push(10 * i);
	}
	ints1_buf = ints1;
	ints2_buf = ints2;
	ints1.swap(ints2);
	ASSERT_TRUE(ints1 == ints2_buf);
	ASSERT_TRUE(ints2 == ints1_buf);
	ASSERT_FALSE(ints1 == ints2);


	Queue<double> doubles1;
	Queue<double> doubles2;
	Queue<double> doubles1_buf;
	Queue<double> doubles2_buf;
	for (int i = 0; i < 200; ++i) {
		doubles1.push(0.123);
		doubles2.push(0.456);
	}
	doubles1_buf = doubles1;
	doubles2_buf = doubles2;
	doubles1.swap(doubles2);
	ASSERT_TRUE(doubles2 == doubles1_buf);
	ASSERT_TRUE(doubles1 == doubles2_buf);
	ASSERT_FALSE(doubles1 == doubles2);

}

TEST(Queue, CopyConstructor){
	Queue<int> ints1;
	for (int i = 0; i < 1e5; ++i) {
		ints1.push(i);
	}

	Queue<int> ints2{ints1};
	ASSERT_TRUE(ints1 == ints2);


	Queue<double> doubles1;
	for (int i = 0; i < 1e5; ++i) {
		doubles1.push(0.789);
	}
	Queue<double> doubles2(doubles1);
	ASSERT_TRUE(doubles1 == doubles2);

}

TEST(Queue, MoveConstructor){
	Queue<int> ints1;
	for (int i = 0; i < 1e5; ++i) {
		ints1.push(i);
	}
	Queue<int> ints2(std::move(ints1));
	for (int i = 0; i < 1e5; ++i) {
		ASSERT_TRUE(ints2.front() == i);
		ints2.pop();
	}

	Queue<double> doubles1;
	for (int i = 0; i < 1e5; ++i) {
		doubles1.push(static_cast<double>((i + 1) % 2));
	}
	Queue<double> doubles2(std::move(doubles1));
	ASSERT_TRUE(doubles2.GetSize() == 1e5);
	for (int i = 0; i < 1e5; ++i) {
		ASSERT_TRUE(doubles2.front() == static_cast<double>((i + 1) % 2));
		doubles2.pop();
	}
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}