#pragma once

namespace physics {
	inline constexpr double G_CONST{ 6.6743E-11 };
	// distance
	inline constexpr double KM_MULTIPLIER{ 1000.0 };
	inline constexpr double KKM_MULTIPLIER{ 1'000'000.0 };
	inline constexpr double MKM_MULTIPLIER{ 1'000'000'000.0 };
	inline constexpr double AU{ 1.495978707E12 };
	inline constexpr double EARTH_MOON_DISTANCE{ 3.844E9 };
	// mass
	inline constexpr double TON{1000.0};
	inline constexpr double KILOTON{1'000'000.0};
	inline constexpr double MEGATON{1'000'000'000.0};
	inline constexpr double EARTH_MASS{5.9722E24};
	inline constexpr double JUPITER_MASS{ 1.89819E27 };
	inline constexpr double SOLAR_MASS{1.989E30};
	// speed
	inline constexpr double C_CONST{ 2.99792458E8 };
	inline constexpr double KMS_MULTIPLIER{ 1000.0 };
	inline constexpr double KKMH_MULTIPLIER{ 10'000.0 / 36.0 };
}