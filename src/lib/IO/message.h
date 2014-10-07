#ifndef COMM_MESSAGE_H
#define COMM_MESSAGE_H

#include <stdint.h>
#include <unistd.h>

/*
Message structure:
+------+---------------------+
| 0x00 | Message type        |
| 0x01 | Data size           |
| 0x05 | Data                |
| 0x0N | CRC16 msg checksum  | // TODO
+------+---------------------+
*/
typedef struct Message Message;
struct Message {
    uint8_t  type;
    uint32_t size;
    void    *data;
    Message *next;
};
void message_free(Message *);

// Error message
#define mError         0x00
// Common messages
#define mAuthPut       0x01
#define mAuthGet       0x02
#define mPasswordPut   0x03
#define mPasswordGet   0x04
#define mKeyPairPut    0x05
#define mKeyPairGet    0x06
#define mKeyPubPut     0x07
#define mKeyPubGet     0x08
#define mTextSign      0x09
#define mTextVerify    0x0A
#define mTextEncrypt   0x0B
#define mTextDecrypt   0x0C
#define mBackupCreate  0x0D
#define mBackupRestore 0x0E
// Service messages
#define mDeviceInit    0xF0
#define mDeviceInfo    0xF1

/*
 * Protocol data structures.
 */

// Device information
typedef struct {
    // Unical identifier
    uint64_t ident;
    // Battery state in percents
    uint8_t  batteryState;
    // Avaliable flash password space in bytes
    uint32_t freePasswordSpace;
    // Avaliable flash key space in bytes
    uint32_t freeKeySpace;
} DeviceInfo;
// Message destructor
void device_info_free(DeviceInfo *);

// Password managment eq auth
typedef struct {
    // Host@login and password strings
    char *login, *password;
    // Sum of string sizes
    uint32_t size;
} Password;
// Message destructor
void password_free(Password *);

/*
 * Deserialisation methods.
 */

/*
 * Deserialize QByteArray (Latin1 string)
 * @param data pointer
 * @param readed data size var pointer
 */
char *
deserialize_qbytearray(const char *, uint32_t *);

/*
 * Deserialize auth message
 * @param data pointer
 * @param data size
 */
Password *
deserialize_password_message(const char *, size_t);

#endif // COMM_MESSAGE_H

