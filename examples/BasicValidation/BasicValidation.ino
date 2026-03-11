#include <ArduinoJson.h>
#include <ArduinoJsonSchemaValidator.h>

const char* schema = R"({
  "type": "object",
  "properties": {
    "temperature": { "type": "number" },
    "unit": { "type": "string" }
  },
  "required": ["temperature", "unit"]
})";

const char* json = R"({
  "temperature": 21.2,
  "unit": "C"
})";

ArduinoJsonSchemaValidator validator(schema);

void setup() {
  Serial.begin(9600);
  bool valid = validator.validate(json);
  Serial.println(valid ? "Valid JSON" : "Invalid JSON");
}

void loop() {}
