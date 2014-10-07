#include "../message.h"
#include <stdlib.h>
#include <string.h>

void message_free(Message *msg)
{
    free(msg->data);
    free(msg);
}

void device_info_free(DeviceInfo *msg)
{
    free(msg);
}

void password_free(Password *msg)
{
    free(msg->login);
    free(msg->password);
    free(msg);
}

char *
deserialize_qbytearray(const char *data_p, uint32_t *readed)
{
    char *string;                               // String pointer
    // String size
    uint32_t string_size;
    const uint32_t *string_p = (uint32_t *) data_p;

    string_size = *string_p++;
    if (string_size == 0xFFFFFFFF)
    // Empty string
        return 0;
    
    // Allocate string by string size + one byte for \0
    string = malloc(string_size + 1);
    // Copy string
    memcpy(string, string_p, string_size);
    // Set zero at the end of string
    string[string_size] = 0;
    // Set readed bytes
    if (readed)
        *readed = sizeof(uint32_t) + string_size;
    // Return string
    return string;
}

Password *
deserialize_password_message(const char *data_p, size_t data_size)
{
    Password *msg = malloc(sizeof(Password));
    if (!msg)
        return 0;

    msg->size = 0;

    // Data pointer
    const char *data = data_p;
    // Readed data size
    uint32_t readed;

    msg->login = deserialize_qbytearray(data, &readed);
    data += readed;
    msg->size += readed - sizeof(uint32_t) + 1;

    msg->password = deserialize_qbytearray(data, &readed);
    msg->size += readed - sizeof(uint32_t) + 1;

    return msg;
}

