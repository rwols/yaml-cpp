#include "yaml-cpp/yaml.h"
#include "gtest/gtest.h"

namespace YAML {
namespace {

class EmitParseDecodeTest : public ::testing::Test {
 protected:
  template <class T>
  void check(const T& expected) {
    std::stringstream ss;
    Emitter out(ss);
    out << expected;                            // emit the thing
    const auto node = Load(ss.str());           // parse it
    const auto actual = node.template as<T>();  // then decode it back
    EXPECT_EQ(expected, actual);                // should equal the original
  }
};

// does exactly the same thing as a regular std::allocator, but it's just here
// for testing purposes.
template <class T>
class MockAllocator : public std::allocator<T> {};

template <class T>
using MockVector = std::vector<T, MockAllocator<T>>;

TEST_F(EmitParseDecodeTest, StdVector) {
  MockVector<int> primes;
  primes.push_back(2);
  primes.push_back(3);
  primes.push_back(5);
  primes.push_back(7);
  primes.push_back(11);
  primes.push_back(13);
  std::vector<int> sameprimes(primes.begin(), primes.end());
  check(primes);
  check(sameprimes);
}

TEST_F(EmitParseDecodeTest, StdVectorOfVectors) {
  MockVector<MockVector<int>> matrix;
  matrix.push_back(std::vector<int, MockAllocator<int>>{1, 0, 0});
  matrix.push_back(std::vector<int, MockAllocator<int>>{0, 1, 0});
  matrix.push_back(std::vector<int, MockAllocator<int>>{0, 0, 1});
  std::vector<std::vector<int>> samematrix;
  for (const auto& row : matrix)
    samematrix.push_back(std::vector<int>(row.begin(), row.end()));
  check(matrix);
  check(samematrix);
}

template <class T>
using MockDeque = std::deque<T, MockAllocator<T>>;

TEST_F(EmitParseDecodeTest, StdDeque) {
  MockDeque<int> primes;
  primes.push_back(2);
  primes.push_back(3);
  primes.push_back(5);
  primes.push_back(7);
  primes.push_back(11);
  primes.push_back(13);
  std::deque<int> sameprimes(primes.begin(), primes.end());
  check(primes);
  check(sameprimes);
}

template <class T>
using MockList = std::list<T, MockAllocator<T>>;

TEST_F(EmitParseDecodeTest, StdList) {
  MockList<int> primes;
  primes.push_back(2);
  primes.push_back(3);
  primes.push_back(5);
  primes.push_back(7);
  primes.push_back(11);
  primes.push_back(13);
  std::list<int> sameprimes(primes.begin(), primes.end());
  // check(primes);  // <--- this fails to compile for some reason
  check(sameprimes);
}

template <class T>
using MockForwardList = std::forward_list<T, MockAllocator<T>>;

TEST_F(EmitParseDecodeTest, StdForwardList) {
  MockForwardList<int> primes;
  primes.push_front(13);
  primes.push_front(11);
  primes.push_front(7);
  primes.push_front(5);
  primes.push_front(3);
  primes.push_front(2);
  std::forward_list<int> sameprimes(primes.begin(), primes.end());
  check(primes);
  check(sameprimes);
}

template <class Key, class T, class Compare = std::less<Key>>
using MockMap =
    std::map<Key, T, Compare, MockAllocator<std::pair<const Key, T>>>;

TEST_F(EmitParseDecodeTest, StdMapOfMaps) {
  MockMap<std::string, MockMap<std::string, int>> data;
  data["zero"] = MockMap<std::string, int>{{"john", 0}, {"doe", 1}};
  data["one"] = MockMap<std::string, int>{{"hello", 2}, {"world", 3}};
  check(data);
}

template <class Key, class T, class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key>>
using MockUnorderedMap =
    std::unordered_map<Key, T, Hash, KeyEqual,
                       MockAllocator<std::pair<const Key, T>>>;

TEST_F(EmitParseDecodeTest, StdUnorderedMap) {
  MockUnorderedMap<int, int> squares;
  squares[0] = 0;
  squares[1] = 1;
  squares[2] = 4;
  squares[3] = 9;
  squares[4] = 16;
  check(squares);
}

template <class Key, class Compare = std::less<Key>>
using MockSet = std::set<Key, Compare, MockAllocator<Key>>;

TEST_F(EmitParseDecodeTest, StdSet) {
  MockSet<int> primes;
  primes.insert(2);
  primes.insert(3);
  primes.insert(5);
  primes.insert(7);
  primes.insert(11);
  primes.insert(13);
  std::set<int> sameprimes(primes.begin(), primes.end());
  check(primes);
  check(sameprimes);
}

template <class Key, class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key>>
using MockUnorderedSet =
    std::unordered_set<Key, Hash, KeyEqual, MockAllocator<Key>>;

TEST_F(EmitParseDecodeTest, StdUnorderedSet) {
  MockUnorderedSet<int> primes;
  primes.insert(0);
  primes.insert(1);
  primes.insert(4);
  primes.insert(9);
  primes.insert(16);
  std::unordered_set<int> sameprimes(primes.begin(), primes.end());
  check(primes);
  check(sameprimes);
}

TEST_F(EmitParseDecodeTest, StdBitset) {
  std::bitset<8> bits;
  bits.set(0, true);
  bits.set(1, true);
  bits.set(2, false);
  bits.set(3, true);
  bits.set(4, true);
  bits.set(5, false);
  bits.set(6, false);
  bits.set(7, false);
  check(bits);
}

TEST_F(EmitParseDecodeTest, StdPair) {
  std::pair<int, std::string> p;
  p.first = 5;
  p.second = "five";
  check(p);
}

TEST_F(EmitParseDecodeTest, StdNestedNonsense) {
  std::map<std::string, std::pair<std::forward_list<std::bitset<2>>,
                                  std::vector<std::deque<std::string>>>>
      data;

  std::bitset<2> bits;
  bits.set(0, true);
  bits.set(1, false);

  std::forward_list<std::bitset<2>> thelist;
  thelist.push_front(bits);

  std::deque<std::string> thedeque;
  thedeque.push_back("hello");
  thedeque.push_back("world");

  std::vector<std::deque<std::string>> thevector;
  thevector.push_back(thedeque);
  thedeque[1] = "john";
  thedeque.push_back("kate");
  thevector.push_back(thedeque);

  data["one"] = std::make_pair(thelist, thevector);

  thelist.clear();
  bits.set(1, false);
  thelist.push_front(bits);
  bits.set(1, true);
  thelist.push_front(bits);

  thedeque.push_front("mary");
  thedeque.push_front("bob");
  thedeque.push_back("ellis");

  thevector.push_back(thedeque);

  data["two"] = std::make_pair(thelist, thevector);

  check(data);
}

TEST_F(EmitParseDecodeTest, VitaHomebrews) {
  /*
  homebrews:
    vita:
      - name: "PSP2048"
        author: dots-tb
      - name: "PSVident"
        author: Freakler
  */

  std::map<
      std::string,
      std::map<std::string, std::vector<std::map<std::string, std::string>>>>
      doc;

  std::map<std::string, std::string> nameAuthor;
  nameAuthor["name"] = "PSP2048";
  nameAuthor["author"] = "dots-tb";
  std::vector<std::map<std::string, std::string>> list;
  list.push_back(nameAuthor);
  nameAuthor["name"] = "PSVident";
  nameAuthor["author"] = "Freakler";
  list.push_back(nameAuthor);

  doc["homebrews"]["vita"] = list;

  check(doc);
}

}  // anonymous namespace
}  // namespace YAML
