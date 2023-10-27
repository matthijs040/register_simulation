#include <HAL/clock_control.hpp>
#include <array>
#include <rp2040/time/ROSC.hpp>

using namespace reg::ROSC;

constexpr std::array frequencies{
    2972972u, 3092783u, 3108808u, 3125000u, 3333333u, 3378378u, 3409090u,
    3571428u, 3603603u, 3619909u, 3773584u, 3881278u, 3935185u, 4000000u,
    4081632u, 4123711u, 4301075u, 4395604u, 4419889u, 4761904u, 4918032u,
    4972375u, 5263157u, 5347593u, 5405405u, 4301075u, 4301075u, 4278074u,
    4278074u, 4278074u, 4255319u, 4255319u, 4522613u, 4615384u, 4663212u,
    4926108u, 5050505u, 5102040u, 5583756u, 5729166u, 5820105u, 6217616u,
    6372549u, 6500000u, 8163265u, 8219178u, 8450704u, 8333333u, 8333333u,
    8333333u, 8333333u, 8212560u, 8173076u, 8333333u, 8235294u,
};
constexpr uint32_t table_divisor = 31;
constexpr uint32_t divisor_prefix = 0xaa0;

// The three power-stages of all 8 drive-strength registers. (used in the
// "low" frequency range)
constexpr auto low_range_power = 8 * 3;
// the three power-stages of the 6 drive-strength registers used in the "mid"
// frequency range.
constexpr auto mid_range_power = 6 * 3;

ROSC &ROSC::get() noexcept {
  static ROSC *handle;
  if (handle)
    return *handle;
  return *(handle = new ROSC());
}

ROSC::~ROSC() {}

void ROSC::operator delete(void *addr) { static_cast<ROSC *>(addr)->~ROSC(); }

ROSC::ROSC() : CTRL() {}

void *ROSC::operator new(std::size_t size) {
  if constexpr (USE_SIMULATED_REGISTERS)
    return simulated_peripheral<ROSC>::operator new(size);
  return reinterpret_cast<ROSC *>(base_address);
}

std::expected<uint32_t, std::error_code>
ROSC::get_frequency_Hz() const noexcept {
  std::expected<uint32_t, std::error_code> ret;

  if (CTRL.ENABLE == reg::ROSC::CTRL::ENABLE_states::disabled) {
    std::error_code err = clock_error::code::disabled;
    ret = std::unexpected(err);
    return ret;
  }

  return frequencies.at(get_power_stage()) *
         table_divisor / (DIV.divisor - divisor_prefix);
}

constexpr uint32_t drive_strength_to_power_level(drive_strength strength) {
  return strength == drive_strength::double_strength      ? 1
         : strength == drive_strength::triple_strength    ? 2
         : strength == drive_strength::quadruple_strength ? 3
                                                          : 0;
}

std::uint32_t ROSC::get_power_stage() const noexcept {
  uint32_t power_stage = 0u;
  if (CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::medium ||
      CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::high)
    power_stage += low_range_power + 1;
  if (CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::high)
    power_stage += mid_range_power + 1;

  power_stage += drive_strength_to_power_level(FREQA.DS0);
  power_stage += drive_strength_to_power_level(FREQA.DS1);
  power_stage += drive_strength_to_power_level(FREQA.DS2);
  power_stage += drive_strength_to_power_level(FREQA.DS3);
  if (CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::high)
    return power_stage;

  power_stage += drive_strength_to_power_level(FREQB.DS4);
  power_stage += drive_strength_to_power_level(FREQB.DS5);

  if (CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::medium)
    return power_stage;

  power_stage += drive_strength_to_power_level(FREQB.DS6);
  power_stage += drive_strength_to_power_level(FREQB.DS7);
  return power_stage;
}

constexpr reg::ROSC::drive_strength take_drive_strength(uint32_t &strength) {
  if (strength >= 3) {
    strength -= 3;
    return reg::ROSC::drive_strength::quadruple_strength;
  }
  if (strength >= 2) {
    strength -= 2;
    return reg::ROSC::drive_strength::triple_strength;
  }
  if (strength >= 1) {
    strength -= 1;
    return reg::ROSC::drive_strength::double_strength;
  }

  return reg::ROSC::drive_strength::default_strength;
}

