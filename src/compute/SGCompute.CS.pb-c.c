/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: SGCompute.CS.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "SGCompute.CS.pb-c.h"
void   sgcompute__cs__piece_info__init
                     (SGCompute__CS__PieceInfo         *message)
{
  static SGCompute__CS__PieceInfo init_value = SGCOMPUTE__CS__PIECE_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__cs__piece_info__get_packed_size
                     (const SGCompute__CS__PieceInfo *message)
{
  assert(message->base.descriptor == &sgcompute__cs__piece_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__piece_info__pack
                     (const SGCompute__CS__PieceInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__piece_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__piece_info__pack_to_buffer
                     (const SGCompute__CS__PieceInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__piece_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__PieceInfo *
       sgcompute__cs__piece_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__PieceInfo *)
     protobuf_c_message_unpack (&sgcompute__cs__piece_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__piece_info__free_unpacked
                     (SGCompute__CS__PieceInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__piece_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__cs__compute_info__init
                     (SGCompute__CS__ComputeInfo         *message)
{
  static SGCompute__CS__ComputeInfo init_value = SGCOMPUTE__CS__COMPUTE_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__cs__compute_info__get_packed_size
                     (const SGCompute__CS__ComputeInfo *message)
{
  assert(message->base.descriptor == &sgcompute__cs__compute_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__compute_info__pack
                     (const SGCompute__CS__ComputeInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__compute_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__compute_info__pack_to_buffer
                     (const SGCompute__CS__ComputeInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__compute_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__ComputeInfo *
       sgcompute__cs__compute_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__ComputeInfo *)
     protobuf_c_message_unpack (&sgcompute__cs__compute_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__compute_info__free_unpacked
                     (SGCompute__CS__ComputeInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__compute_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__cs__execute_info__key__init
                     (SGCompute__CS__ExecuteInfo__Key         *message)
{
  static SGCompute__CS__ExecuteInfo__Key init_value = SGCOMPUTE__CS__EXECUTE_INFO__KEY__INIT;
  *message = init_value;
}
void   sgcompute__cs__execute_info__func_info__init
                     (SGCompute__CS__ExecuteInfo__FuncInfo         *message)
{
  static SGCompute__CS__ExecuteInfo__FuncInfo init_value = SGCOMPUTE__CS__EXECUTE_INFO__FUNC_INFO__INIT;
  *message = init_value;
}
void   sgcompute__cs__execute_info__formula_info__init
                     (SGCompute__CS__ExecuteInfo__FormulaInfo         *message)
{
  static SGCompute__CS__ExecuteInfo__FormulaInfo init_value = SGCOMPUTE__CS__EXECUTE_INFO__FORMULA_INFO__INIT;
  *message = init_value;
}
void   sgcompute__cs__execute_info__init
                     (SGCompute__CS__ExecuteInfo         *message)
{
  static SGCompute__CS__ExecuteInfo init_value = SGCOMPUTE__CS__EXECUTE_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__cs__execute_info__get_packed_size
                     (const SGCompute__CS__ExecuteInfo *message)
{
  assert(message->base.descriptor == &sgcompute__cs__execute_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__execute_info__pack
                     (const SGCompute__CS__ExecuteInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__execute_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__execute_info__pack_to_buffer
                     (const SGCompute__CS__ExecuteInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__execute_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__ExecuteInfo *
       sgcompute__cs__execute_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__ExecuteInfo *)
     protobuf_c_message_unpack (&sgcompute__cs__execute_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__execute_info__free_unpacked
                     (SGCompute__CS__ExecuteInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__execute_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__cs__file_content__init
                     (SGCompute__CS__FileContent         *message)
{
  static SGCompute__CS__FileContent init_value = SGCOMPUTE__CS__FILE_CONTENT__INIT;
  *message = init_value;
}
size_t sgcompute__cs__file_content__get_packed_size
                     (const SGCompute__CS__FileContent *message)
{
  assert(message->base.descriptor == &sgcompute__cs__file_content__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__file_content__pack
                     (const SGCompute__CS__FileContent *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__file_content__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__file_content__pack_to_buffer
                     (const SGCompute__CS__FileContent *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__file_content__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__FileContent *
       sgcompute__cs__file_content__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__FileContent *)
     protobuf_c_message_unpack (&sgcompute__cs__file_content__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__file_content__free_unpacked
                     (SGCompute__CS__FileContent *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__file_content__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__cs__result__init
                     (SGCompute__CS__Result         *message)
{
  static SGCompute__CS__Result init_value = SGCOMPUTE__CS__RESULT__INIT;
  *message = init_value;
}
size_t sgcompute__cs__result__get_packed_size
                     (const SGCompute__CS__Result *message)
{
  assert(message->base.descriptor == &sgcompute__cs__result__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__result__pack
                     (const SGCompute__CS__Result *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__result__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__result__pack_to_buffer
                     (const SGCompute__CS__Result *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__result__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__Result *
       sgcompute__cs__result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__Result *)
     protobuf_c_message_unpack (&sgcompute__cs__result__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__result__free_unpacked
                     (SGCompute__CS__Result *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__result__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__cs__copy_info__init
                     (SGCompute__CS__CopyInfo         *message)
{
  static SGCompute__CS__CopyInfo init_value = SGCOMPUTE__CS__COPY_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__cs__copy_info__get_packed_size
                     (const SGCompute__CS__CopyInfo *message)
{
  assert(message->base.descriptor == &sgcompute__cs__copy_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__cs__copy_info__pack
                     (const SGCompute__CS__CopyInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__cs__copy_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__cs__copy_info__pack_to_buffer
                     (const SGCompute__CS__CopyInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__cs__copy_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__CS__CopyInfo *
       sgcompute__cs__copy_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__CS__CopyInfo *)
     protobuf_c_message_unpack (&sgcompute__cs__copy_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__cs__copy_info__free_unpacked
                     (SGCompute__CS__CopyInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__cs__copy_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor sgcompute__cs__piece_info__field_descriptors[4] =
{
  {
    "path",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__PieceInfo, path),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "datatype",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__PieceInfo, datatype),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pieceType",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__PieceInfo, piecetype),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "keyDimesion",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(SGCompute__CS__PieceInfo, n_keydimesion),
    offsetof(SGCompute__CS__PieceInfo, keydimesion),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__piece_info__field_indices_by_name[] = {
  1,   /* field[1] = datatype */
  3,   /* field[3] = keyDimesion */
  0,   /* field[0] = path */
  2,   /* field[2] = pieceType */
};
static const ProtobufCIntRange sgcompute__cs__piece_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor sgcompute__cs__piece_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.PieceInfo",
  "PieceInfo",
  "SGCompute__CS__PieceInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__PieceInfo),
  4,
  sgcompute__cs__piece_info__field_descriptors,
  sgcompute__cs__piece_info__field_indices_by_name,
  1,  sgcompute__cs__piece_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__piece_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__compute_info__field_descriptors[3] =
{
  {
    "executor",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ComputeInfo, executor),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "inputPieces",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(SGCompute__CS__ComputeInfo, n_inputpieces),
    offsetof(SGCompute__CS__ComputeInfo, inputpieces),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "outputPiece",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ComputeInfo, outputpiece),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__compute_info__field_indices_by_name[] = {
  0,   /* field[0] = executor */
  1,   /* field[1] = inputPieces */
  2,   /* field[2] = outputPiece */
};
static const ProtobufCIntRange sgcompute__cs__compute_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor sgcompute__cs__compute_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ComputeInfo",
  "ComputeInfo",
  "SGCompute__CS__ComputeInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__ComputeInfo),
  3,
  sgcompute__cs__compute_info__field_descriptors,
  sgcompute__cs__compute_info__field_indices_by_name,
  1,  sgcompute__cs__compute_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__compute_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__execute_info__key__field_descriptors[2] =
{
  {
    "index",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__Key, index),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pos",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__Key, pos),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__execute_info__key__field_indices_by_name[] = {
  0,   /* field[0] = index */
  1,   /* field[1] = pos */
};
static const ProtobufCIntRange sgcompute__cs__execute_info__key__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__cs__execute_info__key__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ExecuteInfo.Key",
  "Key",
  "SGCompute__CS__ExecuteInfo__Key",
  "SGCompute.CS",
  sizeof(SGCompute__CS__ExecuteInfo__Key),
  2,
  sgcompute__cs__execute_info__key__field_descriptors,
  sgcompute__cs__execute_info__key__field_indices_by_name,
  1,  sgcompute__cs__execute_info__key__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__execute_info__key__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__execute_info__func_info__field_descriptors[4] =
{
  {
    "formula",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__FuncInfo, formula),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "parameter",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__FuncInfo, parameter),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "inputsType",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__FuncInfo, inputstype),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "variableKey",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(SGCompute__CS__ExecuteInfo__FuncInfo, n_variablekey),
    offsetof(SGCompute__CS__ExecuteInfo__FuncInfo, variablekey),
    &sgcompute__cs__execute_info__key__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__execute_info__func_info__field_indices_by_name[] = {
  0,   /* field[0] = formula */
  2,   /* field[2] = inputsType */
  1,   /* field[1] = parameter */
  3,   /* field[3] = variableKey */
};
static const ProtobufCIntRange sgcompute__cs__execute_info__func_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor sgcompute__cs__execute_info__func_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ExecuteInfo.FuncInfo",
  "FuncInfo",
  "SGCompute__CS__ExecuteInfo__FuncInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__ExecuteInfo__FuncInfo),
  4,
  sgcompute__cs__execute_info__func_info__field_descriptors,
  sgcompute__cs__execute_info__func_info__field_indices_by_name,
  1,  sgcompute__cs__execute_info__func_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__execute_info__func_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__execute_info__formula_info__field_descriptors[2] =
{
  {
    "sConditionFormula",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__FormulaInfo, sconditionformula),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sVariableInfo",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo__FormulaInfo, svariableinfo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__execute_info__formula_info__field_indices_by_name[] = {
  0,   /* field[0] = sConditionFormula */
  1,   /* field[1] = sVariableInfo */
};
static const ProtobufCIntRange sgcompute__cs__execute_info__formula_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__cs__execute_info__formula_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ExecuteInfo.FormulaInfo",
  "FormulaInfo",
  "SGCompute__CS__ExecuteInfo__FormulaInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__ExecuteInfo__FormulaInfo),
  2,
  sgcompute__cs__execute_info__formula_info__field_descriptors,
  sgcompute__cs__execute_info__formula_info__field_indices_by_name,
  1,  sgcompute__cs__execute_info__formula_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__execute_info__formula_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__execute_info__field_descriptors[4] =
{
  {
    "sFuncInfo",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo, sfuncinfo),
    &sgcompute__cs__execute_info__func_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sConditionInfo",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo, sconditioninfo),
    &sgcompute__cs__execute_info__formula_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "outputKey",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(SGCompute__CS__ExecuteInfo, n_outputkey),
    offsetof(SGCompute__CS__ExecuteInfo, outputkey),
    &sgcompute__cs__execute_info__key__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__ExecuteInfo, type),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__execute_info__field_indices_by_name[] = {
  2,   /* field[2] = outputKey */
  1,   /* field[1] = sConditionInfo */
  0,   /* field[0] = sFuncInfo */
  3,   /* field[3] = type */
};
static const ProtobufCIntRange sgcompute__cs__execute_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor sgcompute__cs__execute_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ExecuteInfo",
  "ExecuteInfo",
  "SGCompute__CS__ExecuteInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__ExecuteInfo),
  4,
  sgcompute__cs__execute_info__field_descriptors,
  sgcompute__cs__execute_info__field_indices_by_name,
  1,  sgcompute__cs__execute_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__execute_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__file_content__field_descriptors[2] =
{
  {
    "contents",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    offsetof(SGCompute__CS__FileContent, has_contents),
    offsetof(SGCompute__CS__FileContent, contents),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "file_name",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__FileContent, file_name),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__file_content__field_indices_by_name[] = {
  0,   /* field[0] = contents */
  1,   /* field[1] = file_name */
};
static const ProtobufCIntRange sgcompute__cs__file_content__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__cs__file_content__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.FileContent",
  "FileContent",
  "SGCompute__CS__FileContent",
  "SGCompute.CS",
  sizeof(SGCompute__CS__FileContent),
  2,
  sgcompute__cs__file_content__field_descriptors,
  sgcompute__cs__file_content__field_indices_by_name,
  1,  sgcompute__cs__file_content__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__file_content__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__result__field_descriptors[2] =
{
  {
    "code",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__Result, code),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "magic",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__Result, magic),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__result__field_indices_by_name[] = {
  0,   /* field[0] = code */
  1,   /* field[1] = magic */
};
static const ProtobufCIntRange sgcompute__cs__result__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__cs__result__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.Result",
  "Result",
  "SGCompute__CS__Result",
  "SGCompute.CS",
  sizeof(SGCompute__CS__Result),
  2,
  sgcompute__cs__result__field_descriptors,
  sgcompute__cs__result__field_indices_by_name,
  1,  sgcompute__cs__result__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__result__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__cs__copy_info__field_descriptors[2] =
{
  {
    "read_magic",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__CopyInfo, read_magic),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "write_magic",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__CS__CopyInfo, write_magic),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__cs__copy_info__field_indices_by_name[] = {
  0,   /* field[0] = read_magic */
  1,   /* field[1] = write_magic */
};
static const ProtobufCIntRange sgcompute__cs__copy_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__cs__copy_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.CopyInfo",
  "CopyInfo",
  "SGCompute__CS__CopyInfo",
  "SGCompute.CS",
  sizeof(SGCompute__CS__CopyInfo),
  2,
  sgcompute__cs__copy_info__field_descriptors,
  sgcompute__cs__copy_info__field_indices_by_name,
  1,  sgcompute__cs__copy_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__cs__copy_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCMethodDescriptor sgcompute__cs__compute_server__method_descriptors[7] =
{
  { "CreateExecutor", &sgcompute__cs__execute_info__descriptor, &sgcompute__cs__result__descriptor },
  { "Execute", &sgcompute__cs__compute_info__descriptor, &sgcompute__cs__result__descriptor },
  { "Create", &sgcompute__cs__piece_info__descriptor, &sgcompute__cs__result__descriptor },
  { "Release", &sgcompute__cs__result__descriptor, &sgcompute__cs__result__descriptor },
  { "Copy", &sgcompute__cs__copy_info__descriptor, &sgcompute__cs__result__descriptor },
  { "Download", &sgcompute__cs__file_content__descriptor, &sgcompute__cs__file_content__descriptor },
  { "Upload", &sgcompute__cs__file_content__descriptor, &sgcompute__cs__file_content__descriptor },
};
const unsigned sgcompute__cs__compute_server__method_indices_by_name[] = {
  4,        /* Copy */
  2,        /* Create */
  0,        /* CreateExecutor */
  5,        /* Download */
  1,        /* Execute */
  3,        /* Release */
  6         /* Upload */
};
const ProtobufCServiceDescriptor sgcompute__cs__compute_server__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "SGCompute.CS.ComputeServer",
  "ComputeServer",
  "SGCompute__CS__ComputeServer",
  "SGCompute.CS",
  7,
  sgcompute__cs__compute_server__method_descriptors,
  sgcompute__cs__compute_server__method_indices_by_name
};
void sgcompute__cs__compute_server__create_executor(ProtobufCService *service,
                                                    const SGCompute__CS__ExecuteInfo *input,
                                                    SGCompute__CS__Result_Closure closure,
                                                    void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__execute(ProtobufCService *service,
                                            const SGCompute__CS__ComputeInfo *input,
                                            SGCompute__CS__Result_Closure closure,
                                            void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__create(ProtobufCService *service,
                                           const SGCompute__CS__PieceInfo *input,
                                           SGCompute__CS__Result_Closure closure,
                                           void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 2, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__release(ProtobufCService *service,
                                            const SGCompute__CS__Result *input,
                                            SGCompute__CS__Result_Closure closure,
                                            void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 3, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__copy(ProtobufCService *service,
                                         const SGCompute__CS__CopyInfo *input,
                                         SGCompute__CS__Result_Closure closure,
                                         void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 4, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__download(ProtobufCService *service,
                                             const SGCompute__CS__FileContent *input,
                                             SGCompute__CS__FileContent_Closure closure,
                                             void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 5, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__upload(ProtobufCService *service,
                                           const SGCompute__CS__FileContent *input,
                                           SGCompute__CS__FileContent_Closure closure,
                                           void *closure_data)
{
  assert(service->descriptor == &sgcompute__cs__compute_server__descriptor);
  service->invoke(service, 6, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__cs__compute_server__init (SGCompute__CS__ComputeServer_Service *service,
                                          SGCompute__CS__ComputeServer_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &sgcompute__cs__compute_server__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
