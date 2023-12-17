#include "list.h"

int main()
{
	try{
		Matrix<DList<Element>> a, b;
//		Matrix<list<Element>> c;
		
		ifstream f("input.txt");
		if(!f.is_open()) throw myException("File input.txt doesn't exist.\n", EC_FILE);
		f >> a;
		f >> b;
		f.close();
		cout << a << b;
		a.transpose();
		cout << "Matrix a after transposing:" << endl << a;
		
		auto t1 = chrono::high_resolution_clock::now();
		a += b;
		cout << "Added b to a:" << endl << a;
		a = a * b;
		cout << "Multiplied a by b:" << endl << a;
		cout << a;
		auto t2 = chrono::high_resolution_clock::now();
		
		auto ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
		std::cout << "Execution time for my own implementation is " <<  ns.count() << "ns\n";
		
		
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