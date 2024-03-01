#include <functional>
#include <type_traits>

#ifndef OMEGASTAR_IGENERATOR_HPP
#define OMEGASTAR_IGENERATOR_HPP

namespace omegastar
{

/// Function that returns a generated value
template <typename T>
using gen_f = std::function<T()>;

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
	virtual gen_f<std::string> get_strgen (void) const = 0;

	/// Return generator function that uniformly generates integers between a and b
	virtual gen_f<int64_t> unif_intgen (
		const int64_t& lower, const int64_t& upper) const = 0;

	/// Return generator function that uniformly generates decimals between a and b
	virtual gen_f<double> unif_decgen (
		const double& lower, const double& upper) const = 0;

	/// Return generator function that normally generate decimal with mean and stdev
	virtual gen_f<double> norm_decgen (
		const double& mean, const double& stdev) const = 0;
};

template <class GENERATOR>
struct iRandGenerator : public iGenerator
{
	using ptr_t = std::shared_ptr<iRandGenerator>;

	using generator_t = GENERATOR;

	using result_type = typename GENERATOR::result_type;

	static constexpr size_t max (void) { return GENERATOR::max(); }

	static constexpr size_t min (void) { return GENERATOR::min(); }

	virtual ~iRandGenerator (void) = default;

	/// Seed the random engine using seed specified
	virtual void seed (size_t s) = 0;

	virtual size_t operator() (void) = 0;

	virtual GENERATOR& get_internal (void) = 0;
};

}

#endif // OMEGASTAR_IGENERATOR_HPP
