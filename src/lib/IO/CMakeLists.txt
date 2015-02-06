set (IO_SRC
	src/CK_Logger.cpp
	src/IO_ByteStream.cpp
	src/CK_Array.cpp
	src/IO_DeviceInfo.cpp
	src/CK_PasswordPair.cpp
	src/CK_String.cpp
	src/IO_Serial.cpp
	src/IO_Message.cpp
	)

# add_definitions (-D DEBUG)

add_library (IO ${IO_SRC})
