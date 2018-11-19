#include <string>
#include <cstdlib>
#include <cstdio>

#include "conversion.h"


namespace gbenchmarkexample {


std::string IntToString(int v) {
  char buf[sizeof(int) * 8 / 3 + 1];
  int pos = 0;

  while (v > 10) {
    int r = v % 10;
    v /= 10;

    buf[pos] = '0' + static_cast<char>(r);
    pos++;
  }

  if (v > 0) {
    buf[pos] = '0' + static_cast<char>(v);
    pos++;
  }

  // reverse buf
  for (int i0 = 0, i1 = pos - 1; i0 < i1; i0++, i1--) {
    char ch = buf[i0];
    buf[i0] = buf[i1];
    buf[i1] = ch;
  }

  std::string s(buf, pos);
  return s;
}


}
