#pragma once
#ifndef DATA_BINNYBUNDLE_BUNDLE_H
#define DATA_BINNYBUNDLE_BUNDLE_H

#include "al2o3_platform/platform.h"

static const uint16_t DataBinnyBundle_MajorVersion = 2;
static const uint16_t DataBinnyBundle_MinorVersion = 0;

static const uint32_t DataBinnyBundle_HeaderFlag64Bit = 0x1;
#define DATABINNYBUNDLE_ID(s) (uint32_t)(((s[0])<<24) | ((s[0])<<16) | ((s[0])<<8) | ((s[0])<<0))

//  32 bytes
typedef struct DataBinnyBundle_Header
{
	uint32_t magic;
	uint32_t flags;

	uint16_t majorVersion;
	uint16_t minorVersion;
	// this allow padding between the directory, the strings and the start of the chunks
	uint16_t stringsMicroOffset;
	uint16_t chunksMicroOffset;

	// this is a 64 bit user data item, usually used as a cache/regen id
	uint64_t userData;

	// string table is limited to 4GB I hope this limit never gets hit!
	uint32_t stringTableSize;
	uint32_t chunkCount;

} DataBinnyBundle_Header;

typedef struct DataBinnyBundle_DirEntry64
{
	uint32_t id;
	uint32_t storedCrc32c;
	uint32_t uncompressedCrc32c;
	uint32_t flags;

	union {
		uint64_t nameOffset;  // this is replaced by the real name pointer
		char const* name;
	};
	uint64_t storedOffset; // this is never used after fixup but is set to the ptr for debugging

	uint64_t storedSize;
	uint64_t uncompressedSize;
} DataBinnyBundle_DirEntry64;

typedef struct DataBinnyBundle_ChunkHeader64
{
	uint64_t fixupSize;
	uint64_t dataSize;
	uint64_t fixupOffset;
	uint64_t dataOffset;
	uint16_t majorVersion;
	uint16_t minorVersion;
} DataBinnyBundle_Chunkheader64;



#endif //DATA_BINNYBUNDLE_BUNDLE_H