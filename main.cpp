#include <cstdio>
#include <fstream>
#include <iterator>
#include <stack>
#include <string>
// clang-format off

int main(int argc, const char *const argv[]) {
  using namespace std;
  if(argc < 2) {
    fprintf(stderr, "Usage: %s source\n", argv[0]);
    return 1;
  }

  ifstream fin{argv[1]};
  auto stream = string(istream_iterator<uint8_t>{fin}, {});
  stack<string::iterator> st;

  uint8_t cells[30'000]{};
  uint8_t *ptr = &cells[0];

  for(auto it = stream.begin(); it != stream.end(); ++it) {
    switch (*it) {
      case '>': ++ptr;                                            break;
      case '<': --ptr;                                            break;
      case '+': ++*ptr;                                           break;
      case '-': --*ptr;                                           break;
      case '.': putchar(*ptr);                                    break;
      case ',': *ptr = getchar();                                 break;
      case '[': if (*ptr) { st.push(it); }                        break;
      case ']': if (!*ptr) { st.pop(); } else { it = st.top(); }  break;
      default: break;
    }
  }
  return 0;
}

