#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector
{
private:
    T* Tdata;
    size_t Tsize;
    size_t Tcapacity;

public:
    SimpleVector() : Tdata(new T[10]), Tsize(0), Tcapacity(10) {}
    SimpleVector(size_t n) : Tdata(new T[n]), Tsize(0), Tcapacity(n) {}
    SimpleVector(const SimpleVector& other) : Tdata(new T[other.Tcapacity]), Tsize(other.Tsize), Tcapacity(other.Tcapacity)
    {
        for (size_t i = 0; i < Tsize; ++i)
            Tdata[i] = other.Tdata[i];
    }

    ~SimpleVector() { delete[] Tdata; }


    void push_back(const T& value) 
    {
        if (Tsize < Tcapacity) 
        {
            Tdata[Tsize++] = value;
        } 
        else if (Tsize >= Tcapacity)
        {
            resize(Tcapacity + 5);
        }
    }

    void pop_back() 
    {
        if (Tsize > 0) 
        {
            --Tsize;
        }
    }

    void resize(size_t newCapacity)
    {
		if (newCapacity <= Tcapacity) return;

        T* newData = new T[newCapacity];
        for (size_t i = 0; i < Tsize; ++i)
            newData[i] = Tdata[i];
        delete[] Tdata;

        Tdata = newData;
		Tcapacity = newCapacity;
    }

    void sortData()
    {
		sort(Tdata, Tdata + Tsize);
    }

    size_t size() const { return Tsize; }

    size_t capacity() const { return Tcapacity; }

    T get(size_t index) const 
    {
		return Tdata[index];
	}
};

int main()
{
    SimpleVector<int> v(5);
    int n;
    cin >> n;

    v.push_back(n);

    cout << "백터의 길이는 : " << v.size() << ", 백터의 크기는 : " << v.capacity() << endl;

    cout << "push 하고 싶은 길이는 : ";
	cin >> n;
    for (int i = 0; i < n; ++i) 
    {   
		int value;
        cout << "값을 입력하세요: ";
        cin >> value;
        v.push_back(value);
	}
	cout << "push 이후 길이는 : " << v.size() << endl;

	v.sortData();
    cout << "정렬된 이후 백터은 : ";
    for (int i = 0; i < v.size(); ++i) 
    {
        cout << v.get(i) << " ";
	}
	cout << endl;

    v.pop_back();
    cout << "pop 이후 길이는 : " << v.size() << endl;

    return 0;
}
