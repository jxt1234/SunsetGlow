/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: SGCompute.SR.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "SGCompute.SR.pb-c.h"
void   sgcompute__sr__work_info__file_info__init
                     (SGCompute__SR__WorkInfo__FileInfo         *message)
{
  static SGCompute__SR__WorkInfo__FileInfo init_value = SGCOMPUTE__SR__WORK_INFO__FILE_INFO__INIT;
  *message = init_value;
}
void   sgcompute__sr__work_info__init
                     (SGCompute__SR__WorkInfo         *message)
{
  static SGCompute__SR__WorkInfo init_value = SGCOMPUTE__SR__WORK_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__sr__work_info__get_packed_size
                     (const SGCompute__SR__WorkInfo *message)
{
  assert(message->base.descriptor == &sgcompute__sr__work_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__sr__work_info__pack
                     (const SGCompute__SR__WorkInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__sr__work_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__sr__work_info__pack_to_buffer
                     (const SGCompute__SR__WorkInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__sr__work_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__SR__WorkInfo *
       sgcompute__sr__work_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__SR__WorkInfo *)
     protobuf_c_message_unpack (&sgcompute__sr__work_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__sr__work_info__free_unpacked
                     (SGCompute__SR__WorkInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__sr__work_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__sr__run_info__unit__init
                     (SGCompute__SR__RunInfo__Unit         *message)
{
  static SGCompute__SR__RunInfo__Unit init_value = SGCOMPUTE__SR__RUN_INFO__UNIT__INIT;
  *message = init_value;
}
void   sgcompute__sr__run_info__init
                     (SGCompute__SR__RunInfo         *message)
{
  static SGCompute__SR__RunInfo init_value = SGCOMPUTE__SR__RUN_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__sr__run_info__get_packed_size
                     (const SGCompute__SR__RunInfo *message)
{
  assert(message->base.descriptor == &sgcompute__sr__run_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__sr__run_info__pack
                     (const SGCompute__SR__RunInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__sr__run_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__sr__run_info__pack_to_buffer
                     (const SGCompute__SR__RunInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__sr__run_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__SR__RunInfo *
       sgcompute__sr__run_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__SR__RunInfo *)
     protobuf_c_message_unpack (&sgcompute__sr__run_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__sr__run_info__free_unpacked
                     (SGCompute__SR__RunInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__sr__run_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__sr__result_info__init
                     (SGCompute__SR__ResultInfo         *message)
{
  static SGCompute__SR__ResultInfo init_value = SGCOMPUTE__SR__RESULT_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__sr__result_info__get_packed_size
                     (const SGCompute__SR__ResultInfo *message)
{
  assert(message->base.descriptor == &sgcompute__sr__result_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__sr__result_info__pack
                     (const SGCompute__SR__ResultInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__sr__result_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__sr__result_info__pack_to_buffer
                     (const SGCompute__SR__ResultInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__sr__result_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__SR__ResultInfo *
       sgcompute__sr__result_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__SR__ResultInfo *)
     protobuf_c_message_unpack (&sgcompute__sr__result_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__sr__result_info__free_unpacked
                     (SGCompute__SR__ResultInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__sr__result_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   sgcompute__sr__registor_info__init
                     (SGCompute__SR__RegistorInfo         *message)
{
  static SGCompute__SR__RegistorInfo init_value = SGCOMPUTE__SR__REGISTOR_INFO__INIT;
  *message = init_value;
}
size_t sgcompute__sr__registor_info__get_packed_size
                     (const SGCompute__SR__RegistorInfo *message)
{
  assert(message->base.descriptor == &sgcompute__sr__registor_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t sgcompute__sr__registor_info__pack
                     (const SGCompute__SR__RegistorInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &sgcompute__sr__registor_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t sgcompute__sr__registor_info__pack_to_buffer
                     (const SGCompute__SR__RegistorInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &sgcompute__sr__registor_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SGCompute__SR__RegistorInfo *
       sgcompute__sr__registor_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SGCompute__SR__RegistorInfo *)
     protobuf_c_message_unpack (&sgcompute__sr__registor_info__descriptor,
                                allocator, len, data);
}
void   sgcompute__sr__registor_info__free_unpacked
                     (SGCompute__SR__RegistorInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &sgcompute__sr__registor_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor sgcompute__sr__work_info__file_info__field_descriptors[3] =
{
  {
    "key_dimesion",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(SGCompute__SR__WorkInfo__FileInfo, n_key_dimesion),
    offsetof(SGCompute__SR__WorkInfo__FileInfo, key_dimesion),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "path",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo__FileInfo, path),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo__FileInfo, type),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__work_info__file_info__field_indices_by_name[] = {
  0,   /* field[0] = key_dimesion */
  1,   /* field[1] = path */
  2,   /* field[2] = type */
};
static const ProtobufCIntRange sgcompute__sr__work_info__file_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor sgcompute__sr__work_info__file_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.WorkInfo.FileInfo",
  "FileInfo",
  "SGCompute__SR__WorkInfo__FileInfo",
  "SGCompute.SR",
  sizeof(SGCompute__SR__WorkInfo__FileInfo),
  3,
  sgcompute__sr__work_info__file_info__field_descriptors,
  sgcompute__sr__work_info__file_info__field_indices_by_name,
  1,  sgcompute__sr__work_info__file_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__work_info__file_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue sgcompute__sr__work_info__type__enum_values_by_number[2] =
{
  { "MAP", "SGCOMPUTE__SR__WORK_INFO__TYPE__MAP", 0 },
  { "REDUCE", "SGCOMPUTE__SR__WORK_INFO__TYPE__REDUCE", 1 },
};
static const ProtobufCIntRange sgcompute__sr__work_info__type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex sgcompute__sr__work_info__type__enum_values_by_name[2] =
{
  { "MAP", 0 },
  { "REDUCE", 1 },
};
const ProtobufCEnumDescriptor sgcompute__sr__work_info__type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "SGCompute.SR.WorkInfo.TYPE",
  "TYPE",
  "SGCompute__SR__WorkInfo__TYPE",
  "SGCompute.SR",
  2,
  sgcompute__sr__work_info__type__enum_values_by_number,
  2,
  sgcompute__sr__work_info__type__enum_values_by_name,
  1,
  sgcompute__sr__work_info__type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const SGCompute__SR__WorkInfo__TYPE sgcompute__sr__work_info__type__default_value = SGCOMPUTE__SR__WORK_INFO__TYPE__MAP;
static const ProtobufCFieldDescriptor sgcompute__sr__work_info__field_descriptors[6] =
{
  {
    "inputs",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(SGCompute__SR__WorkInfo, n_inputs),
    offsetof(SGCompute__SR__WorkInfo, inputs),
    &sgcompute__sr__work_info__file_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "output",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo, output),
    &sgcompute__sr__work_info__file_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo, type),
    &sgcompute__sr__work_info__type__descriptor,
    &sgcompute__sr__work_info__type__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "formula",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo, formula),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "inputTypes",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo, inputtypes),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "parameters",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__WorkInfo, parameters),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__work_info__field_indices_by_name[] = {
  3,   /* field[3] = formula */
  4,   /* field[4] = inputTypes */
  0,   /* field[0] = inputs */
  1,   /* field[1] = output */
  5,   /* field[5] = parameters */
  2,   /* field[2] = type */
};
static const ProtobufCIntRange sgcompute__sr__work_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor sgcompute__sr__work_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.WorkInfo",
  "WorkInfo",
  "SGCompute__SR__WorkInfo",
  "SGCompute.SR",
  sizeof(SGCompute__SR__WorkInfo),
  6,
  sgcompute__sr__work_info__field_descriptors,
  sgcompute__sr__work_info__field_indices_by_name,
  1,  sgcompute__sr__work_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__work_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__sr__run_info__unit__field_descriptors[2] =
{
  {
    "inputKeys",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(SGCompute__SR__RunInfo__Unit, n_inputkeys),
    offsetof(SGCompute__SR__RunInfo__Unit, inputkeys),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "outputKeys",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(SGCompute__SR__RunInfo__Unit, n_outputkeys),
    offsetof(SGCompute__SR__RunInfo__Unit, outputkeys),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__run_info__unit__field_indices_by_name[] = {
  0,   /* field[0] = inputKeys */
  1,   /* field[1] = outputKeys */
};
static const ProtobufCIntRange sgcompute__sr__run_info__unit__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__sr__run_info__unit__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.RunInfo.Unit",
  "Unit",
  "SGCompute__SR__RunInfo__Unit",
  "SGCompute.SR",
  sizeof(SGCompute__SR__RunInfo__Unit),
  2,
  sgcompute__sr__run_info__unit__field_descriptors,
  sgcompute__sr__run_info__unit__field_indices_by_name,
  1,  sgcompute__sr__run_info__unit__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__run_info__unit__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor sgcompute__sr__run_info__field_descriptors[2] =
{
  {
    "work_content",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(SGCompute__SR__RunInfo, n_work_content),
    offsetof(SGCompute__SR__RunInfo, work_content),
    &sgcompute__sr__run_info__unit__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "work_magic",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__RunInfo, work_magic),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__run_info__field_indices_by_name[] = {
  0,   /* field[0] = work_content */
  1,   /* field[1] = work_magic */
};
static const ProtobufCIntRange sgcompute__sr__run_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__sr__run_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.RunInfo",
  "RunInfo",
  "SGCompute__SR__RunInfo",
  "SGCompute.SR",
  sizeof(SGCompute__SR__RunInfo),
  2,
  sgcompute__sr__run_info__field_descriptors,
  sgcompute__sr__run_info__field_indices_by_name,
  1,  sgcompute__sr__run_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__run_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue sgcompute__sr__result_info__status__enum_values_by_number[2] =
{
  { "SUCCESS", "SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS", 0 },
  { "FAILED", "SGCOMPUTE__SR__RESULT_INFO__STATUS__FAILED", 1 },
};
static const ProtobufCIntRange sgcompute__sr__result_info__status__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex sgcompute__sr__result_info__status__enum_values_by_name[2] =
{
  { "FAILED", 1 },
  { "SUCCESS", 0 },
};
const ProtobufCEnumDescriptor sgcompute__sr__result_info__status__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "SGCompute.SR.ResultInfo.STATUS",
  "STATUS",
  "SGCompute__SR__ResultInfo__STATUS",
  "SGCompute.SR",
  2,
  sgcompute__sr__result_info__status__enum_values_by_number,
  2,
  sgcompute__sr__result_info__status__enum_values_by_name,
  1,
  sgcompute__sr__result_info__status__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const SGCompute__SR__ResultInfo__STATUS sgcompute__sr__result_info__status__default_value = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
static const ProtobufCFieldDescriptor sgcompute__sr__result_info__field_descriptors[3] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__ResultInfo, status),
    &sgcompute__sr__result_info__status__descriptor,
    &sgcompute__sr__result_info__status__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "message",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__ResultInfo, message),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "magic",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__ResultInfo, magic),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__result_info__field_indices_by_name[] = {
  2,   /* field[2] = magic */
  1,   /* field[1] = message */
  0,   /* field[0] = status */
};
static const ProtobufCIntRange sgcompute__sr__result_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor sgcompute__sr__result_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.ResultInfo",
  "ResultInfo",
  "SGCompute__SR__ResultInfo",
  "SGCompute.SR",
  sizeof(SGCompute__SR__ResultInfo),
  3,
  sgcompute__sr__result_info__field_descriptors,
  sgcompute__sr__result_info__field_indices_by_name,
  1,  sgcompute__sr__result_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__result_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue sgcompute__sr__registor_info__type__enum_values_by_number[2] =
{
  { "LOCAL", "SGCOMPUTE__SR__REGISTOR_INFO__TYPE__LOCAL", 0 },
  { "TCP", "SGCOMPUTE__SR__REGISTOR_INFO__TYPE__TCP", 1 },
};
static const ProtobufCIntRange sgcompute__sr__registor_info__type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex sgcompute__sr__registor_info__type__enum_values_by_name[2] =
{
  { "LOCAL", 0 },
  { "TCP", 1 },
};
const ProtobufCEnumDescriptor sgcompute__sr__registor_info__type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "SGCompute.SR.RegistorInfo.TYPE",
  "TYPE",
  "SGCompute__SR__RegistorInfo__TYPE",
  "SGCompute.SR",
  2,
  sgcompute__sr__registor_info__type__enum_values_by_number,
  2,
  sgcompute__sr__registor_info__type__enum_values_by_name,
  1,
  sgcompute__sr__registor_info__type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const SGCompute__SR__RegistorInfo__TYPE sgcompute__sr__registor_info__type__default_value = SGCOMPUTE__SR__REGISTOR_INFO__TYPE__LOCAL;
static const ProtobufCFieldDescriptor sgcompute__sr__registor_info__field_descriptors[2] =
{
  {
    "info",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__RegistorInfo, info),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(SGCompute__SR__RegistorInfo, type),
    &sgcompute__sr__registor_info__type__descriptor,
    &sgcompute__sr__registor_info__type__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned sgcompute__sr__registor_info__field_indices_by_name[] = {
  0,   /* field[0] = info */
  1,   /* field[1] = type */
};
static const ProtobufCIntRange sgcompute__sr__registor_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor sgcompute__sr__registor_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.RegistorInfo",
  "RegistorInfo",
  "SGCompute__SR__RegistorInfo",
  "SGCompute.SR",
  sizeof(SGCompute__SR__RegistorInfo),
  2,
  sgcompute__sr__registor_info__field_descriptors,
  sgcompute__sr__registor_info__field_indices_by_name,
  1,  sgcompute__sr__registor_info__number_ranges,
  (ProtobufCMessageInit) sgcompute__sr__registor_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCMethodDescriptor sgcompute__sr__compute_responser__method_descriptors[3] =
{
  { "CreateWork", &sgcompute__sr__work_info__descriptor, &sgcompute__sr__result_info__descriptor },
  { "RunWork", &sgcompute__sr__run_info__descriptor, &sgcompute__sr__result_info__descriptor },
  { "ReleaseWork", &sgcompute__sr__result_info__descriptor, &sgcompute__sr__result_info__descriptor },
};
const unsigned sgcompute__sr__compute_responser__method_indices_by_name[] = {
  0,        /* CreateWork */
  2,        /* ReleaseWork */
  1         /* RunWork */
};
const ProtobufCServiceDescriptor sgcompute__sr__compute_responser__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.ComputeResponser",
  "ComputeResponser",
  "SGCompute__SR__ComputeResponser",
  "SGCompute.SR",
  3,
  sgcompute__sr__compute_responser__method_descriptors,
  sgcompute__sr__compute_responser__method_indices_by_name
};
void sgcompute__sr__compute_responser__create_work(ProtobufCService *service,
                                                   const SGCompute__SR__WorkInfo *input,
                                                   SGCompute__SR__ResultInfo_Closure closure,
                                                   void *closure_data)
{
  assert(service->descriptor == &sgcompute__sr__compute_responser__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__sr__compute_responser__run_work(ProtobufCService *service,
                                                const SGCompute__SR__RunInfo *input,
                                                SGCompute__SR__ResultInfo_Closure closure,
                                                void *closure_data)
{
  assert(service->descriptor == &sgcompute__sr__compute_responser__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__sr__compute_responser__release_work(ProtobufCService *service,
                                                    const SGCompute__SR__ResultInfo *input,
                                                    SGCompute__SR__ResultInfo_Closure closure,
                                                    void *closure_data)
{
  assert(service->descriptor == &sgcompute__sr__compute_responser__descriptor);
  service->invoke(service, 2, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__sr__compute_responser__init (SGCompute__SR__ComputeResponser_Service *service,
                                             SGCompute__SR__ComputeResponser_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &sgcompute__sr__compute_responser__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
static const ProtobufCMethodDescriptor sgcompute__sr__compute_server_waiter__method_descriptors[2] =
{
  { "ReportSuccess", &sgcompute__sr__result_info__descriptor, &sgcompute__sr__result_info__descriptor },
  { "Registor", &sgcompute__sr__registor_info__descriptor, &sgcompute__sr__result_info__descriptor },
};
const unsigned sgcompute__sr__compute_server_waiter__method_indices_by_name[] = {
  1,        /* Registor */
  0         /* ReportSuccess */
};
const ProtobufCServiceDescriptor sgcompute__sr__compute_server_waiter__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "SGCompute.SR.ComputeServerWaiter",
  "ComputeServerWaiter",
  "SGCompute__SR__ComputeServerWaiter",
  "SGCompute.SR",
  2,
  sgcompute__sr__compute_server_waiter__method_descriptors,
  sgcompute__sr__compute_server_waiter__method_indices_by_name
};
void sgcompute__sr__compute_server_waiter__report_success(ProtobufCService *service,
                                                          const SGCompute__SR__ResultInfo *input,
                                                          SGCompute__SR__ResultInfo_Closure closure,
                                                          void *closure_data)
{
  assert(service->descriptor == &sgcompute__sr__compute_server_waiter__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__sr__compute_server_waiter__registor(ProtobufCService *service,
                                                    const SGCompute__SR__RegistorInfo *input,
                                                    SGCompute__SR__ResultInfo_Closure closure,
                                                    void *closure_data)
{
  assert(service->descriptor == &sgcompute__sr__compute_server_waiter__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void sgcompute__sr__compute_server_waiter__init (SGCompute__SR__ComputeServerWaiter_Service *service,
                                                 SGCompute__SR__ComputeServerWaiter_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &sgcompute__sr__compute_server_waiter__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
