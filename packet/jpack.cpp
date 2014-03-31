/*
 z * jpack.cpp
 *
 *  Created on: 2014. 3. 30.
 *      Author: jack
 */

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#include "jpack.h"
#include "include/simpleCRC32.h"

jpack::jpack(int endian):m_endian(endian) {
	// TODO Auto-generated constructor stub
}

jpack::~jpack() {
	// TODO Auto-generated destructor stub
}

int jpack::enpack(jpack_struct_type * jpack, char * dst, int length) {
	int actual_length = 0;
	int header_size = jpack->length + JPACKET_HEADER_LENGTH + JPACKET_CRC_SIZE;

	assert(jpack);

	if( jpack->length > 0 ) {

		if ( header_size > length )
			return JPACK_ERROR_INSUFFICIENT_MEMORY;

		actual_length += int32todata((int)JPACK_HEAD_PREAMBLE, dst+actual_length);
		actual_length += int32todata((int)jpack->idx, dst+actual_length);
		actual_length += int32todata((int)jpack->cmd, dst+actual_length);
		actual_length += int32todata((int)jpack->length, dst+actual_length);
		memcpy( dst+actual_length, jpack->data, jpack->length);
		actual_length += jpack->length;
		Crc32 * crc = new Crc32();
		crc->Reset();
		crc->AddData((const unsigned char *)jpack->data, jpack->length);
		actual_length += int32todata(crc->GetCrc32(), dst+actual_length);
		delete crc;
	}
	return actual_length;
}


int jpack::depack(char * data, int length, jpack_struct_type * dst) {
	int actual_length = 0;

	int preamble = datatoint32(data);

	if(preamble != JPACK_HEAD_PREAMBLE)
		return JPACK_ERROR_WRONG_PREAMBLE;

	if( (length - (JPACKET_HEADER_LENGTH + JPACKET_CRC_SIZE)) > dst->length )
		return JPACK_ERROR_INSUFFICIENT_MEMORY;

	actual_length += sizeof(preamble);
	dst->idx = datatoint32(data+actual_length); actual_length += sizeof(dst->idx);
	dst->cmd = datatoint32(data+actual_length);	actual_length += sizeof(dst->cmd);
	dst->length = (unsigned int) datatoint32(data+actual_length);	actual_length += sizeof(dst->length);

	Crc32 * crc = new Crc32();
	crc->Reset();
	crc->AddData((const unsigned char *)(data+actual_length), dst->length);
	dst->crc32 = crc->GetCrc32();
	delete crc;

	if( datatoint32(data+actual_length+dst->length) != dst->crc32 )
		return JPACK_ERROR_CRC_ERROR;

	memcpy(dst->data, (void *)(data+actual_length), dst->length); actual_length += dst->length;

	actual_length += sizeof(dst->crc32);

	return actual_length;
}

short jpack::int16todata(short value, char * dst) {

	assert(dst);

	if(m_endian) {
		*(dst) = (value) & 0xFF;
		*(dst++) = (value >> 8) & 0xFF;
	} else {
		*(dst) = (value >> 8) & 0xFF;
		*(dst++) = (value) & 0xFF;
	}

	return sizeof(short);
}

int jpack::int32todata(int value, char * dst) {

	assert(dst);

	if(m_endian) {
		*(dst) = (value) & 0xFF;
		*(++dst) = (value >> 8*1) & 0xFF;
		*(++dst) = (value >> 8*2) & 0xFF;
		*(++dst) = (value >> 8*3) & 0xFF;
	} else {
		*(dst) = (value >> 8*3) & 0xFF;
		*(++dst) = (value >> 8*2) & 0xFF;
		*(++dst) = (value >> 8*1) & 0xFF;
		*(++dst) = (value) & 0xFF;
	}

	return sizeof(int);
}

short jpack::datatoint16(char * src) {

	short ret = 0x0000;

	assert(src);

	if(m_endian) {
		ret |= *(src)			& 0X00FF;
		ret |= (*(src) << 8) 	& 0xFF00;
	} else {
		ret |= (*(src) << 8)	& 0xFF00;
		ret |= *(src++)			& 0x00FF;
	}

	return ret;
}

int jpack::datatoint32(char * src) {

	int ret = 0x00000000;

	assert(src);

	if(m_endian) {
		ret |= *src			& 0X000000FF;
		ret |= (*(++src) << 8)	& 0x0000FF00;
		ret |= (*(++src) << 16)	& 0x00FF0000;
		ret |= (*(++src) << 24)	& 0xFF000000;
	} else {
		ret |= (*(src) << 24)	& 0xFF000000;
		ret |= (*(++src) << 16)	& 0x00FF0000;
		ret |= (*(++src) << 8)	& 0x0000FF00;
		ret |= *(++src) 		& 0x000000FF;
	}

	return ret;
}
