#include "list.h"

int M, N;

int main()
{
	try{
		DList<double> a, b;
		list<double> c, d;
		ifstream f("input.txt");
		if(!f.is_open()) throw myException("File input.txt doesn't exist.\n", EC_FILE);
		f >> M >> N;
		f >> a;
		f >> b;
		f.close();
		a += b;
		cout << a;
		a = a * b;
		cout << a;
	}
	catch (bad_alloc)
	{
		throw myException("Memory allocation error\n", EC_MEMORY);
	}
	catch (runtime_error)
	{
		throw myException("Runtime error\n", EC_MEMORY);
	}
	catch (myException e)
	{
		cout << e.getMessage();
		return e.getCode();
	}
	return 0;
}