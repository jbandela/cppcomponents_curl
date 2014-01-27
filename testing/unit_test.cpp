// Leak check detection with MSVC
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

namespace{
    struct MemLeakCheckInit{
        MemLeakCheckInit(){
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
            //_crtBreakAlloc = 437;
        }
    };

    MemLeakCheckInit mlcinit;
}
#endif
#include <cppcomponents_curl/curl_client.hpp>
#include <cppcomponents_async_coroutine_wrapper/cppcomponents_resumable_await.hpp>
#include <cppcomponents/loop_executor.hpp>

#include <iostream>
#include <assert.h>

using namespace cppcomponents_curl;

bool test_get(cppcomponents::awaiter await){

    CurlClient client;
    Request req("https://www.google.com");
    //req.ConnectTimeout = 5;
    //req.RequestTimeout = 10;
	req.DownloadFileName = "down.htm";
    auto response = await(client.Fetch(req));

    auto str = response.ErrorMessage();
	auto body = response.Body().to_string();

    return true;
}

int async_main(cppcomponents::awaiter await){
    await(cppcomponents::resumable(test_get)());
    cppcomponents_curl::CurlClient client;
	auto response = await(client.Fetch("ftp://sailor.gutenberg.lib.md.us/gutenberg/8/81/81-h/81-h.htm"));
    std::string str;
    if (response.ErrorCode() < 0){
        str = "Error: " + response.ErrorMessage().to_string();
    }
    else{
        str = response.Body().to_string();

    }
    auto rc = response.ResponseCode();
    auto headers = response.Headers();
    return 0;

}

int main(){
    cppcomponents::LoopExecutor exec;
    auto am = cppcomponents::resumable(async_main);
    am().Then([&exec](cppcomponents::Future<int> f){
        exec.MakeLoopExit();
    });
    exec.Loop();
    std::cerr << "Completed successfully\n";
    return 0;
}



