#include "list.h"

int main()
{
	try{
		Matrix<DList<Element>> a, b;
		Matrix<list<Element>> c, d;
		
		ifstream f("input.txt");
		if(!f.is_open()) throw myException("File input.txt doesn't exist.\n", EC_FILE);
		f >> a;
		f >> b;
		
		f.clear();
		f.seekg(0);
		f >> c;
		f >> d;
		f.close();
		
		auto t1 = chrono::high_resolution_clock::now();
		a.transpose();
		auto t2 = chrono::high_resolution_clock::now();
		
		auto ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
		std::cout << "Execution time for my own implementation is " <<  ns.count() << "ns\n";
		
		t1 = chrono::high_resolution_clock::now();
		c.transpose();
		t2 = chrono::high_resolution_clock::now();
		
		ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
		std::cout << "Execution time for STL implementation is " <<  ns.count() << "ns\n";
		
		cout << "Transposed matrix a:" << endl << a;
		
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