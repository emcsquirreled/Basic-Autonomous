string sTemp = "";
TFileHandle hFileWriteHandle = NOT_A_HANDLE;
bool bFirstNumberOnLine = true;
TFileIOResult nIoResult = ioRsltSuccess;

bool log_open(const string &sFileName, int nFileSize);

void log_close();

void log_integer(long nNumber);

void log_string(string nString);

void log_writedelimiters();

bool log_open(const string &sFileName, int nFileSize)
{
	bFirstNumberOnLine = true;
	Delete(sFileName, nIoResult);
	OpenWrite(hFileWriteHandle, nIoResult, sFileName, nFileSize);
	return nIoResult == ioRsltSuccess;
}

void log_close()
{
	Close(hFileWriteHandle, nIoResult);
	hFileWriteHandle = NOT_A_HANDLE;
}

void log_newline()
{
	WriteText(hFileWriteHandle, nIoResult, "\r\n");
	bFirstNumberOnLine = true;
	return;
}

void log_writedelimiters()
{
	if (bFirstNumberOnLine)
		bFirstNumberOnLine = false;
	else
		WriteText(hFileWriteHandle, nIoResult, ", ");
	return;
}

void log_integer(long nNumber)
{
	string sTemp;
	log_writedelimiters();
	StringFormat(sTemp, "%d", (long) nNumber);
	WriteText(hFileWriteHandle, nIoResult, sTemp);
	return;
}

void log_string(string nString)
{
	WriteText(hFileWriteHandle, nIoResult, sTemp);
	return;
}
