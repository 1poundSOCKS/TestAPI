#include "pch.h"

#pragma warning (disable:4459)

#include "soapspProxy.h"
#include "sp.nsmap"

auto main(int argc, char* argv[]) -> int
{
  for( int arg = 0; arg < argc; ++arg )
  {
    std::cout << argv[arg] << '\n';
  }

  if( argc != 5 )
  {
    return 0;
  }

  struct soap* soap = soap_new();

  std::string url = argv[1];
  ns2__spLogin ns2__LoginRequest;
  ns2__LoginRequest.databaseUser = argv[2];
  ns2__LoginRequest.password = argv[3];
  ns2__LoginRequest.spUser = argv[4];
  ns2__LoginRequest.soap = soap;
  
  ns2__LoginResponse ns2__LoginResponse_;

  spProxy proxy;
  std::cout << proxy.Login(url.c_str(), "", &ns2__LoginRequest, ns2__LoginResponse_) << '\n';

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);

  return 0;
}
