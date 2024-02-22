
#ifndef DISABLE_ENGINE_TEST


#include <array>

#include "gtest/gtest.h"

#include "omegastar/random.h"


TEST(ENGINE, RandInt)
{
	typename omegastar::iGenerator::ptr_t engine = std::make_shared<omegastar::Randomizer>();

	int64_t mi = -5;
	int64_t ma = 4;
	std::array<size_t,10> bucket;
	bucket.fill(0);
	for (size_t i = 0; i < 1000; ++i)
	{
		int64_t result = engine->uniform(mi, ma);
		ASSERT_LE(-5, result);
		ASSERT_GE(4, result);
		int64_t index = result + 5;
		++bucket[index];
	}
	for (auto b : bucket)
	{
		EXPECT_LT(75, b);
		EXPECT_GT(125, b);
	}
}


TEST(ENGINE, RandString)
{
	typename omegastar::iGenerator::ptr_t engine = std::make_shared<omegastar::Randomizer>();
	std::cout << engine->get_str() << std::endl;
}


#endif // DISABLE_ENGINE_TEST
