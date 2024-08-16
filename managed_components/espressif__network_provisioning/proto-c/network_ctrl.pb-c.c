/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: network_ctrl.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "network_ctrl.pb-c.h"
void   cmd_ctrl_wifi_reset__init
                     (CmdCtrlWifiReset         *message)
{
  static const CmdCtrlWifiReset init_value = CMD_CTRL_WIFI_RESET__INIT;
  *message = init_value;
}
size_t cmd_ctrl_wifi_reset__get_packed_size
                     (const CmdCtrlWifiReset *message)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t cmd_ctrl_wifi_reset__pack
                     (const CmdCtrlWifiReset *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t cmd_ctrl_wifi_reset__pack_to_buffer
                     (const CmdCtrlWifiReset *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
CmdCtrlWifiReset *
       cmd_ctrl_wifi_reset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (CmdCtrlWifiReset *)
     protobuf_c_message_unpack (&cmd_ctrl_wifi_reset__descriptor,
                                allocator, len, data);
}
void   cmd_ctrl_wifi_reset__free_unpacked
                     (CmdCtrlWifiReset *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &cmd_ctrl_wifi_reset__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   resp_ctrl_wifi_reset__init
                     (RespCtrlWifiReset         *message)
{
  static const RespCtrlWifiReset init_value = RESP_CTRL_WIFI_RESET__INIT;
  *message = init_value;
}
size_t resp_ctrl_wifi_reset__get_packed_size
                     (const RespCtrlWifiReset *message)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t resp_ctrl_wifi_reset__pack
                     (const RespCtrlWifiReset *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t resp_ctrl_wifi_reset__pack_to_buffer
                     (const RespCtrlWifiReset *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reset__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RespCtrlWifiReset *
       resp_ctrl_wifi_reset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RespCtrlWifiReset *)
     protobuf_c_message_unpack (&resp_ctrl_wifi_reset__descriptor,
                                allocator, len, data);
}
void   resp_ctrl_wifi_reset__free_unpacked
                     (RespCtrlWifiReset *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &resp_ctrl_wifi_reset__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   cmd_ctrl_wifi_reprov__init
                     (CmdCtrlWifiReprov         *message)
{
  static const CmdCtrlWifiReprov init_value = CMD_CTRL_WIFI_REPROV__INIT;
  *message = init_value;
}
size_t cmd_ctrl_wifi_reprov__get_packed_size
                     (const CmdCtrlWifiReprov *message)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t cmd_ctrl_wifi_reprov__pack
                     (const CmdCtrlWifiReprov *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t cmd_ctrl_wifi_reprov__pack_to_buffer
                     (const CmdCtrlWifiReprov *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &cmd_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
CmdCtrlWifiReprov *
       cmd_ctrl_wifi_reprov__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (CmdCtrlWifiReprov *)
     protobuf_c_message_unpack (&cmd_ctrl_wifi_reprov__descriptor,
                                allocator, len, data);
}
void   cmd_ctrl_wifi_reprov__free_unpacked
                     (CmdCtrlWifiReprov *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &cmd_ctrl_wifi_reprov__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   resp_ctrl_wifi_reprov__init
                     (RespCtrlWifiReprov         *message)
{
  static const RespCtrlWifiReprov init_value = RESP_CTRL_WIFI_REPROV__INIT;
  *message = init_value;
}
size_t resp_ctrl_wifi_reprov__get_packed_size
                     (const RespCtrlWifiReprov *message)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t resp_ctrl_wifi_reprov__pack
                     (const RespCtrlWifiReprov *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t resp_ctrl_wifi_reprov__pack_to_buffer
                     (const RespCtrlWifiReprov *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &resp_ctrl_wifi_reprov__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RespCtrlWifiReprov *
       resp_ctrl_wifi_reprov__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RespCtrlWifiReprov *)
     protobuf_c_message_unpack (&resp_ctrl_wifi_reprov__descriptor,
                                allocator, len, data);
}
void   resp_ctrl_wifi_reprov__free_unpacked
                     (RespCtrlWifiReprov *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &resp_ctrl_wifi_reprov__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   cmd_ctrl_thread_reset__init
                     (CmdCtrlThreadReset         *message)
{
  static const CmdCtrlThreadReset init_value = CMD_CTRL_THREAD_RESET__INIT;
  *message = init_value;
}
size_t cmd_ctrl_thread_reset__get_packed_size
                     (const CmdCtrlThreadReset *message)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reset__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t cmd_ctrl_thread_reset__pack
                     (const CmdCtrlThreadReset *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reset__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t cmd_ctrl_thread_reset__pack_to_buffer
                     (const CmdCtrlThreadReset *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reset__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
CmdCtrlThreadReset *
       cmd_ctrl_thread_reset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (CmdCtrlThreadReset *)
     protobuf_c_message_unpack (&cmd_ctrl_thread_reset__descriptor,
                                allocator, len, data);
}
void   cmd_ctrl_thread_reset__free_unpacked
                     (CmdCtrlThreadReset *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &cmd_ctrl_thread_reset__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   resp_ctrl_thread_reset__init
                     (RespCtrlThreadReset         *message)
{
  static const RespCtrlThreadReset init_value = RESP_CTRL_THREAD_RESET__INIT;
  *message = init_value;
}
size_t resp_ctrl_thread_reset__get_packed_size
                     (const RespCtrlThreadReset *message)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reset__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t resp_ctrl_thread_reset__pack
                     (const RespCtrlThreadReset *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reset__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t resp_ctrl_thread_reset__pack_to_buffer
                     (const RespCtrlThreadReset *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reset__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RespCtrlThreadReset *
       resp_ctrl_thread_reset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RespCtrlThreadReset *)
     protobuf_c_message_unpack (&resp_ctrl_thread_reset__descriptor,
                                allocator, len, data);
}
void   resp_ctrl_thread_reset__free_unpacked
                     (RespCtrlThreadReset *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &resp_ctrl_thread_reset__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   cmd_ctrl_thread_reprov__init
                     (CmdCtrlThreadReprov         *message)
{
  static const CmdCtrlThreadReprov init_value = CMD_CTRL_THREAD_REPROV__INIT;
  *message = init_value;
}
size_t cmd_ctrl_thread_reprov__get_packed_size
                     (const CmdCtrlThreadReprov *message)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t cmd_ctrl_thread_reprov__pack
                     (const CmdCtrlThreadReprov *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t cmd_ctrl_thread_reprov__pack_to_buffer
                     (const CmdCtrlThreadReprov *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &cmd_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
CmdCtrlThreadReprov *
       cmd_ctrl_thread_reprov__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (CmdCtrlThreadReprov *)
     protobuf_c_message_unpack (&cmd_ctrl_thread_reprov__descriptor,
                                allocator, len, data);
}
void   cmd_ctrl_thread_reprov__free_unpacked
                     (CmdCtrlThreadReprov *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &cmd_ctrl_thread_reprov__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   resp_ctrl_thread_reprov__init
                     (RespCtrlThreadReprov         *message)
{
  static const RespCtrlThreadReprov init_value = RESP_CTRL_THREAD_REPROV__INIT;
  *message = init_value;
}
size_t resp_ctrl_thread_reprov__get_packed_size
                     (const RespCtrlThreadReprov *message)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t resp_ctrl_thread_reprov__pack
                     (const RespCtrlThreadReprov *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t resp_ctrl_thread_reprov__pack_to_buffer
                     (const RespCtrlThreadReprov *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &resp_ctrl_thread_reprov__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RespCtrlThreadReprov *
       resp_ctrl_thread_reprov__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RespCtrlThreadReprov *)
     protobuf_c_message_unpack (&resp_ctrl_thread_reprov__descriptor,
                                allocator, len, data);
}
void   resp_ctrl_thread_reprov__free_unpacked
                     (RespCtrlThreadReprov *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &resp_ctrl_thread_reprov__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   network_ctrl_payload__init
                     (NetworkCtrlPayload         *message)
{
  static const NetworkCtrlPayload init_value = NETWORK_CTRL_PAYLOAD__INIT;
  *message = init_value;
}
size_t network_ctrl_payload__get_packed_size
                     (const NetworkCtrlPayload *message)
{
  assert(message->base.descriptor == &network_ctrl_payload__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t network_ctrl_payload__pack
                     (const NetworkCtrlPayload *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &network_ctrl_payload__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t network_ctrl_payload__pack_to_buffer
                     (const NetworkCtrlPayload *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &network_ctrl_payload__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
NetworkCtrlPayload *
       network_ctrl_payload__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (NetworkCtrlPayload *)
     protobuf_c_message_unpack (&network_ctrl_payload__descriptor,
                                allocator, len, data);
}
void   network_ctrl_payload__free_unpacked
                     (NetworkCtrlPayload *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &network_ctrl_payload__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
#define cmd_ctrl_wifi_reset__field_descriptors NULL
#define cmd_ctrl_wifi_reset__field_indices_by_name NULL
#define cmd_ctrl_wifi_reset__number_ranges NULL
const ProtobufCMessageDescriptor cmd_ctrl_wifi_reset__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "CmdCtrlWifiReset",
  "CmdCtrlWifiReset",
  "CmdCtrlWifiReset",
  "",
  sizeof(CmdCtrlWifiReset),
  0,
  cmd_ctrl_wifi_reset__field_descriptors,
  cmd_ctrl_wifi_reset__field_indices_by_name,
  0,  cmd_ctrl_wifi_reset__number_ranges,
  (ProtobufCMessageInit) cmd_ctrl_wifi_reset__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define resp_ctrl_wifi_reset__field_descriptors NULL
#define resp_ctrl_wifi_reset__field_indices_by_name NULL
#define resp_ctrl_wifi_reset__number_ranges NULL
const ProtobufCMessageDescriptor resp_ctrl_wifi_reset__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "RespCtrlWifiReset",
  "RespCtrlWifiReset",
  "RespCtrlWifiReset",
  "",
  sizeof(RespCtrlWifiReset),
  0,
  resp_ctrl_wifi_reset__field_descriptors,
  resp_ctrl_wifi_reset__field_indices_by_name,
  0,  resp_ctrl_wifi_reset__number_ranges,
  (ProtobufCMessageInit) resp_ctrl_wifi_reset__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define cmd_ctrl_wifi_reprov__field_descriptors NULL
#define cmd_ctrl_wifi_reprov__field_indices_by_name NULL
#define cmd_ctrl_wifi_reprov__number_ranges NULL
const ProtobufCMessageDescriptor cmd_ctrl_wifi_reprov__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "CmdCtrlWifiReprov",
  "CmdCtrlWifiReprov",
  "CmdCtrlWifiReprov",
  "",
  sizeof(CmdCtrlWifiReprov),
  0,
  cmd_ctrl_wifi_reprov__field_descriptors,
  cmd_ctrl_wifi_reprov__field_indices_by_name,
  0,  cmd_ctrl_wifi_reprov__number_ranges,
  (ProtobufCMessageInit) cmd_ctrl_wifi_reprov__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define resp_ctrl_wifi_reprov__field_descriptors NULL
#define resp_ctrl_wifi_reprov__field_indices_by_name NULL
#define resp_ctrl_wifi_reprov__number_ranges NULL
const ProtobufCMessageDescriptor resp_ctrl_wifi_reprov__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "RespCtrlWifiReprov",
  "RespCtrlWifiReprov",
  "RespCtrlWifiReprov",
  "",
  sizeof(RespCtrlWifiReprov),
  0,
  resp_ctrl_wifi_reprov__field_descriptors,
  resp_ctrl_wifi_reprov__field_indices_by_name,
  0,  resp_ctrl_wifi_reprov__number_ranges,
  (ProtobufCMessageInit) resp_ctrl_wifi_reprov__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define cmd_ctrl_thread_reset__field_descriptors NULL
#define cmd_ctrl_thread_reset__field_indices_by_name NULL
#define cmd_ctrl_thread_reset__number_ranges NULL
const ProtobufCMessageDescriptor cmd_ctrl_thread_reset__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "CmdCtrlThreadReset",
  "CmdCtrlThreadReset",
  "CmdCtrlThreadReset",
  "",
  sizeof(CmdCtrlThreadReset),
  0,
  cmd_ctrl_thread_reset__field_descriptors,
  cmd_ctrl_thread_reset__field_indices_by_name,
  0,  cmd_ctrl_thread_reset__number_ranges,
  (ProtobufCMessageInit) cmd_ctrl_thread_reset__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define resp_ctrl_thread_reset__field_descriptors NULL
#define resp_ctrl_thread_reset__field_indices_by_name NULL
#define resp_ctrl_thread_reset__number_ranges NULL
const ProtobufCMessageDescriptor resp_ctrl_thread_reset__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "RespCtrlThreadReset",
  "RespCtrlThreadReset",
  "RespCtrlThreadReset",
  "",
  sizeof(RespCtrlThreadReset),
  0,
  resp_ctrl_thread_reset__field_descriptors,
  resp_ctrl_thread_reset__field_indices_by_name,
  0,  resp_ctrl_thread_reset__number_ranges,
  (ProtobufCMessageInit) resp_ctrl_thread_reset__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define cmd_ctrl_thread_reprov__field_descriptors NULL
#define cmd_ctrl_thread_reprov__field_indices_by_name NULL
#define cmd_ctrl_thread_reprov__number_ranges NULL
const ProtobufCMessageDescriptor cmd_ctrl_thread_reprov__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "CmdCtrlThreadReprov",
  "CmdCtrlThreadReprov",
  "CmdCtrlThreadReprov",
  "",
  sizeof(CmdCtrlThreadReprov),
  0,
  cmd_ctrl_thread_reprov__field_descriptors,
  cmd_ctrl_thread_reprov__field_indices_by_name,
  0,  cmd_ctrl_thread_reprov__number_ranges,
  (ProtobufCMessageInit) cmd_ctrl_thread_reprov__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define resp_ctrl_thread_reprov__field_descriptors NULL
#define resp_ctrl_thread_reprov__field_indices_by_name NULL
#define resp_ctrl_thread_reprov__number_ranges NULL
const ProtobufCMessageDescriptor resp_ctrl_thread_reprov__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "RespCtrlThreadReprov",
  "RespCtrlThreadReprov",
  "RespCtrlThreadReprov",
  "",
  sizeof(RespCtrlThreadReprov),
  0,
  resp_ctrl_thread_reprov__field_descriptors,
  resp_ctrl_thread_reprov__field_indices_by_name,
  0,  resp_ctrl_thread_reprov__number_ranges,
  (ProtobufCMessageInit) resp_ctrl_thread_reprov__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor network_ctrl_payload__field_descriptors[10] =
{
  {
    "msg",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(NetworkCtrlPayload, msg),
    &network_ctrl_msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "status",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(NetworkCtrlPayload, status),
    &status__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cmd_ctrl_wifi_reset",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, cmd_ctrl_wifi_reset),
    &cmd_ctrl_wifi_reset__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "resp_ctrl_wifi_reset",
    12,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, resp_ctrl_wifi_reset),
    &resp_ctrl_wifi_reset__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cmd_ctrl_wifi_reprov",
    13,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, cmd_ctrl_wifi_reprov),
    &cmd_ctrl_wifi_reprov__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "resp_ctrl_wifi_reprov",
    14,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, resp_ctrl_wifi_reprov),
    &resp_ctrl_wifi_reprov__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cmd_ctrl_thread_reset",
    15,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, cmd_ctrl_thread_reset),
    &cmd_ctrl_thread_reset__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "resp_ctrl_thread_reset",
    16,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, resp_ctrl_thread_reset),
    &resp_ctrl_thread_reset__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cmd_ctrl_thread_reprov",
    17,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, cmd_ctrl_thread_reprov),
    &cmd_ctrl_thread_reprov__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "resp_ctrl_thread_reprov",
    18,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(NetworkCtrlPayload, payload_case),
    offsetof(NetworkCtrlPayload, resp_ctrl_thread_reprov),
    &resp_ctrl_thread_reprov__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned network_ctrl_payload__field_indices_by_name[] = {
  8,   /* field[8] = cmd_ctrl_thread_reprov */
  6,   /* field[6] = cmd_ctrl_thread_reset */
  4,   /* field[4] = cmd_ctrl_wifi_reprov */
  2,   /* field[2] = cmd_ctrl_wifi_reset */
  0,   /* field[0] = msg */
  9,   /* field[9] = resp_ctrl_thread_reprov */
  7,   /* field[7] = resp_ctrl_thread_reset */
  5,   /* field[5] = resp_ctrl_wifi_reprov */
  3,   /* field[3] = resp_ctrl_wifi_reset */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange network_ctrl_payload__number_ranges[2 + 1] =
{
  { 1, 0 },
  { 11, 2 },
  { 0, 10 }
};
const ProtobufCMessageDescriptor network_ctrl_payload__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "NetworkCtrlPayload",
  "NetworkCtrlPayload",
  "NetworkCtrlPayload",
  "",
  sizeof(NetworkCtrlPayload),
  10,
  network_ctrl_payload__field_descriptors,
  network_ctrl_payload__field_indices_by_name,
  2,  network_ctrl_payload__number_ranges,
  (ProtobufCMessageInit) network_ctrl_payload__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue network_ctrl_msg_type__enum_values_by_number[9] =
{
  { "TypeCtrlReserved", "NETWORK_CTRL_MSG_TYPE__TypeCtrlReserved", 0 },
  { "TypeCmdCtrlWifiReset", "NETWORK_CTRL_MSG_TYPE__TypeCmdCtrlWifiReset", 1 },
  { "TypeRespCtrlWifiReset", "NETWORK_CTRL_MSG_TYPE__TypeRespCtrlWifiReset", 2 },
  { "TypeCmdCtrlWifiReprov", "NETWORK_CTRL_MSG_TYPE__TypeCmdCtrlWifiReprov", 3 },
  { "TypeRespCtrlWifiReprov", "NETWORK_CTRL_MSG_TYPE__TypeRespCtrlWifiReprov", 4 },
  { "TypeCmdCtrlThreadReset", "NETWORK_CTRL_MSG_TYPE__TypeCmdCtrlThreadReset", 5 },
  { "TypeRespCtrlThreadReset", "NETWORK_CTRL_MSG_TYPE__TypeRespCtrlThreadReset", 6 },
  { "TypeCmdCtrlThreadReprov", "NETWORK_CTRL_MSG_TYPE__TypeCmdCtrlThreadReprov", 7 },
  { "TypeRespCtrlThreadReprov", "NETWORK_CTRL_MSG_TYPE__TypeRespCtrlThreadReprov", 8 },
};
static const ProtobufCIntRange network_ctrl_msg_type__value_ranges[] = {
{0, 0},{0, 9}
};
static const ProtobufCEnumValueIndex network_ctrl_msg_type__enum_values_by_name[9] =
{
  { "TypeCmdCtrlThreadReprov", 7 },
  { "TypeCmdCtrlThreadReset", 5 },
  { "TypeCmdCtrlWifiReprov", 3 },
  { "TypeCmdCtrlWifiReset", 1 },
  { "TypeCtrlReserved", 0 },
  { "TypeRespCtrlThreadReprov", 8 },
  { "TypeRespCtrlThreadReset", 6 },
  { "TypeRespCtrlWifiReprov", 4 },
  { "TypeRespCtrlWifiReset", 2 },
};
const ProtobufCEnumDescriptor network_ctrl_msg_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "NetworkCtrlMsgType",
  "NetworkCtrlMsgType",
  "NetworkCtrlMsgType",
  "",
  9,
  network_ctrl_msg_type__enum_values_by_number,
  9,
  network_ctrl_msg_type__enum_values_by_name,
  1,
  network_ctrl_msg_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};