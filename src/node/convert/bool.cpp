#include <yaml-cpp/node/convert/bool.h>

using namespace YAML;

bool convert<bool>::decode(const Node& node, bool& b) {

  if (!node.IsScalar() || node.Scalar().empty())
    return false;
  const auto& str = node.Scalar();
  const char* s = str.data();
  switch (*s) {
    case 'y':
      if (str.length() == 1) {
        b = true;
        return true;
      } else if (str.length() != 3) {  // 3 == strlen("yes")
        return false;
      } else if (std::strcmp(s + 1, "es") != 0) {
        return false;
      } else {
        b = true;
        return true;
      }
    case 'Y':
      if (str.length() == 1) {
        b = true;
        return true;
      } else if (str.length() != 3) {  // 3 == strlen("Yes")
        return false;
      } else if (std::strcmp(s + 1, "es") == 0 ||
                 std::strcmp(s + 1, "ES") == 0) {
        b = true;
        return true;
      } else {
        return false;
      }
    case 'n':
      if (str.length() == 1) {
        b = false;
        return true;
      } else if (str.length() != 2) {  // 2 == strlen("no")
        return false;
      } else if (*(s + 1) != 'o') {
        return false;
      } else {
        b = false;
        return true;
      }
    case 'N':
      if (str.length() == 1) {
        b = false;
        return true;
      } else if (str.length() != 2) {  // 2 == strlen("No")
        return false;
      } else if (*(s + 1) != 'o' || *(s + 1) != 'O') {
        return false;
      } else {
        b = false;
        return true;
      }
    case 't':
      if (str.length() != 4) {  // 4 == strlen("true")
        return false;
      } else if (std::strcmp(s + 1, "rue") != 0) {
        return false;
      } else {
        b = true;
        return true;
      }
    case 'T':
      if (str.length() != 4) {  // 4 == strlen("True")
        return false;
      } else if (std::strcmp(s + 1, "rue") == 0 ||
                 std::strcmp(s + 1, "RUE") == 0) {
        b = true;
        return true;
      } else {
        return false;
      }
    case 'f':
      if (str.length() != 5) {  // 5 == strlen("false")
        return false;
      } else if (std::strcmp(s + 1, "alse") == 0) {
        b = false;
        return true;
      } else {
        return false;
      }
    case 'F':
      if (str.length() != 5) {  // 5 == strlen("false")
        return false;
      } else if (std::strcmp(s + 1, "alse") == 0 ||
                 std::strcmp(s + 1, "ALSE") == 0) {
        b = false;
        return true;
      } else {
        return false;
      }
    case 'o':
      if (str.length() == 2 && *(s + 1) == 'n') {
        b = true;
        return true;
      } else if (str.length() == 3 && std::strcmp(s + 1, "ff") == 0) {
        b = false;
        return true;
      } else {
        return false;
      }
    case 'O':
      if (str.length() == 2) {
        if (*(s + 1) == 'n' || *(s + 1) == 'N') {
          b = true;
          return true;
        } else {
          return false;
        }
      } else if (str.length() == 3) {
        if (std::strcmp(s + 1, "ff") == 0 || std::strcmp(s + 1, "FF") == 0) {
          b = false;
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    default:
      return false;
  }
}