constexpr CTRL::FREQ_RANGE_states
determine_frequency_range(uint32_t &strength) {
  if (strength <= low_range_power)
    return CTRL::FREQ_RANGE_states::low;
  strength -= low_range_power + 1;
  if (strength <= mid_range_power)
    return CTRL::FREQ_RANGE_states::medium;
  strength -= mid_range_power + 1;
  return CTRL::FREQ_RANGE_states::high;
}

inline void find_closest_match(uint32_t desired_frequency,
                               const uint32_t *&result,
                               uint32_t &used_divisor) {

  uint32_t old_offset = std::numeric_limits<uint32_t>::max();
  for (uint32_t divisor = table_divisor; divisor; divisor--) {
    for (const auto &frequency : frequencies) {
      uint32_t offset =
          abs(desired_frequency - (frequency * table_divisor / divisor));
      if (!result || offset < old_offset) {
        old_offset = offset;
        used_divisor = divisor;
        result = &frequency;
      }
    }
  }
}

std::expected<uint32_t, std::error_code>
ROSC::set_frequency_Hz(std::uint32_t desired_frequency) noexcept {
  if (CTRL.ENABLE == reg::ROSC::CTRL::ENABLE_states::disabled) {
    std::cout << "CTRL.ENABLE is disabled\n";
    std::error_code err = clock_error::code::disabled;
    auto ret = std::unexpected(err);
    return ret;
  }
  const uint32_t *result = nullptr;
  uint32_t used_divisor;
  find_closest_match(desired_frequency, result,
                     used_divisor);

  uint32_t power_stage = result - frequencies.data();
  auto final_frequency =
      frequencies.at(power_stage) * table_divisor / used_divisor;
  set_power_stage(power_stage);
  DIV.divisor = divisor_prefix + used_divisor;

  return final_frequency;
}

void ROSC::set_power_stage(uint32_t power_stage) noexcept {
  const auto frequency_range = determine_frequency_range(power_stage);
  apply_settings(
      frequency_range, take_drive_strength(power_stage),
      take_drive_strength(power_stage), take_drive_strength(power_stage),
      take_drive_strength(power_stage),
      // The following DS registers have their DS set based on given strength
      // only if their frequency range uses those stages. The datasheet mentions
      // that these stages must *at least* have the strength of the lowest-power
      // stage that is active in the loop. Setting these at their highest anyway
      // guarantees this condition while not affecting frequency.
      frequency_range == CTRL::FREQ_RANGE_states::low ||
              frequency_range == CTRL::FREQ_RANGE_states::medium
          ? take_drive_strength(power_stage)
          : drive_strength::quadruple_strength,
      frequency_range == CTRL::FREQ_RANGE_states::low ||
              frequency_range == CTRL::FREQ_RANGE_states::medium
          ? take_drive_strength(power_stage)
          : drive_strength::quadruple_strength,
      frequency_range == CTRL::FREQ_RANGE_states::low
          ? take_drive_strength(power_stage)
          : drive_strength::quadruple_strength,
      frequency_range == CTRL::FREQ_RANGE_states::low
          ? take_drive_strength(power_stage)
          : drive_strength::quadruple_strength);
}

void ROSC::apply_settings(
    reg::ROSC::CTRL::FREQ_RANGE_states range, reg::ROSC::drive_strength DS0,
    reg::ROSC::drive_strength DS1, reg::ROSC::drive_strength DS2,
    reg::ROSC::drive_strength DS3, reg::ROSC::drive_strength DS4,
    reg::ROSC::drive_strength DS5, reg::ROSC::drive_strength DS6,
    reg::ROSC::drive_strength DS7) noexcept {

  CTRL.FREQ_RANGE = range;
  FREQA.DS0 = DS0;
  FREQA.DS1 = DS1;
  FREQA.DS2 = DS2;
  FREQA.DS3 = DS3;
  FREQA.PASSWD = reg::ROSC::PASSWD_states::apply;

  FREQB.DS4 = DS4;
  FREQB.DS5 = DS5;
  FREQB.DS6 = DS6;
  FREQB.DS7 = DS7;
  FREQB.PASSWD = reg::ROSC::PASSWD_states::apply;
}

std::span<const uint32_t> ROSC::get_frequencies_by_power_stage() noexcept {
  return frequencies;
}