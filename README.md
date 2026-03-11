# ArduinoJsonSchemaValidator

JSON Schema validation library for [ArduinoJson](https://github.com/bblanchon/ArduinoJson).  
Validate JSON documents against [JSON Schema](https://json-schema.org/) using C++ in Arduino and embedded environments.

## Features

- Basic [JSON Schema](https://json-schema.org/) keyword support (`type`, `properties`, `required`)
- Simple API for schema validation
- Designed for memory-constrained devices

## Example

```cpp
#include <ArduinoJsonSchemaValidator.h>
#include <ArduinoJson.h>

const char* schemaStr = R"({
  "type": "object",
  "properties": {
    "temperature": { "type": "number" },
    "unit": { "type": "string" }
  },
  "required": ["temperature", "unit"]
})";

const char* jsonStr = R"({
  "temperature": 25.0,
  "unit": "C"
})";

ArduinoJsonSchemaValidator validator(schemaStr);
bool valid = validator.validate(jsonStr);
if (valid) {
  Serial.println("Valid!");
} else {
  Serial.println("Invalid!");
}
```

## Installation

1. Clone this repository
2. Add `src/` to your Arduino sketch or platform

## License

MIT
