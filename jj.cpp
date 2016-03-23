#include <iostream>
using namespace std;
/*class AbstractMatrix
{
protected:
	int n;
	int m;
	float* data;
public:
     Проблема утечки памяти(оператор копирования)
	 Деструктор
w	AbstractMatrix();
w	AbstractMatrix(int m, int n);
w	virtual AbstractMatrix& operator+(const AbstractMatrix&)=0;
w	virtual AbstractMatrix& operator*(const AbstractMatrix&)=0;
w	virtual AbstractMatrix& operator*(const float&)=0;
w	virtual AbstractMatrix& operator-(const AbstractMatrix&)=0;
w	virtual AbstractMatrix& reverse()=0;
w	virtual AbstractMatrix& transpose()=0;
w	virtual float determinant()=0;
w	virtual ostream& print(ostream& o)=0;
	virtual istream& read(istream& o)=0;
w	virtual void set(int i, int j, float data)=0;
w	virtual float get(int i, int j)=0;
w	virtual int getN()=0;
w	virtual int getM()=0;
	virtual bool failed()=0;
};

AbstractMatrix* get_init()
{
	return NULL;
}*/

class Matrix
{
	int n;
	int m;
	float* data;
public:
	Matrix& operator+(const Matrix& res)
	{

		if(res.m!=m||res.n!=n)
		{
			 cout<<"Error in size of matrixs."<<endl;
			Matrix*tmp=new Matrix;
			tmp->data[0]=0;
			return *tmp;
		}

		Matrix* tmp=new Matrix;
		tmp->m=this->m;
		tmp->n=this->n;
		tmp->data=new float[n*m];

		for(int i=0; i<(n*m); i++)
		{
			tmp->data[i]=data[i]+res.data[i];


		}
		return *tmp;
	}
	Matrix& operator-(const Matrix& res)
	{

		if(res.m!=m||res.n!=n)
		{
			 cout<<"Error in size of matrixs."<<endl;
			Matrix*tmp=new Matrix;
			tmp->data[0]=0;
			return *tmp;
		}

		Matrix* tmp=new Matrix;
		tmp->m=this->m;
		tmp->n=this->n;
		tmp->data=new float[n*m];

		for(int i=0; i<(n*m); i++)
		{
			tmp->data[i]=data[i]-res.data[i];


		}
		return *tmp;
	}
	Matrix& operator*(float value)
	{
		Matrix* res=new Matrix;
		float*c=new float[n*m];
		res->m=this->m;
		res->n=this->n;

		res->data=c;

		int i=0;
		while(i!=(n*m))
		{
			res->data[i]=value*this->data[i];

			i++;
		}
		delete[] data;
		return *res;

	}
     Matrix& operator*(const Matrix& res)
	 {
		 if(this->m!=res.n)
		 {
			 cout<<"Error in size of matrixs."<<endl;
			 Matrix* tmp2=new Matrix;
			 tmp2->data[0]=0;
			 return *tmp2;
		 }
		 float z=0;
		 int e=1; int d=1;
		 Matrix* tmp=new Matrix;
		 int h;
		 tmp->data=new float[this->n*res.m];
		 tmp->n=this->n;
		 tmp->m=res.m;
		 int i=0;
		 while(e!=this->n+1 && d!=res.m+1)
		 {
			 z=0;
			 h=1;
			 while(h!=res.n+1)
			 {
				 z=z+data[(((e-1)*n+h)-1)]*(res.data[(((h-1)*res.m+d)-1)]);
				 //cout<<"1first"<<res.data[(((h-1)*res.m+d)-1)]<<endl;
				 //cout<<z<<endl;
				 h++;

			 }
			 //cout<<z<<endl;
			 tmp->data[i]=z;
			 i++;
			 d++;
			 if(d>res.m)
			 {
				 d=1;
				 e++;
			 }

		 }
		 return *tmp;

	 }
	Matrix& transpose()
	{
		
		Matrix* res=new Matrix;
		float*c=new float[n*m];
		res->m=this->m;
		res->n=this->n;

		res->data=c;

		int a1,a2;
		a1=1;
		a2=1;
		while(a1!=n+1 && a2!=m+1)
		{
			res->data[(((a1-1)*n+a2)-1)]=this->data[(((a2-1)*m+a1)-1)];

				a2++;
				if(a2>n)
				{
					a1++;
					a2=1;
				}
		}
	
	
	
		return *res;
	}
	Matrix()
	{
		data=new float;
		data[0]=1;
		this->m=1;
		this->n=1;
	}
	Matrix(int n, int m)
	{
		this->n=n;
		this->m=m;
		float* a=new float[n*m];
		data=a;
		int i=0;
		while(i!=(n*m))
		{
			float a;
			a=rand()%34;
			//cin>>a;

			data[i]=a;
			i++;
		}


	}
	/*Matrix(const Matrix& a)
	{
	

	}*/
	~Matrix()
	{
		cout<<"deconstr"<<endl;
		delete[] data;

	}
	float determinant()
	{
		if(n!=m)
		{
			cout<<"It is incorrect."<<endl;
			return 0;

		}
		float D=0;
		if((n*m)==4)
		{
			float b1=data[0]*data[3];
			float b2=data[1]*data[2];
			D=b1-b2;
			return D;
		}
	
		
		int c1=1; int c2=1;
		while(c2!=m+1)
		{

			Matrix a;
			float*c=new float[(n-1)*(m-1)];
			a.data=c;
			a.m=m-1;
			a.n=n-1;
			int a1=1;
			int a2=1;
			int a3=0;
			while(a1!=n+1 && a2!=m+1)
			{


				if(a1!=c1 && a2!=c2)
				{
					a.data[a3]=data[(((a1-1)*n+a2)-1)];
					a3++;
				}
				a2++;
				if(a2>n)
				{
					a1++;
					a2=1;
				}
			}
			int a4;
			if((c1+c2)%2==0)
			{
				a4=1;
			}
			else
			{
				a4=-1;
			}
			D=D+a4*data[(((c1-1)*n+c2)-1)]*a.determinant();
			c2++;
			//delete c;
		}
		return D;
	}
	Matrix& reverse()
	{

	
		float x=0;
		
		Matrix* b=new Matrix;
		if(n!=m)
		{
			b->data[0]=0;
			cout<<"It is impossible.This matrix is not backwards"<<endl;
			return *b;
		}
		if(n==2)
		{
		
			float b1=data[0]*data[3];
			float b2=data[1]*data[2];
			x=b1-b2;
			if(x==0)
			{
				b->data[0]=0;
				cout<<"It is impossible.This matrix is not backwards"<<endl;
				return *b;
			}
			
			b->data=new float[4];
			b->m=2;
			b->n=2;
			b->data[0]=this->data[3];
			b->data[3]=this->data[0];
			b->data[1]=-this->data[1];
			b->data[2]=-this->data[2];
			

			*b=*b*(1/x);
			return *b;
		



		}
			float*d=new float[n*m];
			b->data=d;
			b->m=m;
			b->n=n;
		

		int c1=1; int c2=1;
		while(c2!=m+1 && c1!=n+1)
		{
			Matrix a;
			float*c=new float[(n-1)*(m-1)];
			a.data=c;
			a.m=m-1;
			a.n=n-1;
			int a1=1;
			int a2=1;
			int a3=0;
			
			while(a1!=n+1 && a2!=m+1)
			{


				if(a1!=c1 && a2!=c2)
				{
					a.data[a3]=data[(((a1-1)*n+a2)-1)];
					a3++;
				}
				a2++;
				if(a2>n)
				{
					a1++;
					a2=1;
				}
			}
			int a4;
			if((c1+c2)%2==0)
			{
				a4=1;
			}
			else
			{
				a4=-1;
			}

			x=x+a4*data[(((c1-1)*n+c2)-1)]*a.determinant();
			b->data[(((c2-1)*n+c1)-1)]=a4*a.determinant();
			c2++;
				if(c2>m)
				{
					c1++;
					c2=1;
				}
				
			//delete c;
		}
		//Matrix* f=new Matrix;
		//f=&b->reverse();
		x=x/3;
		if(x==0)
		{
			delete b;
			Matrix *k=new Matrix;
			k->data[0]=0;
			cout<<"It is impossible.This matrix is not backwards"<<endl;
			return *k;


		}
		*b=*b*(1/x);
		cout<<x<<endl;
		return *b;


	}
	float get(int i, int j)
	{
		float d;
		d=data[(((i-1)*m+j)-1)];
		return d;


	}
	void set(int i, int j,float data)
	{
		
		this->data[(((i-1)*m+j)-1)]=data;
	}

