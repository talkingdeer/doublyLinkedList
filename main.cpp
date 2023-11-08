#include "list.h"

int main()
{
	DList<double> a, b;
	int k;
	for (k = 0; k < 66; k++) {
		a.PushFront(k);
	}
	for (k = 0; k < 63; k++) {
		b.PushFront(k);
	}
	std::cout << a;
	std::cout << a.getValue(5) << '\n';
	std::cout << (a == b) << '\n';
	b = a;
	std::cout << b;
    return 0;
}