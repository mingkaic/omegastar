#include <random>

#include "omegastar/igenerator.h"

#ifdef ENABLE_BOOST_UUID
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#else
#include <sstream>
#endif // ENABLE_BOOST_UUID

#ifndef OMEGASTAR_RANDOM_HPP
#define OMEGASTAR_RANDOM_HPP

namespace omegastar
{

struct Randomizer final : public iRandGenerator
{
	Randomizer (void) : rengine_(std::random_device()()) {}

	/// Implementation of iGenerator
	int64_t unif_int (const int64_t& lower, const int64_t& upper) const override
	{
		std::uniform_int_distribution<int64_t> dist(lower, upper);
		return dist(rengine_);
	}

	/// Implementation of iGenerator
	double unif_dec (const double& lower, const double& upper) const override
	{
		std::uniform_real_distribution<double> dist(lower, upper);
		return dist(rengine_);
	}

	/// Implementation of iGenerator
	double norm_dec (const double& mean, const double& stdev) const override
	{
		std::normal_distribution<double> dist(mean, stdev);
		return dist(rengine_);
	}

	/// Implementation of iGenerator
	gen_f<std::string> get_strgen (void) const override
	{
		return [this]{ return this->get_str(); };
	}

	/// Implementation of iGenerator
	gen_f<int64_t> unif_intgen (
		const int64_t& lower, const int64_t& upper) const override
	{
		std::uniform_int_distribution<int64_t> dist(lower, upper);
		return std::bind(dist, rengine_);
	}

	/// Implementation of iGenerator
	gen_f<double> unif_decgen (
		const double& lower, const double& upper) const override
	{
		std::uniform_real_distribution<double> dist(lower, upper);
		return std::bind(dist, rengine_);
	}

	/// Implementation of iGenerator
	gen_f<double> norm_decgen (
		const double& mean, const double& stdev) const override
	{
		std::normal_distribution<double> dist(mean, stdev);
		return std::bind(dist, rengine_);
	}

	/// Implementation of iRandGenerator
	void seed (size_t s) override
	{
		rengine_.seed(s);
	}

	mutable std::mt19937 rengine_;

#ifdef ENABLE_BOOST_UUID
	/// Implementation of iGenerator
	std::string get_str (void) const override
	{
		return boost::uuids::to_string(uengine_());
	}

	mutable boost::uuids::random_generator uengine_;
#else
	/// Implementation of iGenerator
	std::string get_str (void) const override
	{
		std::uniform_int_distribution<int> uuid_dis(0, 15);
        std::stringstream ss;
        ss << std::hex;
        for (size_t i = 0; i < 36; i++) {
            ss << uuid_dis(rengine_);
        }
        return ss.str();
	}
#endif // ENABLE_BOOST_UUID
};

}

#endif // OMEGASTAR_RANDOM_HPP
