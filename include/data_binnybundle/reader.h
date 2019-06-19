#pragma once
#ifndef DATA_BINNYBUNDLE_READER_H
#define DATA_BINNYBUNDLE_READER_H

#include "al2o3_platform/platform.h"
#include "al2o3_vfile/vfile.h"
#include "data_binnybundle/bundle.h"

typedef struct DataBinnyBundle_Reader *DataBinnyBundle_ReaderHandle;

// chunk name, stage, major version, minor version, memory size, pointer to the base of memory
typedef bool (*DataBinnyBundle_ReaderChunkCreateFunc)(char const *chunkName,
																int stage,
																uint16_t majorVersion,
																uint16_t minorVersion,
																size_t memorySize,
																void *ptr);

typedef bool (*DataBinnyBundle_ReaderChunkDestroyFunc)(int stage, void *ptr);

typedef struct DataBinnyBundle_ReaderChunkHandler {
	uint32_t id;
	int stage;
	uint32_t extraMem;
	DataBinnyBundle_ReaderChunkCreateFunc createFunc;
	DataBinnyBundle_ReaderChunkDestroyFunc destroyFunc;
//	bool writePrefix = false; // stage 0 only will write pointers into the begining of memory
//	bool allocatePrefix = false; // stage 0 only whether should add the size of the prefix onto the data size
} DataBinnyBundle_ReaderChunkHandler;

AL2O3_EXTERN_C DataBinnyBundle_ReaderHandle DataBinnyBundle_ReaderCreate(VFile_Handle vfile);
AL2O3_EXTERN_C void DataBinnyBundle_ReaderDestroy(DataBinnyBundle_ReaderHandle handle);
AL2O3_EXTERN_C void DataBinnyBundle_ReaderAddHandler(DataBinnyBundle_ReaderHandle handle, DataBinnyBundle_ReaderChunkHandler* handler);
AL2O3_EXTERN_C size_t DataBinnyBundle_ReaderGetDirectoryCount(DataBinnyBundle_ReaderHandle handle);
AL2O3_EXTERN_C DataBinnyBundle_DirEntry64 const* DataBinnyBundle_ReaderGetDirectory(DataBinnyBundle_ReaderHandle handle);
#endif //DATA_BINNYBUNDLE_READER_H