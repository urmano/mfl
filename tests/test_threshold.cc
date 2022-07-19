#include <mfl/mfl.hxx>
#include <cassert>

int main() {
  assert(mfl::Threshold(.03, 1)(3.14, 0l, 3.12f, 1ull) == true);
  assert(mfl::Threshold(.03, 1)(3.14, 0l, 3.10f, 1ull) == false);
  assert(mfl::Threshold(.03, 1)(3.14, 0l, 3.12f, 2ull) == false);
  assert(mfl::Threshold(.03, 1)(3.14, 0l, 3.10f, 2ull) == false);

  assert(mfl::Threshold(.03, 1)(std::make_tuple(3.14, 0l), std::make_tuple(3.12f, 1ull)) == true);
  assert(mfl::Threshold(.03, 1)(std::make_tuple(3.14, 0l), std::make_tuple(3.10f, 1ull)) == false);
  assert(mfl::Threshold(.03, 1)(std::make_tuple(3.14, 0l), std::make_tuple(3.12f, 2ull)) == false);
  assert(mfl::Threshold(.03, 1)(std::make_tuple(3.14, 0l), std::make_tuple(3.10f, 2ull)) == false);

}
