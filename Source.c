#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* file;
	unsigned char* settings;
	unsigned char* buffer;
	size_t result;
	char fileName[] = "SAVEENGN.00";
	int i = 0;
	unsigned char initialByte = 0;
	unsigned char changedByte = 0;

	const int saveIndex = 10;
	const size_t size = 10;
	const int index = 5;
	const unsigned char flags = 224;
	/* const unsigned char flags = 0b11100000; */

	/* allocate memory */
	settings = (unsigned char*)calloc(size, sizeof(unsigned char));
	buffer = (unsigned char*)calloc(size, sizeof(unsigned char));
	if (buffer == NULL || settings == NULL)
	{
		printf("Memory error");
		return 1;
	}

	/* read settings */
	file = fopen("ASPTS.cfg", "rb");
	if (file == NULL)
	{
		printf("File error");
		return 2;
	}

	/* copy settings */
	result = fread(settings, 1, size, file);
	if (result == 0 || result > size)
	{
		printf("Reading error");
		return 3;
	}
	fclose(file);

	for (i = 0; i < size; i++)
	{
		if (settings[i] <= '9' && settings[i] >= '0')
		{
			fileName[saveIndex] = settings[i];
			file = fopen(fileName, "rb+");
			if (file == NULL)
			{
				continue;
			}

			result = fread(buffer, 1, size, file);
			if (result != size)
			{
				continue;
			}

			initialByte = buffer[index];
			changedByte = initialByte | flags;

			fseek(file, index, SEEK_SET);
			fwrite(&changedByte, sizeof(unsigned char), 1, file);
			fclose(file);

		}
	}



	free(buffer);
	free(settings);
	return 0;
}
