#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <jsi/jsi.h>

using namespace facebook::jsi;
using namespace std;

namespace example {
  int multiply(float a, float b);
  void install(Runtime & jsiRuntime) ;
}

#endif /* EXAMPLE_H */
