#include "pch.h"

#pragma warning (disable:4459)

#include "soapspProxy.h"
#include "sp.nsmap"

auto main(int argc, char* argv[]) -> int
{
  std::cout << argc << '\n';
  std::cout << argv[0] << '\n';

  ns2__spLogin ns2__LoginRequest;
  ns2__LoginResponse ns2__LoginResponse_;
  
  spProxy proxy;
  proxy.Login(&ns2__LoginRequest, ns2__LoginResponse_);

  return 0;
}
