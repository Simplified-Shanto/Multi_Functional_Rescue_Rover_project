#include "lapse.h"

#include "FS.h"
#include "SD_MMC.h"

bool writeFile(const char *path, const unsigned char *data, unsigned long len)
{
	if(wtd) Serial.printf("Writing file: %s\n", path);
	File file = SD_MMC.open(path, FILE_WRITE);
	if (!file)
	{
		if(wtd) Serial.println("Failed to open file for writing");
		return false;
	}
	if (file.write(data, len))
	{
		if(wtd) Serial.println("File written");
	}
	else
	{
		if(wtd) Serial.println("Write failed");
		return false;
	}
	file.close();
	return true;
}

bool appendFile(const char *path, const unsigned char *data, unsigned long len)
{
	if(wtd) Serial.printf("Appending to file: %s\n", path);

	File file = SD_MMC.open(path, FILE_APPEND);
	if (!file)
	{
		if(wtd) Serial.println("Failed to open file for writing");
		return false;
	}
	if (file.write(data, len))
	{
		if(wtd) Serial.println("File written");
	}
	else
	{
		if(wtd) Serial.println("Write failed");
		return false;
	}
	file.close();
	return true;
}

bool initFileSystem()
{
	if (!SD_MMC.begin())
	{
		if(wtd) Serial.println("Card Mount Failed");
		return false;
	}
	uint8_t cardType = SD_MMC.cardType();

	if (cardType == CARD_NONE)
	{
		if(wtd) Serial.println("No SD card attached");
		return false;
	}
	if(wtd) Serial.print("SD Card Type: ");
	if (cardType == CARD_MMC)
		if(wtd) Serial.println("MMC");
	else if (cardType == CARD_SD)
		if(wtd) Serial.println("SDSC");
	else if (cardType == CARD_SDHC)
		if(wtd) Serial.println("SDHC");
	else

		if(wtd) Serial.println("UNKNOWN");

	uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
	if(wtd) Serial.printf("SD Card Size: %lluMB\n", cardSize);
	if(wtd) Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
	if(wtd) Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));
	return true;
}

bool createDir(const char *path)
{
	if(wtd) Serial.printf("Creating Dir: %s\n", path);
	if (SD_MMC.mkdir(path))
	{
		if(wtd) Serial.println("Dir created");
	}
	else
	{
		if(wtd) Serial.println("mkdir failed");
		return false;
	}
	return true;
}

bool fileExists(const char *path)
{
	return SD_MMC.exists(path);
}
