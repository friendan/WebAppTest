#include <hv/hthread.h>  // import hv_gettid
#include <hv/hasync.h>   // import hv::async
#include <hv/requests.h> // import requests::async
#include "router.h"
#include "handler.h"

void Router::Register(hv::HttpService& router) {
    Handler::HttpService(router);
    /* handler chain */
    // headerHandler -> preprocessor -> middleware -> processor -> postprocessor
    // processor: pathHandlers -> staticHandler -> errorHandler
    router.headerHandler = Handler::headerHandler;
    router.preprocessor = Handler::preprocessor;
    router.postprocessor = Handler::postprocessor;
    router.mitmhandler = Handler::mitmhandler;
    // router.errorHandler = Handler::errorHandler;
    // router.largeFileHandler = Handler::sendLargeFile;

    // middleware
    // router.Use(Handler::Authorization);

    // router.Static("/", "./html");
    // router.Proxy("/baidu/", "https://www.baidu.com/");

    // middleware
    router.AllowCORS();
    router.Use([](HttpRequest* req, HttpResponse* resp) {
        resp->SetHeader("X-Request-tid", hv::to_string(hv_gettid()));
        return HTTP_STATUS_NEXT;
    });
    
}
