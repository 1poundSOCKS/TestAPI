#include "pch.h"

#pragma warning (disable:4459)

#include "soapspProxy.h"
#include "sp.nsmap"

auto main(int argc, char* argv[]) -> int
{
  std::cout << argc << '\n';
  std::cout << argv[0] << '\n';

  spProxy proxy;

  return 0;
}
