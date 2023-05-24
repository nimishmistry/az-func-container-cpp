#pragma once

#ifndef DTO_HPP
#define DTO_HPP

#include <oatpp/web/server/HttpConnectionHandler.hpp>

#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/* TODO - Add more DTOs here */

namespace Example::DTO
{
    class Message : public oatpp::DTO
    {
        DTO_INIT(Message, DTO);

        DTO_FIELD(String, description);
    };
}

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif /* DTO_HPP */