/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: SGCompute.CS.proto */

#ifndef PROTOBUF_C_SGCompute_2eCS_2eproto__INCLUDED
#define PROTOBUF_C_SGCompute_2eCS_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1002001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _SGCompute__CS__PieceInfo SGCompute__CS__PieceInfo;
typedef struct _SGCompute__CS__ComputeInfo SGCompute__CS__ComputeInfo;
typedef struct _SGCompute__CS__ComputeInfo__FuncInfo SGCompute__CS__ComputeInfo__FuncInfo;
typedef struct _SGCompute__CS__ComputeInfo__FormulaInfo SGCompute__CS__ComputeInfo__FormulaInfo;
typedef struct _SGCompute__CS__ComputeInfo__KeyInfo SGCompute__CS__ComputeInfo__KeyInfo;
typedef struct _SGCompute__CS__ComputeInfo__KeyInfo__Key SGCompute__CS__ComputeInfo__KeyInfo__Key;
typedef struct _SGCompute__CS__Result SGCompute__CS__Result;


/* --- enums --- */

typedef enum _SGCompute__CS__Result__StatusCode {
  SGCOMPUTE__CS__RESULT__STATUS_CODE__SUCCESS = 1,
  SGCOMPUTE__CS__RESULT__STATUS_CODE__FAIL = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(SGCOMPUTE__CS__RESULT__STATUS_CODE)
} SGCompute__CS__Result__StatusCode;

/* --- messages --- */

struct  _SGCompute__CS__PieceInfo
{
  ProtobufCMessage base;
  char *describe;
  char *type;
  size_t n_keydimesion;
  uint32_t *keydimesion;
};
#define SGCOMPUTE__CS__PIECE_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__piece_info__descriptor) \
    , NULL, NULL, 0,NULL }


struct  _SGCompute__CS__ComputeInfo__FuncInfo
{
  ProtobufCMessage base;
  char *formula;
  char *parameter;
  char *inputstype;
};
#define SGCOMPUTE__CS__COMPUTE_INFO__FUNC_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__compute_info__func_info__descriptor) \
    , NULL, NULL, NULL }


struct  _SGCompute__CS__ComputeInfo__FormulaInfo
{
  ProtobufCMessage base;
  char *sconditionformula;
  char *svariableinfo;
};
#define SGCOMPUTE__CS__COMPUTE_INFO__FORMULA_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__compute_info__formula_info__descriptor) \
    , NULL, NULL }


struct  _SGCompute__CS__ComputeInfo__KeyInfo__Key
{
  ProtobufCMessage base;
  uint32_t index;
  uint32_t pos;
};
#define SGCOMPUTE__CS__COMPUTE_INFO__KEY_INFO__KEY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__compute_info__key_info__key__descriptor) \
    , 0, 0 }


struct  _SGCompute__CS__ComputeInfo__KeyInfo
{
  ProtobufCMessage base;
  size_t n_inputkey;
  SGCompute__CS__ComputeInfo__KeyInfo__Key **inputkey;
  size_t n_outputkey;
  SGCompute__CS__ComputeInfo__KeyInfo__Key **outputkey;
};
#define SGCOMPUTE__CS__COMPUTE_INFO__KEY_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__compute_info__key_info__descriptor) \
    , 0,NULL, 0,NULL }


struct  _SGCompute__CS__ComputeInfo
{
  ProtobufCMessage base;
  SGCompute__CS__ComputeInfo__FuncInfo *sfuncinfo;
  SGCompute__CS__ComputeInfo__FormulaInfo *sconditioninfo;
  SGCompute__CS__ComputeInfo__KeyInfo *skeyinfo;
  SGCompute__CS__PieceInfo *inputpiecedescribe;
  SGCompute__CS__PieceInfo *outputpiecedescribe;
};
#define SGCOMPUTE__CS__COMPUTE_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__compute_info__descriptor) \
    , NULL, NULL, NULL, NULL, NULL }


struct  _SGCompute__CS__Result
{
  ProtobufCMessage base;
  SGCompute__CS__Result__StatusCode code;
};
#define SGCOMPUTE__CS__RESULT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__result__descriptor) \
    , 0 }


/* SGCompute__CS__PieceInfo methods */
void   sgcompute__cs__piece_info__init
                     (SGCompute__CS__PieceInfo         *message);
size_t sgcompute__cs__piece_info__get_packed_size
                     (const SGCompute__CS__PieceInfo   *message);
size_t sgcompute__cs__piece_info__pack
                     (const SGCompute__CS__PieceInfo   *message,
                      uint8_t             *out);
size_t sgcompute__cs__piece_info__pack_to_buffer
                     (const SGCompute__CS__PieceInfo   *message,
                      ProtobufCBuffer     *buffer);
SGCompute__CS__PieceInfo *
       sgcompute__cs__piece_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   sgcompute__cs__piece_info__free_unpacked
                     (SGCompute__CS__PieceInfo *message,
                      ProtobufCAllocator *allocator);
/* SGCompute__CS__ComputeInfo__FuncInfo methods */
void   sgcompute__cs__compute_info__func_info__init
                     (SGCompute__CS__ComputeInfo__FuncInfo         *message);
/* SGCompute__CS__ComputeInfo__FormulaInfo methods */
void   sgcompute__cs__compute_info__formula_info__init
                     (SGCompute__CS__ComputeInfo__FormulaInfo         *message);
