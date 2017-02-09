#include <limits>
#include <yaml-cpp/node/convert/unsigned_char.h>

using namespace YAML;

bool convert<unsigned char>::decode(const Node& node, unsigned char& t) {
  if (!node.IsScalar())
    return false;
  const auto& str = node.Scalar();
  std::size_t pos;
  std::size_t adjust;
  unsigned long x;
  try {
    if (str.length() > 2 && str[0] == '0') {
      if (str[1] == 'x' || str[1] == 'X') {
        // base 16
        x = std::stoul(str.substr(2), &pos, 16);
        adjust = 2;
      } else if (str[1] == 'o' || str[1] == 'O') {
        // base 8
        x = std::stoul(str.substr(2), &pos, 8);
        adjust = 2;
      } else {
        return false;
      }
    } else {
      // base 10
      x = std::stoul(str, &pos, 10);
      adjust = 0;
    }
  } catch (const std::exception& /*error*/) {
    return false;
  }
  // did we read the whole string?
  if (pos != str.length() - adjust)
    return false;
  if (x > std::numeric_limits<unsigned char>::max())
    return false;
  t = static_cast<unsigned short>(x);
  return true;
}
