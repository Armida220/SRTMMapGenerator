#include "stdafx.h"
#include "SRTMZipDecompressor.h"


SRTMZipDecompressor::SRTMZipDecompressor()
{

}


SRTMZipDecompressor::~SRTMZipDecompressor()
{

}


int SRTMZipDecompressor::decompress(string source, string destination, string searchingForFile)
{
	int err = 0;
	zip *z = zip_open(source.c_str(), 0, &err);

	struct zip_stat st;
	zip_stat_init(&st);
	zip_stat(z, searchingForFile.c_str(), 0, &st);

	if (st.size > 0) {
		char *buffer = new char[st.size];
		zip_file *f = zip_fopen(z, searchingForFile.c_str(), 0);
		zip_fread(f, buffer, st.size);

		zip_fclose(f);
		zip_close(z);

		#pragma warning (disable : 4996)
		FILE *destinationFile = fopen(destination.c_str(), "wb");
		fwrite(buffer, sizeof(char), st.size, destinationFile);

		fclose(destinationFile);

		delete[] buffer;
	}
	else {
		zip_close(z);
	}

	return err;
}
