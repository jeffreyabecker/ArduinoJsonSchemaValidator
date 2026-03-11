#include "ArduinoJsonSchemaValidator.h"

ArduinoJsonSchemaValidator::ArduinoJsonSchemaValidator(const char* schemaJson) {
    // Parse and store schema
    deserializeJson(_schema, schemaJson);
}

bool ArduinoJsonSchemaValidator::validate(const char* jsonDoc) {
    JsonDocument parsed;
    if (deserializeJson(parsed, jsonDoc) != DeserializationError::Ok) {
        return false;
    }
    return validate(parsed);
}

bool ArduinoJsonSchemaValidator::validate(const JsonDocument& doc) {
    JsonVariant data = doc.as<JsonVariant>();
    JsonObject schemaObj = _schema.as<JsonObject>();

    // Validate type
    if (schemaObj.containsKey("type")) {
        const char* expectedType = schemaObj["type"];
        if (!validateType(data, expectedType)) return false;
    }

    // Validate required
    if (schemaObj.containsKey("required")) {
        JsonArray required = schemaObj["required"];
        if (!validateRequired(data, required)) return false;
    }

    // Validate properties
    if (schemaObj.containsKey("properties")) {
        JsonObject props = schemaObj["properties"];
        if (!validateProperties(data, props)) return false;
    }

    // ... further keywords (stub)
    return true;
}

bool ArduinoJsonSchemaValidator::validateType(const JsonVariant& data, const char* expectedType) {
    if (strcmp(expectedType, "object") == 0) return data.is<JsonObject>();
    if (strcmp(expectedType, "array") == 0) return data.is<JsonArray>();
    if (strcmp(expectedType, "string") == 0) return data.is<const char*>();
    if (strcmp(expectedType, "number") == 0) return data.is<float>() || data.is<double>() || data.is<int>() || data.is<long>();
    if (strcmp(expectedType, "boolean") == 0) return data.is<bool>();
    // ... add more types as needed
    return false;
}

bool ArduinoJsonSchemaValidator::validateRequired(const JsonVariant& data, const JsonArray& required) {
    if (!data.is<JsonObject>()) return false;
    JsonObject obj = data.as<JsonObject>();
    for (const char* key : required) {
        if (!obj.containsKey(key)) return false;
    }
    return true;
}

bool ArduinoJsonSchemaValidator::validateProperties(const JsonVariant& data, const JsonObject& props) {
    if (!data.is<JsonObject>()) return false;
    JsonObject obj = data.as<JsonObject>();
    for (JsonObject::iterator it = props.begin(); it != props.end(); ++it) {
        const char* key = it->key().c_str();
        JsonObject propSchema = it->value().as<JsonObject>();
        if (obj.containsKey(key)) {
            // Minimal: Only 'type'
            if (propSchema.containsKey("type")) {
                if (!validateType(obj[key], propSchema["type"])) return false;
            }
            // ... add support for additional keywords as needed
        }
    }
    return true;
}