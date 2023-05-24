#pragma once

#ifndef APP_COMPONENT_HPP
#define APP_COMPONENT_HPP

#include <string>

#include <oatpp/network/tcp/server/ConnectionProvider.hpp>

#include <oatpp/web/server/HttpConnectionHandler.hpp>

#include <oatpp-swagger/Controller.hpp>

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent
{

private:
    std::string m_host;
    v_uint16 m_port;

public:
    AppComponent(const std::string host, const v_uint16 port) : m_port(port), m_host(host) {}

    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
        ("example-service", [this]
            { return oatpp::network::tcp::server::ConnectionProvider::createShared({ m_host, m_port, oatpp::network::Address::IP_4 }); }());

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
        ([]
            { return oatpp::web::server::HttpRouter::createShared(); }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
        ([]
            {
                OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
                return oatpp::web::server::HttpConnectionHandler::createShared(router);
            }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
        ([]
            { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());

    /**
 *  General API docs info
 */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
        ("example-service", [this]
            {
                oatpp::swagger::DocumentInfo::Builder builder;

                builder
                    .setTitle("Example API")
                    .setDescription("Provides example API")
                    .setVersion("0.0.1")
                    .setContactName("Powered by Example")
                    .setContactUrl("https://www.example.com/")
                    .addServer("http://localhost:" + std::to_string(m_port), "Local server");

                return builder.build();
            }());

    /**
     *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)
        ([]
            {
                // Make sure to specify correct full path to oatpp-swagger/res folder !!!
                return oatpp::swagger::Resources::loadResources("external/oatpp/res");
            }());
};

#endif /* APP_COMPONENT_HPP */