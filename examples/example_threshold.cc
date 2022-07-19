#include <mfl/mfl.hxx>
#include <iostream>
#include <string>
#include <any>
#include <chrono>

int main() {
  constexpr auto paramAThreshold = .03;
  constexpr auto paramBThreshold = 1;
  constexpr auto threshold = mfl::Threshold(paramAThreshold, paramBThreshold);
  constexpr auto paramAExpected = 3.14;
//  constexpr auto paramAReal = 3.11f; // @note absolute value of (3.14 - 3.11) not always == 0.03
  constexpr auto paramAReal = 3.12f;
  constexpr auto paramBExpected = 0l;
//  constexpr auto paramBReal = 1ll; // works fine
  constexpr auto paramBReal = 1ull; // @note it is possible to use unsigned and signed together
//  constexpr auto resWithTuples = threshold(std::make_tuple(std::any(), b1), std::make_tuple(std::any(), b2)); //! should not and does not compile
  constexpr auto resWithTuples = threshold(std::tie(paramAExpected, paramBExpected), std::tie(paramAReal, paramBReal)); //! also may be used // prints true
//  constexpr auto res = threshold(std::any(), b1, std::any(), b2); //! should not and does not compile
  constexpr bool res = threshold(paramAExpected, paramBExpected, paramAReal, paramBReal);
  std::cout << std::boolalpha << res << std::endl; // prints "true"

}
