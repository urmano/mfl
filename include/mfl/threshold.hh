#ifndef MFL_THRESHOLD_HH_
#define MFL_THRESHOLD_HH_

#include <concepts>
#include <tuple>
#include <any>

namespace mfl {

/*!
 * @brief discribes types for which modulus can be found
 * @param lhs is the left-hand side parameter
 * @param rhs is the right-hand side parameter
 */
template <typename Lhs, typename Rhs>
concept Absable = requires(Lhs lhs, Rhs rhs) {
  { (lhs - rhs) < 0 } -> std::same_as<bool>;
};

/*!
 * @brief provides functionality to threshold operations
 *
 * @tparam Args is the types of threshold parameters
 */
template <typename... Params>
class Threshold {
public:
  /*!
   * @brief constructs instance from the threshold parameters
   *
   * @param args are the threshold parameters
   */
  constexpr Threshold(Params... params);
  /*!
   * @note deprecated
   * @brief checks if given parameters' moduluses of difference
   * are under or equal to the threshold level
   *
   * @param lhs is the left-hand side parameters for modulus of difference
   * @param rhs is the right-hand side parameters for modulus of difference
   * @return true if all threshold parameters were satisfied and false else
   */
  [[deprecated]] [[nodiscard]] constexpr bool operator()(
    const Params&... lhs,
    const Params&... rhs
  ) const;
  /*!
   * @brief checks if given parameters' moduluses of a difference
   * are under or equal to the threshold level
   *
   * @param lhs is the left-hand side parameters for modulus of a difference
   * @param rhs is the right-hand side parameters for modulus of a difference
   * @return true if all threshold parameters were satisfied and false else
   */
  template <typename... ArgsLhs, typename... ArgsRhs>
  [[nodiscard]] constexpr bool operator()(
    std::tuple<ArgsLhs...> lhs,
    std::tuple<ArgsRhs...> rhs
  ) const;
  /*!
   * @brief checks if given parameters' moduluses of a difference
   * are under or equal to the threshold level
   *
   * @param args
   * @return true if all threshold parameters were satisfied and false else
   */
  template <typename... Args>
  [[nodiscard]] constexpr bool operator()(Args&&... args) const;
protected:
  /*!
   * @brief gets absolute difference of lhs and rhs
   *
   * @param lhs is the left-hand side argument
   * @param rhs is the right-hand side argument
   * @return absolute difference
   */
  template <typename Rhs, Absable<Rhs> Lhs>
  [[nodiscard]] constexpr static auto abs(Lhs&& lhs, Rhs&& rhs);
  /*!
   * @brief checks if all paramters were satisfied
   * @note does not check if sizeof d == sizeof params
   *
   * @param d is the absolute difference
   * @param params are the threshold parameters
   * @return true if all parameters were satisfied and false else
   */
  [[nodiscard]] constexpr static auto checkAll(
    const auto& d,
    const auto& params
  );
  std::tuple<Params...> params_;
private:
};

} /// namespace mfl

namespace mfl {

template <typename... Params>
constexpr Threshold<Params...>::Threshold(Params... args) :
  params_(std::move(args)...) {}

template <typename... Params>
constexpr bool Threshold<Params...>::operator()(
    const Params&... lhs,
    const Params&... rhs
  ) const {
//  return std::apply(
//    [this](auto&&... args) {
//      return std::apply(
//        [&args...](auto&&... params) {
//          return ((args <= params) && ...);
//        },
//        params_
//      );
//    },
//    std::tuple<Params...>((Threshold<Params...>::abs(lhs, rhs))...)
//  );
  const auto d = std::tie(Threshold<Params...>::abs(lhs, rhs)...);
  return checkAll(d, params_);
}

template <typename... Params>
template <typename... ArgsLhs, typename... ArgsRhs>
constexpr bool Threshold<Params...>::operator()(
    std::tuple<ArgsLhs...> lhs,
    std::tuple<ArgsRhs...> rhs
  ) const {
  static_assert(sizeof...(ArgsLhs) == std::tuple_size_v<decltype(params_)>);
  static_assert(sizeof...(ArgsRhs) == std::tuple_size_v<decltype(params_)>);
//  return std::apply(
//    [this](auto&&... args) {
//      return std::apply(
//        [&args...](auto&&... params) {
//          return ((args <= params) && ...);
//        },
//        params_
//      );
//    },
//    std::apply(
//      [&rhs](auto&&... argsl) {
//        return std::apply(
//          [&argsl...](auto&& ... argsr) {
//            return std::make_tuple(Threshold<Params...>::abs(argsl, argsr)...);
//          },
//          rhs
//        );
//      },
//      lhs
//    )
//  );
  const auto d = [&lhs, &rhs]<std::size_t... Is>(std::index_sequence<Is...>) {
    return std::make_tuple(
      Threshold<Params...>::abs(
        std::get<Is>(lhs), std::get<Is>(rhs)
      )...
    );
  }(std::index_sequence_for<Params...>());
  return checkAll(d, params_);
}

template <typename... Params>
template <typename... Args>
constexpr bool Threshold<Params...>::operator()(Args&&... args) const {
  static_assert((sizeof...(Args) >> 1) == sizeof...(Params));
  const auto d = [&args...]<std::size_t N, std::size_t... Is>(
    std::index_sequence<Is...>
  ) {
    const auto as = std::tie(args...);
    return std::make_tuple(
      Threshold<Params...>::abs(
        std::get<Is>(as), std::get<Is+N>(as)
      )...
    );
  }.template operator()<sizeof...(Params)>(
    std::index_sequence_for<Params...>()
  );
  return checkAll(d, params_);
}

template <typename... Params>
template <typename Rhs, Absable<Rhs> Lhs>
constexpr auto Threshold<Params...>::abs(Lhs&& lhs, Rhs&& rhs) {
//  static_assert(
//    std::is_signed_v<std::remove_reference_t<Lhs>> ==
//    std::is_signed_v<std::remove_reference_t<Rhs>>
//  );
//  if constexpr (std::is_unsigned_v<std::remove_reference_t<Lhs>>) {
//    const auto l = std::make_signed_t<std::remove_reference_t<Lhs>>(lhs);
//  } else {
//    const auto l = lhs;
//  }
//  if constexpr (std::is_unsigned_v<std::remove_reference_t<Rhs>>) {
//    const auto r = std::make_signed_t<std::remove_reference_t<Rhs>>(rhs);
//  } else {
//    const auto r = rhs;
//  }
  const auto d = lhs - rhs;
  if constexpr (std::is_unsigned_v<decltype(d)>) {
    const auto ds = std::make_signed_t<decltype(d)>(d);
    return ds < 0 ? -ds : ds;
  } else {
    return d < 0 ? -d : d;
  }
}

template <typename... Params>
constexpr auto Threshold<Params...>::checkAll(
    const auto& d,
    const auto& params
  ) {
    return [&d, &params]<std::size_t... Is>(std::index_sequence<Is...>) {
      return ((std::get<Is>(d) <= std::get<Is>(params)) && ...);
    }(std::index_sequence_for<Params...>());
  };

} /// namespace mfl

#endif /// MFL_THRESHOLD_HH_
