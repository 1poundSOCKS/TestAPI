#include "pch.h"

#pragma warning (disable:4459)

#include "soapspProxy.h"
#include "sp.nsmap"
#include "common_defs.h"

struct getjob_response
{
  int httpResponse;
  std::optional<unsigned int> apiResponse;
};

auto CallGetJob(session_info& sessionInfo, auth_info& authInfo, const char* jobRef) -> getjob_response
{
  ns2__GetJobRequest request;
  request.soap = sessionInfo.soap;
  request.login = new ns2__spLogin;
  request.login->databaseUser = authInfo.databaseUser;
  request.login->password = authInfo.password;
  request.login->spUser = authInfo.spUser;
  request.jobID = jobRef;

  ns2__GetJobResponse getjobResponse;

  getjob_response response;

  spProxy proxy;
  response.httpResponse = proxy.GetJob(sessionInfo.url.c_str(), "", &request, getjobResponse);

  if( response.httpResponse == 0 )
  {
    response.apiResponse = getjobResponse.result->code;
  }

  return response;
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
  auth_info authInfo { argv[2], argv[3], argv[4] };

  auto getJobResponse = CallGetJob(sessionInfo, authInfo, "autoGUI_ob_1");

  std::cout << std::string_view("HTTP result: ") << getJobResponse.httpResponse << '\n';
  getJobResponse.apiResponse ? std::cout << std::string_view("API result: ") << *getJobResponse.apiResponse << '\n' : std::cout << std::string_view("API result missing") << '\n';

  return 0;
}
