#include <yaml-cpp/node/convert/unsigned_long_long.h>

using namespace YAML;

bool convert<unsigned long long>::decode(const Node& node,
                                         unsigned long long& t) {
  if (!node.IsScalar())
    return false;
  const auto& str = node.Scalar();
  std::size_t pos;
  std::size_t adjust;
  try {
    if (str.length() > 2 && str[0] == '0') {
      if (str[1] == 'x' || str[1] == 'X') {
        // base 16
        t = std::stoull(str.substr(2), &pos, 16);
        adjust = 2;
      } else if (str[1] == 'o' || str[1] == 'O') {
        // base 8
        t = std::stoull(str.substr(2), &pos, 8);
        adjust = 2;
      } else {
        return false;
      }
    } else {
      // base 10
      t = std::stoull(str, &pos, 10);
      adjust = 0;
    }
  } catch (const std::exception& /*error*/) {
    return false;
  }
  // did we read the whole string?
  if (pos != str.length() - adjust)
    return false;
  return true;
}
