#pragma once

#include <ArduinoJson.h>

class ArduinoJsonSchemaValidator {
public:
    ArduinoJsonSchemaValidator(const char* schemaJson);

    // Validate JSON document against loaded schema
    bool validate(const char* jsonDoc);

    // Optionally: overloaded validate
    bool validate(const JsonDocument& doc);

private:
    JsonDocument _schema;
    bool validateType(const JsonVariant& data, const char* expectedType);
    bool validateRequired(const JsonVariant& data, const JsonArray& required);
    bool validateProperties(const JsonVariant& data, const JsonObject& props);
};
