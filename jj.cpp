#include <iostream>
using namespace std;
/*class AbstractMatrix
{
protected:
	int n;
	int m;
	float* data;
public:
 w    Проблема утечки памяти(оператор копирования)
w	 Деструктор(решена убиранием  &. Теперь возращаем объект матрицы)
w	Matrix();
w	Matrix(int m, int n);
w	virtual Matrix operator+( Matrix&);
w	virtual Matrix operator*( Matrix&);
w	virtual Matrix operator*( float&);
w	virtual Matrix operator-( Matrix&);
w	virtual Matrix reverse();
w	virtual Matrix transpose();
w	virtual float determinant();
w	virtual ostream& print(ostream& o);
w	virtual istream& read(istream& o);
w	virtual void set(int i, int j, float data);
w	virtual float get(int i, int j);
w	virtual int getN();
w	virtual int getM();
w	virtual bool failed();
};
Matrix* get_init()
{
	return NULL;
}*/

class Matrix
{
	int n;
	int m;
	float* data;
public:

	Matrix operator+( Matrix& res)
	{

		if(res.m!=m||res.n!=n)
		{
			 cout<<"Error in size of matrixs."<<endl;
			Matrix tmp;
			tmp.data[0]=0;
			return tmp;
		}

		Matrix tmp;
		tmp.m=this->m;
		tmp.n=this->n;
		tmp.data=new float[n*m];

		for(int i=0; i<(n*m); i++)
		{
			tmp.data[i]=data[i]+res.data[i];


		}
		return tmp;
	}
	Matrix operator-( Matrix& res)
	{

		if(res.m!=m||res.n!=n)
		{
			 cout<<"Error in size of matrixs."<<endl;
			Matrix tmp;
			tmp.data[0]=0;
			return tmp;
		}

		Matrix tmp;
		tmp.m=this->m;
		tmp.n=this->n;
		tmp.data=new float[n*m];

		for(int i=0; i<(n*m); i++)
		{
			tmp.data[i]=data[i]-res.data[i];


		}
		return tmp;
	}
	Matrix operator*(float value)
	{
		Matrix res;
		res.data=new float[n*m];
		res.m=this->m;
		res.n=this->n;
		int i=0;
		while(i!=(n*m))
		{
			res.data[i]=value*this->data[i];

			i++;
		}
		return res;

	}
     Matrix operator*(Matrix& res)
	 {
		 if(this->m!=res.n)
		 {
			 cout<<"Error in size of matrixs."<<endl;
			 Matrix tmp;
			 tmp.data[0]=0;
			 return tmp;
		 }
		 float z=0;
		 int e=1; int d=1;
		 Matrix tmp;
		 int h;
		 tmp.data=new float[this->n*res.m];
		 tmp.n=this->n;
		 tmp.m=res.m;
		 int i=0;
		 while(e!=this->n+1 && d!=res.m+1)
		 {
			 z=0;
			 h=1;
			 while(h!=res.n+1)
			 {
				 z=z+data[(((e-1)*n+h)-1)]*(res.data[(((h-1)*res.m+d)-1)]);
				 h++;

			 }
			 tmp.data[i]=z;
			 i++;
			 d++;
			 if(d>res.m)
			 {
				 d=1;
				 e++;
			 }

		 }
		
		 return Matrix(tmp);

	 }
	Matrix transpose()
	{
		Matrix res;
		res.data = new float[n*m];
		
		res.n = this->m; res.m = this->n;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				res.data[j*n + i] = this->data[i*m + j];
		
		
		return res;
	}
	Matrix()
	{
		this->n=0;
		this->m=0;
		this->data=NULL;
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
			a=rand()%3;

			data[i]=a;
			i++;
		}


	}/*
Matrix(int n, int m)
	{
		this->n=n;
		this->m=m;
		float* a=new float[n*m];
		data=a;
		int c1=1; int c2=1;
		while(c1!=n+1 && c2!=m+1)
		{
			data[(((c1-1)*n+c2)-1)]=0;
			if(c1==c2)
				data[(((c1-1)*n+c2)-1)]=1;
			c1++;
			if(c1>n)
			{
				c1=1;
				c2++;
			}
			if(c2>m)
				break;
		}
		*/

	
	Matrix(const Matrix& a)
	{
		this->m=a.m;
		this->n=a.n;
		data=new float[n*m];
		int i=0;
		while(i!=n*m)
		{
			this->data[i]=a.data[i];
			i++;
		}
	//cout<<"copy"<<endl;

	}
	Matrix& operator=(const Matrix& a)
	{
		delete data;
		this->m=a.m;
		this->m=a.n;
		this->data=new float[a.n*a.m];
		int i=0;
		while(i!=n*m)
		{
			this->data[i]=a.data[i];
			i++;

		}
		//cout<<"="<<endl;
		return (*this);
	}
	~Matrix()
	{

		//cout<<"deconstr"<<endl;
		delete this->data;

	}
	float determinant()
	{
		/*if(n!=m)
		{
			cout<<"It is incorrect."<<endl;
			return 0;

		}*/
		float D=0;
		/*if((n*m)==4)
		{
			float b1=data[0]*data[3];
			float b2=data[1]*data[2];
			D=b1-b2;
			return D;
		}*/
	if(n==1 && m==1)
	{
		return data[0];
	}
		
		int c1=1; int c2=1;
		while(c2!=m+1)
		{

			Matrix a;
			a.data=new float[(n-1)*(m-1)];
			a.m=m-1;
			a.n=n-1;
			int a1=1;
			int a2=1;
			int a3=0;
			while(a1!=n+1 && a2!=m+1)
			{
				if(data[(((c1-1)*n+c2)-1)]==0)
				{
					goto next;
				}

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
				if(a1==m+1)
					break;
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
			next:
			c2++;
		
		}
		
		return D;
	}
	Matrix reverse()
	{


		float x=0;
		
		Matrix b;
		if(n!=m)
		{
			
			
			cout<<"It is impossible.This matrix is not backwards"<<endl;
			return b;
		}
		/*if(n==2)
		{
		
			float b1=data[0]*data[3];
			float b2=data[1]*data[2];
			x=b1-b2;
			if(x==0)
			{
				
				cout<<"It is impossible.This matrix is not backwards"<<endl;
				return b;
			}
			
			b.data=new float[4];
			b.m=2;
			b.n=2;
			b.data[0]=this->data[3];
			b.data[3]=this->data[0];
			b.data[1]=-(this->data[1]);
			b.data[2]=-(this->data[2]);
			

			b=b*(1/x);
			return b;
		



		}*/
			
			b.data=new float[n*m];
			b.m=m;
			b.n=n;
		
			
		int c1=1; int c2=1;
		while(c2!=m+1 && c1!=n+1)
		{
			Matrix a;
			a.data=new float[(n-1)*(m-1)];
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
			if(data[(((c1-1)*n+c2)-1)]==0)
				goto next;
			x=x+a4*data[(((c1-1)*n+c2)-1)]*a.determinant();
			next:
			b.data[(((c2-1)*n+c1)-1)]=a4*a.determinant();
			c2++;
			
			if(c2>m)
				{
					c1++;
					c2=1;
				}

		}
		
		x=x/n;
		if(x==0)
		{
			Matrix k;
			cout<<"It is impossible.This matrix is not backwards"<<endl;
			return k;
		}		
		b=b*(1/x);
		//cout<<x<<endl;
		return b;

	}
	float get(int i, int j)
	{
		return data[(((i-1)*m+j)-1)];
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
	istream& read(istream& o)
	{
		delete data;
		cout<<"Size of matrix."<<endl;
		cout<<"n=";
		o>>this->n;
		cout<<"m=";
		o>>this->m;
		this->data=new float[n*m];
		int i=0;
		cout<<"Insert data."<<endl;
		while(i!=n*m)
		{
			
			o>>data[i];
			i++;
		}
		return o;
	}
	virtual bool failed()
	{
		bool a=false;
		if(n==0)
		{
			a=true;
		}
		if(m==0)
		{
			a=true;
		}
		if(data==NULL)
		{
			a=true;
		}

		return a;
	}

};
Matrix* get_init(int n,int m)
{
	return new Matrix(n,m);
}
/*void main()
{int i=0;
	Matrix a(3,3);
	//Matrix c(10,10);
	float d=a.determinant();
	Matrix b(3,2);
	b.print(cout);
	Matrix k=b.transpose();
	k.print(cout);
	//a.print(cout);
	//cout<<d<<endl;
	/*while(true)
	{
		Matrix b;
		b=a.reverse();
		float k=a.determinant();
		b=a.transpose();
		b=a*c+c*2;
		i++;
		if(i==10)
			break;
	}	*/
	
	//Matrix b=a.transpose();
	//b.print(cout);
	//a.print(cout);
	//int k=a.determinant();
	


}*/



