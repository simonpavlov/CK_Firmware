#ifndef IO_MESSAGE
#define IO_MESSAGE

#include <stdint.h>
#include <stdlib.h>

/*
Message structure:
+------+---------------------+
| 0x00 | Message type        |
| 0x01 | Data size           |
| 0x05 | Data                |
| 0x0N | CRC16 msg checksum  | // TODO
+------+---------------------+
*/

// Message type codes
namespace MessageType {
// Error message
static const uint8_t Error         = 0x00;
// Common messages
static const uint8_t AuthPut       = 0x01;
static const uint8_t AuthGet       = 0x02;
static const uint8_t PasswordPut   = 0x03;
static const uint8_t PasswordGet   = 0x04;
static const uint8_t KeyPairPut    = 0x05;
static const uint8_t KeyPairGet    = 0x06;
static const uint8_t KeyPubPut     = 0x07;
static const uint8_t KeyPubGet     = 0x08;
static const uint8_t TextSign      = 0x09;
static const uint8_t TextVerify    = 0x0A;
static const uint8_t TextEncrypt   = 0x0B;
static const uint8_t TextDecrypt   = 0x0C;
static const uint8_t BackupCreate  = 0x0D;
static const uint8_t BackupRestore = 0x0E;
// Service messages
static const uint8_t DeviceInit    = 0xF0;
static const uint8_t DeviceInfo    = 0xF1;
}

// Generic Message
class Message{
	public:
		/*
		 * Message constructor.
		 * @param type Is a message type.
		 */
		Message(uint8_t type_init, uint16_t size_init, uint16_t crc16_init, uint8_t *data_init):
			type(type_init),
			size(size_init),
			crc16(crc16_init),
			data(data_init)
		{}

		/*
		 * Message type getter.
		 * return type code of message.
		 */
		uint8_t			get_type()	const {return type;}
		uint16_t		get_size()	const {return size;}
		uint16_t		get_crc16()	const {return crc16;}
		const uint8_t *	get_data()	const {return data;}

		// virtual char*	serialize() const = 0;
		// virtual bool	deserialize(char * data, size_t size) = 0;

	protected:
		const uint8_t	type;
		const uint16_t	size;
		const uint16_t	crc16;
		const uint8_t	*data;
};

#endif //IO_MESSAGE
