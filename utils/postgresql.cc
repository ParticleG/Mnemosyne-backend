//
// Created by ParticleG on 2022/5/8.
//

#include <types/JsonValue.h>
#include <utils/postgresql.h>

using namespace std;
using namespace mnemosyne::helpers;
using namespace mnemosyne::utils;
using namespace mnemosyne::types;

string postgresql::toPgArray(const RequestJson &requestJson) {
    if (!requestJson.check(JsonValue::Array)) {
        return "{}";
    }
    auto serialized = requestJson.stringify();
    transform(serialized.begin(), serialized.end(), serialized.begin(), [](char c) {
        return c == '[' ? '{' : c == ']' ? '}' : c;
    });
    return serialized;
}
