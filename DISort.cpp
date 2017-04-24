#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class DIsort{
	public:
		std::vector <int> A;
		int n;
		int m;
		void input(std::vector<int>*,int*);
		void print(void);
		void combine(vector<int>*,int,int,int);
		void DISort(std::vector<int>,int,int,int);
		void swap(std::vector<int>*,int,int,int);
};
void DIsort :: input(std::vector<int>*A,int *n){
	cin >> *n;
	int input1;
	int a=0;
	while(++a<=*n && cin >> input1)
		A->push_back(input1);
}
void DIsort :: print(void){
	for(int i=0;i<n;i++)
		cout << A[i]<<endl;
}
void DIsort :: DISort (vector <int> A,int l,int m,int h){
	DIsort :: swap(&A,l,m,h);
	if(h-l<=2) return;
	DISort(A,l,(l+m)/2,m);
	DISort(A,m+1,(m+h+2)/2,h);
	swap(&A,l,m,h);
}
void DIsort :: swap(vector <int> *A,int l,int m,int h){
	vector<int> temp;
	for (int i = l; i <= m;i++)
	{
		//if(A[i]>A[h-i]){
		//	temp=*(A+i);
		//	*(A+i)=*(A+h-i);
		//	*(A+h-i)=temp;
		//}
		cout << *(A+i);
	}
}
void DIsort :: combine (vector <int> *A,int l,int m,int h){
	int i=l,j=m+1,k=l;
	vector <int> C;
	while(i<=m && j<=h){
		if(A[i]<A[j]){
			C[k]=A[i];
			i++;
			k++;
		}
		else{
			C[k]=A[j];
			j++;
			k++;
		}
	}
	while(i<=m){
		C[k]=A[i];
		k++;
		i++;
	}
	while(j<=h){
		C[k]=A[j];
		k++;
		j++;
	}
	for (int i = l; i < k;i++)
		A[i]=C[i];
}
int main(void){
	DIsort instance;
	instance.input(&instance.A,&instance.n);
	instance.m=(instance.n-1)/2;
	int start=clock();
	instance.swap(&instance.A,0,(instance.n-1)/2,instance.n-1);
	//instance.DISort(instance.A,0,instance.m/2,instance.m);
	//instance.DISort(instance.A,instance.m+1,(instance.n-instance.m-2)/2,instance.n-1);
	//instance.combine(&instance.A,0,(instance.n-1)/2,instance.n-1);
	int end=clock();
	cout << "Time: " << (end-start)/double(CLOCKS_PER_SEC)*1000 <<"s"<< endl;
	instance.print();
	return 0;
}