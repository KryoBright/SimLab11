#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int expRandom(double *probs,int n)
{
	double alpha=rand()*1.0/RAND_MAX;
	int i=0;
	while(((alpha-probs[i])>0)and(i<n-1))
	{
		alpha-=probs[i];
		i++;
	}
	return i;
}

double av(double *probs,int n)
{
	double avrg=0;
	int i=0;
	while(i<n)
	{
		avrg+=i*probs[i];
		i++;
	}
	return avrg;
}


double var(double *probs,int n)
{
	double variance=0;
	int i=0;
	while(i<n)
	{
		variance+=i*i*probs[i];
		i++;
	}
	variance=variance-av(probs,n)*av(probs,n);
	return variance;
}

int main()
{
	srand(unsigned(time(0)));
	int n;
	cout<<"Enter number of probabilities:"<<endl;
	cin>>n;
	double *theoretic=new double[n];
	int i=0;
	while (i<n)
	{
		cout<<endl<<"Enter probability "<<i+1<<":"<<endl;
		cin>>theoretic[i];
		i++;
	}
	cout<<endl<<"Enter number of experiments"<<endl;
	int num;
	cin>>num;
	double *expProb=new double[n];
	i=0;
	while (i<n)
	{
		expProb[i]=0;
		i++;
	}
	i=0;
	while (i<num)
	{
		expProb[expRandom(theoretic,n)]+=1.0/num;
		i++;
	}
	cout<<endl<<"Experemental probabilities:"<<endl;	
	i=0;
	while (i<n)
	{
		cout<<expProb[i]<<endl;
		i++;
	}
	double error=abs(av(expProb,n)-av(theoretic,n))/(av(theoretic,n)+1);
	cout<<"Average: "<<av(expProb,n)+1<<" ( "<<error*100<<"% error)"<<endl;
	
	error=abs(var(expProb,n)-var(theoretic,n))/var(theoretic,n);
	cout<<"Variance: "<<var(expProb,n)+1<<" ( "<<error*100<<"% error)"<<endl;
	
	double chisqr=0;
	i=0;
	while (i<n)
	{
		chisqr+=(expProb[i]*expProb[i])/theoretic[i];
		i++;
	}
	chisqr=(chisqr-1)*num;
	cout<<"Chi squared: "<<chisqr<<endl<<"Compare this to table value to test destribution"<<endl;
	cout<<"(Smaller means that experemental matches theoretical)";
}
