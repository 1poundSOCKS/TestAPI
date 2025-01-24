#include "pch.h"

#pragma warning (disable:4459)

#include "common_soap.h"
#include "common/common_defs.h"

struct login_response
{
  int httpResponse;
  std::optional<unsigned int> apiResponse;
};

auto CallLogin(session_info& sessionInfo, auth_info& authInfo) -> login_response
{
  ns2__spLogin ns2__LoginRequest;
  ns2__LoginRequest.databaseUser = authInfo.databaseUser;
  ns2__LoginRequest.password = authInfo.password;
  ns2__LoginRequest.spUser = authInfo.spUser;
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

  if( argc != 1 )
  {
    return 0;
  }

  auto config = LoadDefaultConfig();

  session_info sessionInfo { soap_new(), config.url.c_str() };
  auth_info authInfo { config.databaseUser.c_str(), config.password.c_str(), config.spUser.c_str() };

  auto loginResponse = CallLogin(sessionInfo, authInfo);

  std::cout << std::string_view("HTTP result: ") << loginResponse.httpResponse << '\n';
  loginResponse.apiResponse ? std::cout << std::string_view("API result: ") << *loginResponse.apiResponse << '\n' : std::cout << std::string_view("API result missing") << '\n';

  return 0;
}
