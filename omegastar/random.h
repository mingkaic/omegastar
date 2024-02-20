#include <random>
#include <type_traits>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#ifndef OMEGASTAR_ENGINE_HPP
#define OMEGASTAR_ENGINE_HPP

namespace omegastar
{

/// Function that returns a generated value
template <typename T>
using GenF = std::function<T()>;

struct iGenerator
{
	using ptr_t = std::shared_ptr<iGenerator>;

	virtual ~iGenerator (void) = default;

	/// Return random string
	virtual std::string get_str (void) const = 0;

	template <typename T, std::enable_if_t<std::is_integral<T>::value,bool> = true>
	inline T uniform (const T& l, const T& r) const
	{
		return this->unif_int(l, r);
	}

	template <typename T, std::enable_if_t<std::is_floating_point<T>::value,bool> = true>
	inline T uniform (const T& l, const T& r) const
	{
		return this->unif_dec(l, r);
	}

	/// Return uniformly generate integer between a and b
	virtual int64_t unif_int (
		const int64_t& lower, const int64_t& upper) const = 0;

	/// Return uniformly generate decimal between a and b
	virtual double unif_dec (
		const double& lower, const double& upper) const = 0;

	/// Return normally generate decimal with mean and stdev
	virtual double norm_dec (
		const double& mean, const double& stdev) const = 0;

	/// Return random string generator function
	virtual GenF<std::string> get_strgen (void) const = 0;

	/// Return generator function that uniformly generates integers between a and b
	virtual GenF<int64_t> unif_intgen (
		const int64_t& lower, const int64_t& upper) const = 0;

	/// Return generator function that uniformly generates decimals between a and b
	virtual GenF<double> unif_decgen (
		const double& lower, const double& upper) const = 0;

	/// Return generator function that normally generate decimal with mean and stdev
	virtual GenF<double> norm_decgen (
		const double& mean, const double& stdev) const = 0;
};

struct iRandGenerator : public iGenerator
{
	virtual ~iRandGenerator (void) = default;

	/// Seed the random engine using seed specified
	virtual void seed (size_t s) = 0;
};

struct Randomizer final : public iRandGenerator
{
	/// Implementation of iGenerator
	std::string get_str (void) const override
	{
		return boost::uuids::to_string(uengine_());
	}

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
	GenF<std::string> get_strgen (void) const override
	{
		return [this]{ return boost::uuids::to_string(this->uengine_()); };
	}

	/// Implementation of iGenerator
	GenF<int64_t> unif_intgen (
		const int64_t& lower, const int64_t& upper) const override
	{
		std::uniform_int_distribution<int64_t> dist(lower, upper);
		return std::bind(dist, rengine_);
	}

	/// Implementation of iGenerator
	GenF<double> unif_decgen (
		const double& lower, const double& upper) const override
	{
		std::uniform_real_distribution<double> dist(lower, upper);
		return std::bind(dist, rengine_);
	}

	/// Implementation of iGenerator
	GenF<double> norm_decgen (
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

	mutable std::default_random_engine rengine_;

	mutable boost::uuids::random_generator uengine_;
};

}

#endif // OMEGASTAR_ENGINE_HPP
