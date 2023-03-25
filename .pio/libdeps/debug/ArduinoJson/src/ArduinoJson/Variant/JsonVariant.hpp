// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2023, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Variant/VariantRefBase.hpp>

ARDUINOJSON_BEGIN_PUBLIC_NAMESPACE

// A reference to a value in a JsonDocument.
// https://arduinojson.org/v6/api/jsonvariant/
class JsonVariant : public detail::VariantRefBase<JsonVariant>,
                    public detail::VariantOperators<JsonVariant> {
  friend class detail::VariantAttorney;

 public:
  // Creates an unbound reference.
  JsonVariant() : _data(0), _pool(0) {}

  // INTERNAL USE ONLY
  JsonVariant(detail::MemoryPool* pool, detail::VariantData* data)
      : _data(data), _pool(pool) {}

 private:
  FORCE_INLINE detail::MemoryPool* getPool() const {
    return _pool;
  }

  FORCE_INLINE detail::VariantData* getData() const {
    return _data;
  }

  FORCE_INLINE detail::VariantData* getOrCreateData() const {
    return _data;
  }

  detail::VariantData* _data;
  detail::MemoryPool* _pool;
};

template <>
struct Converter<JsonVariant> : private detail::VariantAttorney {
  static void toJson(JsonVariant src, JsonVariant dst) {
    detail::variantCopyFrom(getData(dst), getData(src), getPool(dst));
  }

  static JsonVariant fromJson(JsonVariant src) {
    return src;
  }

  static detail::InvalidConversion<JsonVariantConst, JsonVariant> fromJson(
      JsonVariantConst);

  static bool checkJson(JsonVariant src) {
    auto data = getData(src);
    return !!data;
  }

  static bool checkJson(JsonVariantConst) {
    return false;
  }
};

template <>
struct Converter<JsonVariantConst> : private detail::VariantAttorney {
  static void toJson(JsonVariantConst src, JsonVariant dst) {
    variantCopyFrom(getData(dst), getData(src), getPool(dst));
  }

  static JsonVariantConst fromJson(JsonVariantConst src) {
    return JsonVariantConst(getData(src));
  }

  static bool checkJson(JsonVariantConst src) {
    auto data = getData(src);
    return !!data;
  }
};

ARDUINOJSON_END_PUBLIC_NAMESPACE
