void ShowPercentage(__int64 n, __int64 t)
{
	static const int TxtBufSize = 256;
	static double PercentDone = 0.0;
	static Array<char> ProgressMsg(TxtBufSize);
	static Array<char> LastProgressMsg(TxtBufSize);

	PercentDone = ((double)n / (double)t) * 100.0;

	_snprintf(&ProgressMsg[0], TxtBufSize, "%2.2f", PercentDone);
	
	if(strncmp(&ProgressMsg[0], &LastProgressMsg[0], TxtBufSize) != 0)
		printf("\r%s %%", &ProgressMsg[0]);

	strncpy(&LastProgressMsg[0], &ProgressMsg[0], TxtBufSize);
}
