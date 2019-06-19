#include "data_binnybundle/bundle.h"
#include "data_binnybundle/reader.h"
#include "al2o3_catch2/catch2.hpp"

TEST_CASE("Open and close (C)", "[BinnyBundle reader]") {
	DATABINNYBUNDLE_ID("BUND");

	DataBinnyBundle_Header testHeader {
			DATABINNYBUNDLE_ID("BUND"),
			DataBinnyBundle_HeaderFlag64Bit,
			DataBinnyBundle_MajorVersion,
			DataBinnyBundle_MinorVersion,
			0,
			0,
			0,
			0,
			0
	};
	VFile_Handle vfile = VFile_FromMemory(&testHeader, sizeof(DataBinnyBundle_Header), false);
	DataBinnyBundle_ReaderHandle handle = DataBinnyBundle_ReaderCreate(vfile);
	REQUIRE(handle);
	DataBinnyBundle_ReaderDestroy(handle);
	VFile_Close(vfile);
}

