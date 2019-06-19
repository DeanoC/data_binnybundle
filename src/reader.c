#include "al2o3_platform/platform.h"
#include "al2o3_memory/memory.h"
#include "data_binnybundle/reader.h"

typedef struct DataBinnyBundle_Reader {
	VFile_Handle	vfile;
	int64_t  startOffset;
	DataBinnyBundle_Header header;
} DataBinnyBundle_Reader;

static bool ReadHeader(DataBinnyBundle_Reader* reader, DataBinnyBundle_Header* header) {
	// read header
	bool okay = VFile_Read(reader->vfile, header, sizeof(DataBinnyBundle_Header));
	if (!okay)
		return false;

	ASSERT(header->magic == DATABINNYBUNDLE_ID("BUND"));
	ASSERT(header->majorVersion == DataBinnyBundle_MajorVersion);
	ASSERT(header->minorVersion <= DataBinnyBundle_MinorVersion);

	ASSERT(sizeof(uintptr_t) == 8);
	// only 64 bit support currently
	if (!(header->flags & DataBinnyBundle_HeaderFlag64Bit))
		return false;

	return true;
}


AL2O3_EXTERN_C DataBinnyBundle_ReaderHandle DataBinnyBundle_ReaderCreate(VFile_Handle vfile) {
	DataBinnyBundle_Reader* reader = MEMORY_CALLOC(1, sizeof(struct DataBinnyBundle_Reader));
	if(!reader) goto failexit;
	reader->vfile = vfile;
	reader->startOffset = VFile_Tell(vfile);
	bool okay = ReadHeader(reader, &reader->header);
	if(!okay) goto failexit;

	return reader;

failexit:
	MEMORY_FREE(reader);
	return NULL;
}

AL2O3_EXTERN_C void DataBinnyBundle_ReaderDestroy(DataBinnyBundle_ReaderHandle handle) {
	ASSERT(handle);
	DataBinnyBundle_Reader* reader = (DataBinnyBundle_Reader*)handle;
	MEMORY_FREE(reader);
}
