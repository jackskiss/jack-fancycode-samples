/*
 * jpack.h
 *
 *  Created on: 2014. 3. 30.
 *      Author: jack
 */

#ifndef JPACK_H_
#define JPACK_H_

#define JPACK_HEAD_PREAMBLE		0xB16B00B5

#define JPACK_OK								0x0000
#define JPACK_ERROR_CRC							-(0x0001)
#define JPACK_ERROR_INSUFFICIENT_MEMORY			-(0x0002)
#define JPACK_ERROR_WRONG_PREAMBLE				-(0x0003)
#define JPACK_ERROR_CRC_ERROR					-(0x0004)

#define JPACK_LITTLE_ENDIAN						0x0
#define JPACK_BIG_ENDIAN						0x1

//using namespace jpack;

typedef struct {
	int	cmd;
	unsigned int idx;
	unsigned int length;
	char * data;
	int crc32;
} jpack_struct_type;

#define JPACKET_HEADER_COMMAND_SIZE		sizeof(int)
#define JPACKET_HEADER_INDEX_SIZE		sizeof(unsigned int)
#define JPACKET_HEADER_LENGTH_SIZE		sizeof(unsigned int)
#define JPACKET_CRC_SIZE				sizeof(int)

#define JPACKET_HEADER_LENGTH 			sizeof(JPACK_HEAD_PREAMBLE) \
									+	sizeof(JPACKET_HEADER_COMMAND_SIZE) \
									+	sizeof(JPACKET_HEADER_INDEX_SIZE) \
									+	sizeof(JPACKET_HEADER_LENGTH_SIZE)

class jpack {
public:
	jpack(int endian);
	virtual ~jpack();
	int enpack(jpack_struct_type * jpack, char * dst, int length);
	int depack(char * data, int length, jpack_struct_type * dst);

private:
	short int16todata(short value, char * dst);
	int int32todata(int value, char * dst);
	short datatoint16(char * src);
	int datatoint32(char * src);

private:
	int m_endian;

};


#endif /* JPACK_H_ */
