kernel void add(global const int *a, global const int *b, const int *c)
{
	*c = *a + *b;
}
