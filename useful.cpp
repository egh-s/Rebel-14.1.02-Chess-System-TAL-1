
#include <stdlib.h>  
#include <stdio.h>  
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <intrin.h>
#include <time.h>
#include <conio.h>
#include <assert.h>


#include <chrono>
#include <thread>

#include <atomic>

//#include <tchar.h>
#include <windows.h>


typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

#define FILE_SIZE_ERROR -1

u16 read_u16_le(u8* buffer)
{
	u16 val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[0] = buffer[0];
	p[1] = buffer[1];
#else
	p[1] = buffer[0];
	p[0] = buffer[1];
#endif
	return val;
}

u16 read_u16_be(u8* buffer)
{
	uint16_t val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[1] = buffer[0];
	p[0] = buffer[1];
#else
	p[0] = buffer[0];
	p[1] = buffer[1];
#endif
	return val;
}

u32 read_u32_le(u8* buffer)
{
	u32 val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[0] = buffer[0];
	p[1] = buffer[1];
	p[2] = buffer[2];
	p[3] = buffer[3];
#else
	p[3] = buffer[0];
	p[2] = buffer[1];
	p[1] = buffer[2];
	p[0] = buffer[3];
#endif
	return val;
}

u32 read_u32_be(u8* buffer)
{
	u32 val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[3] = buffer[0];
	p[2] = buffer[1];
	p[1] = buffer[2];
	p[0] = buffer[3];
#else
	p[0] = buffer[0];
	p[1] = buffer[1];
	p[2] = buffer[2];
	p[3] = buffer[3];
#endif
	return val;
}

u64 read_u64_le(u8* buffer)
{
	u64 val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[0] = buffer[0];
	p[1] = buffer[1];
	p[2] = buffer[2];
	p[3] = buffer[3];
	p[4] = buffer[4];
	p[5] = buffer[5];
	p[6] = buffer[6];
	p[7] = buffer[7];
#else
	p[7] = buffer[0];
	p[6] = buffer[1];
	p[5] = buffer[2];
	p[4] = buffer[3];
	p[3] = buffer[4];
	p[2] = buffer[5];
	p[1] = buffer[6];
	p[0] = buffer[7];
#endif
	return val;
}

u64 read_u64_be(u8* buffer)
{
	u64 val;
	u8* p = (u8*)&val;

#ifndef TARGET_BIG_ENDIAN
	p[7] = buffer[0];
	p[6] = buffer[1];
	p[5] = buffer[2];
	p[4] = buffer[3];
	p[3] = buffer[4];
	p[2] = buffer[5];
	p[1] = buffer[6];
	p[0] = buffer[7];
#else
	p[0] = buffer[0];
	p[1] = buffer[1];
	p[2] = buffer[2];
	p[3] = buffer[3];
	p[4] = buffer[4];
	p[5] = buffer[5];
	p[6] = buffer[6];
	p[7] = buffer[7];
#endif
	return val;
}
//

#if 0
u32 get_file_size(char* file)
{
	assert(file != NULL);

	HANDLE fh;
	LARGE_INTEGER  size;

	size_t pReturnValue;
	wchar_t wcstr[1024];
	size_t sizeInWords = 512;
	size_t count = 512;
	errno_t err;

	err = mbstowcs_s(&pReturnValue, wcstr, sizeInWords, file, count);

	fh = CreateFile(wcstr, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (!GetFileSizeEx(fh, &size)) {
		return FILE_SIZE_ERROR;
	}
	CloseHandle(fh);

	return (u32)size.QuadPart;
}

#endif
