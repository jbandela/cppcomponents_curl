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
#include <cppcomponents_libcurl_libuv/http_client.hpp>
#include <cppcomponents_async_coroutine_wrapper/cppcomponents_resumable_await.hpp>
#include <cppcomponents_libuv/cppcomponents_libuv.hpp>
#include <cppcomponents/loop_executor.hpp>

#include <iostream>
#include <assert.h>

using namespace cppcomponents_libcurl_libuv;

bool test_get(cppcomponents::awaiter await){

    HttpClient client;
    Request req("http://httbin.org/get");
    //req.ConnectTimeout = 5;
    //req.RequestTimeout = 10;
    auto response = await(client.Fetch(req));

    auto str = response.ErrorMessage();

    return true;
}

int async_main(cppcomponents::awaiter await){
    await(cppcomponents::resumable(test_get)());
    cppcomponents_libcurl_libuv::HttpClient client;
    auto response = await(client.Fetch("https://www.google.com/"));
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
    new char[50];
    auto am = cppcomponents::resumable(async_main);
    am().Then([&exec](cppcomponents::Future<int> f){
        exec.MakeLoopExit();
    });
    exec.Loop();
    std::cerr << "Completed successfully\n";
    return 0;
}



