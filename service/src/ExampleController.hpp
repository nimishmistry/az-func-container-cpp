#pragma once

#ifndef EXAMPLE_CONTROLLER_HPP
#define EXAMPLE_CONTROLLER_HPP

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include <oatpp/web/server/api/ApiController.hpp>

#include <oatpp-swagger/Controller.hpp>

#include "DTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

/**
 * Sample Api Controller.
 */
class ExampleController : public oatpp::web::server::api::ApiController
{
public:
    /**
     * Constructor with object mapper.
     * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
     */
    ExampleController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }

    static std::shared_ptr<ExampleController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    )
    {
        return std::make_shared<ExampleController>(objectMapper);
    }

public:
    ENDPOINT_INFO(root)
    {
        info->summary = "Gets a greeting";
        info->addResponse<Object<Example::DTO::Message>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("GET", "/greeting", root)
    {
        auto response = Example::DTO::Message::createShared();
        response->description = "Hello World...!!!";

        return createDtoResponse(Status::CODE_200, response);
    }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen

#endif /* EXAMPLE_CONTROLLER_HPP */