//
// Created by particleg on 2021/10/2.
//

#pragma once

#include <drogon/drogon.h>
#include <types/JsonValue.h>
#include <types/ResultCode.h>

namespace mnemosyne::internal {
    class BaseException : public std::exception {
    public:
        explicit BaseException(std::string message);

        ~BaseException() noexcept override = default;

        [[nodiscard]] const char *what() const noexcept override;

    protected:
        const std::string _message;
    };

    class CodeException : public BaseException {
    public:
        explicit CodeException(std::string message, const int &code = 0);

        [[nodiscard]] const int &code() const noexcept;

    protected:
        const int _code;
    };
}

namespace mnemosyne::structures {
    class ResponseException : public internal::BaseException {
    public:
        explicit ResponseException(
                std::string message,
                const types::ResultCode &code = types::ResultCode::internalError,
                const drogon::HttpStatusCode &statusCode = drogon::HttpStatusCode::k500InternalServerError
        );

        explicit ResponseException(
                std::string message,
                const std::exception &e,
                const types::ResultCode &code = types::ResultCode::internalError,
                const drogon::HttpStatusCode &statusCode = drogon::HttpStatusCode::k500InternalServerError
        );

        [[nodiscard]] const types::ResultCode &code() const noexcept;

        [[nodiscard]] const drogon::HttpStatusCode &statusCode() const noexcept;

        [[nodiscard]] Json::Value toJson() const noexcept;

    private:
        const std::string _reason;
        const types::ResultCode _code;
        const drogon::HttpStatusCode _statusCode;
    };

    namespace json_exception {
        class InvalidFormat : public internal::BaseException {
        public:
            explicit InvalidFormat(std::string message);
        };

        class WrongType : public internal::BaseException {
        public:
            explicit WrongType(const types::JsonValue &valueType);
        };
    }

    namespace redis_exception {
        class KeyNotFound : public internal::BaseException {
        public:
            explicit KeyNotFound(std::string message);
        };

        class FieldNotFound : public internal::BaseException {
        public:
            explicit FieldNotFound(std::string message);
        };

        class NotEqual : public internal::BaseException {
        public:
            explicit NotEqual(std::string message);
        };
    }
}