/* SGCompute__CS__ComputeInfo__KeyInfo__Key methods */
void   sgcompute__cs__compute_info__key_info__key__init
                     (SGCompute__CS__ComputeInfo__KeyInfo__Key         *message);
/* SGCompute__CS__ComputeInfo__KeyInfo methods */
void   sgcompute__cs__compute_info__key_info__init
                     (SGCompute__CS__ComputeInfo__KeyInfo         *message);
/* SGCompute__CS__ComputeInfo methods */
void   sgcompute__cs__compute_info__init
                     (SGCompute__CS__ComputeInfo         *message);
size_t sgcompute__cs__compute_info__get_packed_size
                     (const SGCompute__CS__ComputeInfo   *message);
size_t sgcompute__cs__compute_info__pack
                     (const SGCompute__CS__ComputeInfo   *message,
                      uint8_t             *out);
size_t sgcompute__cs__compute_info__pack_to_buffer
                     (const SGCompute__CS__ComputeInfo   *message,
                      ProtobufCBuffer     *buffer);
SGCompute__CS__ComputeInfo *
       sgcompute__cs__compute_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   sgcompute__cs__compute_info__free_unpacked
                     (SGCompute__CS__ComputeInfo *message,
                      ProtobufCAllocator *allocator);
/* SGCompute__CS__Result methods */
void   sgcompute__cs__result__init
                     (SGCompute__CS__Result         *message);
size_t sgcompute__cs__result__get_packed_size
                     (const SGCompute__CS__Result   *message);
size_t sgcompute__cs__result__pack
                     (const SGCompute__CS__Result   *message,
                      uint8_t             *out);
size_t sgcompute__cs__result__pack_to_buffer
                     (const SGCompute__CS__Result   *message,
                      ProtobufCBuffer     *buffer);
SGCompute__CS__Result *
       sgcompute__cs__result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   sgcompute__cs__result__free_unpacked
                     (SGCompute__CS__Result *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*SGCompute__CS__PieceInfo_Closure)
                 (const SGCompute__CS__PieceInfo *message,
                  void *closure_data);
typedef void (*SGCompute__CS__ComputeInfo__FuncInfo_Closure)
                 (const SGCompute__CS__ComputeInfo__FuncInfo *message,
                  void *closure_data);
typedef void (*SGCompute__CS__ComputeInfo__FormulaInfo_Closure)
                 (const SGCompute__CS__ComputeInfo__FormulaInfo *message,
                  void *closure_data);
typedef void (*SGCompute__CS__ComputeInfo__KeyInfo__Key_Closure)
                 (const SGCompute__CS__ComputeInfo__KeyInfo__Key *message,
                  void *closure_data);
typedef void (*SGCompute__CS__ComputeInfo__KeyInfo_Closure)
                 (const SGCompute__CS__ComputeInfo__KeyInfo *message,
                  void *closure_data);
typedef void (*SGCompute__CS__ComputeInfo_Closure)
                 (const SGCompute__CS__ComputeInfo *message,
                  void *closure_data);
typedef void (*SGCompute__CS__Result_Closure)
                 (const SGCompute__CS__Result *message,
                  void *closure_data);

/* --- services --- */

typedef struct _SGCompute__CS__ComputeServer_Service SGCompute__CS__ComputeServer_Service;
struct _SGCompute__CS__ComputeServer_Service
{
  ProtobufCService base;
  void (*by_info)(SGCompute__CS__ComputeServer_Service *service,
                  const SGCompute__CS__ComputeInfo *input,
                  SGCompute__CS__Result_Closure closure,
                  void *closure_data);
  void (*create)(SGCompute__CS__ComputeServer_Service *service,
                 const SGCompute__CS__PieceInfo *input,
                 SGCompute__CS__Result_Closure closure,
                 void *closure_data);
};
typedef void (*SGCompute__CS__ComputeServer_ServiceDestroy)(SGCompute__CS__ComputeServer_Service *);
void sgcompute__cs__compute_server__init (SGCompute__CS__ComputeServer_Service *service,
                                          SGCompute__CS__ComputeServer_ServiceDestroy destroy);
#define SGCOMPUTE__CS__COMPUTE_SERVER__BASE_INIT \
    { &sgcompute__cs__compute_server__descriptor, protobuf_c_service_invoke_internal, NULL }
#define SGCOMPUTE__CS__COMPUTE_SERVER__INIT(function_prefix__) \
    { SGCOMPUTE__CS__COMPUTE_SERVER__BASE_INIT,\
      function_prefix__ ## by_info,\
      function_prefix__ ## create  }
void sgcompute__cs__compute_server__by_info(ProtobufCService *service,
                                            const SGCompute__CS__ComputeInfo *input,
                                            SGCompute__CS__Result_Closure closure,
                                            void *closure_data);
void sgcompute__cs__compute_server__create(ProtobufCService *service,
                                           const SGCompute__CS__PieceInfo *input,
                                           SGCompute__CS__Result_Closure closure,
                                           void *closure_data);

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor sgcompute__cs__piece_info__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__compute_info__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__compute_info__func_info__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__compute_info__formula_info__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__compute_info__key_info__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__compute_info__key_info__key__descriptor;
extern const ProtobufCMessageDescriptor sgcompute__cs__result__descriptor;
extern const ProtobufCEnumDescriptor    sgcompute__cs__result__status_code__descriptor;
extern const ProtobufCServiceDescriptor sgcompute__cs__compute_server__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_SGCompute_2eCS_2eproto__INCLUDED */