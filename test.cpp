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

class West {
	public:
		int *numptr;

		West(int num)
		{
			std::cout << "생성자 실행" << std::endl;
			numptr = new int;
			*numptr = num;
		}
		void print_num()
		{
			std::cout << *(this->numptr) << std::endl;
		}
		~West()
		{
			std::cout << *numptr << "소멸자 실행" << std::endl;
			delete numptr;
		}
};

std::ostream	&operator<<(std::ostream &out, Test const &t)
{
	out << t.getN() << " " << t.getT();
	return out;
}

int main()
{
	std::allocator<West> talloc;
	std::allocator<West>::pointer tp;
	tp = talloc.allocate(5);
	for (int i = 0; i < 5; i++)
	{
		talloc.construct(tp + i, i);
	}
	for (int i = 0; i < 4; i++)
	{
		std::cout << "destroy" << std::endl;
		talloc.destroy(tp + i);
	}
	talloc.deallocate(tp, 5);
	// allocator test
	std::allocator<int> a1;
	// int *a = a1.allocate(1);
	std::allocator<int>::pointer a = a1.allocate(1);
	std::cout << "after allocate " << a[0] << std::endl;
	a1.construct(a, 13);
	std::cout << "after construct " <<  a[0] << std::endl;
	a1.destroy(a);
	std::cout <<"after destroy " << a[0] << std::endl;
	a1.deallocate(a, 1);
	std::cout <<"after deallocate " << a[0] << std::endl;

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