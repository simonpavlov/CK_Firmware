#ifndef IO_MESSAGE
#define IO_MESSAGE

#include <stdint.h>
#include <stdlib.h>


// Generic Message
class Message{
	public:
		/*
		 * Message constructor.
		 * @param type Is a message type.
		 */
		Message(uint8_t type) : mType(type) {}

		/*
		 * Message type getter.
		 * return type code of message.
		 */
		uint8_t getType() const {return mType;}

		virtual char*	serialize() const = 0;
		virtual bool	deserialize(char * data, size_t size) = 0;

	protected:
		const uint8_t	mType;
};

#endif //IO_MESSAGE
