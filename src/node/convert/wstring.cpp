#include <codecvt>
#include <locale>
#include <yaml-cpp/node/convert/wstring.h>
#include <yaml-cpp/node/impl.h>

using namespace YAML;

Node convert<std::wstring>::encode(const std::wstring& t) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return Node(converter.to_bytes(t));
}

bool convert<std::wstring>::decode(const Node& node, std::wstring& t) {
  if (!node.IsScalar())
    return false;
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  t = converter.from_bytes(node.Scalar());
  return true;
}
