#include "App.hpp"

#pragma comment(lib, "ws2_32.lib")

void run(std::string host, v_uint16 port)
{
    /* Register Components in scope of run() method */
    AppComponent components(host, port);

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    oatpp::web::server::api::Endpoints docEndpoints;

    docEndpoints.append(router->addController(ExampleController::createShared())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Priny info about server port */
    OATPP_LOGI("Example App", "Server running on %s: %s", connectionProvider->getProperty("host").toString()->c_str(), connectionProvider->getProperty("port").toString()->c_str());

    /* Run server */
    server.run();
}

int main(int argc, const char *argv[])
{
    v_uint16 port = 80;

    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    /* Init oatpp Environment */
    oatpp::base::Environment::init();

    /* Run App */
    run("0.0.0.0", port);

    /* Destroy oatpp Environment */
    oatpp::base::Environment::destroy();

    return 0;
}