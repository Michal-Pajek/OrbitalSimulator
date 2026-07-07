#pragma once

namespace physics {
	inline constexpr double G_CONST{ 6.6743e-11 };
	// distance
	inline constexpr double KM_MULTIPLIER{ 1e3 };
	inline constexpr double KKM_MULTIPLIER{ 1e6 };
	inline constexpr double MKM_MULTIPLIER{ 1e9 };
	inline constexpr double AU{ 1.495978707e12 };
	inline constexpr double EARTH_MOON_DISTANCE{ 3.844e8 };
	// mass
	inline constexpr double TON{ 1e3 };
	inline constexpr double KILOTON{ 1e6 };
	inline constexpr double MEGATON{ 1e9 };
	inline constexpr double MOON_MASS{ 7.347673e22 };
	inline constexpr double EARTH_MASS{ 5.9722e24 };
	inline constexpr double JUPITER_MASS{ 1.89819e27 };
	inline constexpr double SOLAR_MASS{ 1.989e30 };
	// speed
	inline constexpr double C_CONST{ 2.99792458e8 };
	inline constexpr double KMS_MULTIPLIER{ 1e3 };
	inline constexpr double KKMH_MULTIPLIER{ 10'000.0 / 36.0 };
}
