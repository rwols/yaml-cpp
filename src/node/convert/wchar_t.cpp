#include <codecvt>
#include <locale>
#include <yaml-cpp/node/convert/wchar_t.h>
#include <yaml-cpp/node/impl.h>

using namespace YAML;

Node convert<wchar_t>::encode(const wchar_t t) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return Node(converter.to_bytes(t));
}

bool convert<wchar_t>::decode(const Node& node, wchar_t& t) {
  if (!node.IsScalar())
    return false;
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  const auto wstr = converter.from_bytes(node.Scalar());
  if (wstr.length() != 1)
    return false;
  t = wstr[0];
  return true;
}
