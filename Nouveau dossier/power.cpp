int pow(int n, int e)
{
	if(e == 0)
		return 1;

	for(int i = 0; i < e-1; i++)
		n *= n;

	return n;
}