	int getN()
	{
		return this->n;
	}
	int getM()
	{
		return this->m;
	}
	ostream& print(ostream& o)
	{
		int i=0;
	while(i!=(n*m))
	{
		if(i % m != 0)
			o<<"    "<<data[i]<<"\t";
		else
			o<<"\n"<<data[i];

		i++;
	}
	o<<"\n";
	i=0;
	while(i!=m)
	{
	o<<"\\\\\\\\\\\\";
	i++;
	}
	o<<"\n";
	return o;

	}

friend void print(Matrix& a);



};

void print(Matrix& a)
{
	int i=0;
	while(i!=(a.n*a.m))
	{
		if(i % a.m != 0)
			cout<<"    "<<a.data[i]<<"\t";
		else
			cout<<"\n"<<a.data[i];

		i++;
	}
	cout<<"\n";
	i=0;
	while(i!=a.m)
	{
	cout<<"\\\\\\\\\\\\";
	i++;
	}
	cout<<"\n";
}


void main()
{
	
	Matrix one(3,4);
	print(one);
	float d;
	one.print(cout);
	
	//float D;
	/*while(true)
	{
		Matrix one(3,3);
	one=one*2;
	}*/

	/*print(one);
	Matrix two(3,3);
	print(two);
	Matrix res=one-two;
	print(res);*/
	
	//one=one.reverse();
	//print(one);
	//D=one.determinant();
	
	//cout<<"\t"<<D<<endl;
	
}