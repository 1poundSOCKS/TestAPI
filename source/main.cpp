#include "pch.h"

#pragma warning (disable:4459)

#include "soapspProxy.h"
#include "sp.nsmap"

struct session_info
{
  session_info(soap* soap, const char* url) : soap { soap }, url { url }
  {
  }

  ~session_info()
  {
    soap_destroy(soap);
    soap_end(soap);
    soap_free(soap);
  }

  soap* soap;
  std::string url;
};

struct login_response
{
  int httpResponse;
  std::optional<unsigned int> apiResponse;
};

auto CallLogin(session_info& sessionInfo, const char* databaseUser, const char* password, const char* spUser) -> login_response
{
  ns2__spLogin ns2__LoginRequest;
  ns2__LoginRequest.databaseUser = databaseUser;
  ns2__LoginRequest.password = password;
  ns2__LoginRequest.spUser = spUser;
  ns2__LoginRequest.soap = sessionInfo.soap;
  
  ns2__LoginResponse ns2__LoginResponse_;

  login_response loginResponse;

  spProxy proxy;
  loginResponse.httpResponse = proxy.Login(sessionInfo.url.c_str(), "", &ns2__LoginRequest, ns2__LoginResponse_);

  if( loginResponse.httpResponse == 0 )
  {
    loginResponse.apiResponse = ns2__LoginResponse_.result->code;
  }

  return loginResponse;
}

auto main(int argc, char* argv[]) -> int
{
  for( int arg = 0; arg < argc; ++arg )
  {
    std::cout << argv[arg] << ' ';
  }

  std::cout << '\n';

  if( argc != 5 )
  {
    return 0;
  }

  session_info sessionInfo { soap_new(), argv[1] };

  auto loginResponse = CallLogin(sessionInfo, argv[2], argv[3], argv[4]);

  std::cout << std::string_view("HTTP result: ") << loginResponse.httpResponse << '\n';
  loginResponse.apiResponse ? std::cout << std::string_view("API result: ") << *loginResponse.apiResponse << '\n' : std::cout << std::string_view("API result missing") << '\n';

  return 0;
}
