#include <iostream>
#include <hv/HttpServer.h>
#include <hv/hthread.h>    // import hv_gettid
#include <hv/hasync.h>     // import hv::async
#include "router.h"
using namespace hv;

// http://127.0.0.1:8080/
// https://127.0.0.1:8443/

int main() {
    std::cout << "Hello, World!" << std::endl;

    HttpService router;
    Router::Register(router);
    

    HttpServer server;
    server.service = &router;
    server.port = 8080;
    server.https_port = 8443;

    hssl_ctx_opt_t param;
    memset(&param, 0, sizeof(param));
    param.crt_file = "cert/server.crt";
    param.key_file = "cert/server.key";
    param.endpoint = HSSL_SERVER;
    if (server.newSslCtx(&param) != 0) {
        fprintf(stderr, "new SSL_CTX failed!\n");
        return -20;
    }

    // uncomment to test multi-processes
   // server.setProcessNum(4);
   // uncomment to test multi-threads
   // server.setThreadNum(4);

    server.start();

    // press Enter to stop
    while (getchar() != '\n');
    hv::async::cleanup();

    //std::cin.get();
    return 0;
}


