//
// Created by particleg on 2021/10/2.
//

#include <helpers/ResponseJson.h>
#include <magic_enum.hpp>
#include <structures/Exceptions.h>

using namespace drogon;
using namespace magic_enum;
using namespace std;
using namespace mnemosyne::helpers;
using namespace mnemosyne::internal;
using namespace mnemosyne::structures;
using namespace mnemosyne::types;

BaseException::BaseException(string message) : _message(move(message)) {}

char const *BaseException::what() const noexcept { return _message.c_str(); }

CodeException::CodeException(string message, const int &code) :
        BaseException(move(message)), _code(code) {}

const int &CodeException::code() const noexcept { return _code; }

ResponseException::ResponseException(
        string message,
        const ResultCode &code,
        const drogon::HttpStatusCode &statusCode
) : BaseException(move(message)), _code(code), _statusCode(statusCode) {}

ResponseException::ResponseException(
        string message,
        const exception &e,
        const ResultCode &code,
        const HttpStatusCode &statusCode
) : BaseException(move(message)), _code(code), _statusCode(statusCode), _reason(e.what()) {}

const ResultCode &ResponseException::code() const noexcept { return _code; }

const drogon::HttpStatusCode &ResponseException::statusCode() const noexcept { return _statusCode; }

Json::Value ResponseException::toJson() const noexcept {
    ResponseJson result;
    result.setResultCode(_code);
    result.setMessage(_message);
    if (!_reason.empty()) {
        result.setReason(_reason);
    }
    return result.ref();
}

json_exception::InvalidFormat::InvalidFormat(std::string message) :
        BaseException(move(message)) {}

json_exception::WrongType::WrongType(const JsonValue &valueType) :
        BaseException(string(enum_name(valueType))) {}

redis_exception::KeyNotFound::KeyNotFound(string message) :
        BaseException(move(message)) {}

redis_exception::FieldNotFound::FieldNotFound(string message) :
        BaseException(move(message)) {}

redis_exception::NotEqual::NotEqual(string message) :
        BaseException(move(message)) {}
