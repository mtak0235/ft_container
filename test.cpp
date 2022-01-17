#include <iostream>

class Test
{
	private:
		int n;
		int t;
	public:
		Test():n(0), t(0){}
		Test(int n, int t):n(n), t(t){}
		~Test(){ std::cout << "test over" << std::endl; }
		int getN() const { return this->n;}
		int getT() const { return this->t;}
};

std::ostream	&operator<<(std::ostream &out, Test const &t)
{
	out << t.getN() << " " << t.getT();
	return out;
}

int main()
{
	//allocator test
	std::allocator<int> a1;
	int *a = a1.allocate(1);
	std::cout << a[0] << std::endl;
	a1.construct(a, 13);
	std::cout << a[0] << std::endl;
	a1.destroy(a);
	a1.deallocate(a, 1);

	std::allocator<float> f1;
	float *f = f1.allocate(3);
	for (int i = 0; i < 3; i++)
		f1.construct(f + i, i + 1.2 + i * 0.2);
	for (int i = 0; i < 3; i++)
		std::cout << "float test : " << f[i] << std::endl;

	for (int i = 0; i < 3; i++)
		f1.destroy(f + i);
	f1.deallocate(f, 3);


	std::allocator<Test> t1;
	Test *t = t1.allocate(1);
	std::cout << *t << std::endl;
	t1.construct(t, 3, 5);
	std::cout << *t << std::endl;
	t1.destroy(t);
	t1.deallocate(t, 1);

	return (0);
}