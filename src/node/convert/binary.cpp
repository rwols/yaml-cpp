#include <yaml-cpp/binary.h>
#include <yaml-cpp/node/convert/binary.h>

using namespace YAML;

Node convert<Binary>::encode(const Binary& rhs) {
  return Node(EncodeBase64(rhs.data(), rhs.size()));
}

bool convert<Binary>::decode(const Node& node, Binary& rhs) {
  if (!node.IsScalar())
    return false;

  std::vector<unsigned char> data = DecodeBase64(node.Scalar());
  if (data.empty() && !node.Scalar().empty())
    return false;

  rhs.swap(data);
  return true;
}
