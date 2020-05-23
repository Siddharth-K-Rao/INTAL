#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "intal.h"

static char *copy_string(const char *string)
{
    int len_string=strlen(string);
    char *temp = malloc(sizeof(char)*(len_string+1));
    strcpy(temp,string);
    return temp;
}


static char *copy_mod(const char *string)
{
    char *temp = malloc(sizeof(char)*1001);
    strcpy(temp,string);
    return temp;
}


static char **create_array(int n)
{
    char **p=malloc(sizeof(char *)*n);
    return p;
}


static char *toString(int unsigned n)
{
	int rem;
	char *str;
	int num = n;
	int len = 0;
	while(num!=0)
	{
		len++;
		num/=10;
	}
	str = malloc(sizeof(char)*(len+1));
	for(int i=0;i<len;++i)
	{
		rem = n%10;
		n = n/10;
		str[len-(i+1)] = rem + '0';
	}
	str[len] = '\0';
	return str;
}


static void revstr(char *string) 
{ 
    int count = strlen(string); 
    for (int i = 0; i < count / 2; i++) 
	{
	    char temp=string[i];
		string[i]=string[count-i-1];
		string[count-i-1]=temp;
	}	 
} 


int intal_compare(const char* intal1, const char* intal2)
{
	int len_intal1 = strlen(intal1);
	int len_intal2 = strlen(intal2);
	
	if(len_intal1<len_intal2)
	{
		return -1;
	}
	else if(len_intal1>len_intal2)
	{
		return 1;
	}
	else
	{
		for(int i=0;i<len_intal1;i++)
		{
			if(intal1[i]<intal2[i])
			{
				return -1;
			}
			else if(intal1[i]>intal2[i])
			{
				return 1;
			}
		}
	return 0;
	}
}


char* intal_add(const char* intal1, const char* intal2)
{
	char *intal1_copy = copy_string(intal1);
	char *intal2_copy = copy_string(intal2);
	int len1 = strlen(intal1_copy);
	int len2 = strlen(intal2_copy);
	char *answer;
	int max = (len1>len2) ? len1:len2;
	int min = (len1>len2) ? len2:len1;
	answer = (char *)malloc(sizeof(char)*(max+2));
	int carry = 0;
	int k = 0;
	if(intal_compare(intal1_copy,intal2_copy)==-1)
	{
		char *temp = intal1_copy;
		intal1_copy = intal2_copy;
		intal2_copy = temp;
	}
	revstr(intal1_copy);
	revstr(intal2_copy);
	
	for(int i=0; i<min; i++) 
	{ 
	    int sum = (intal1_copy[i]-'0') + (intal2_copy[i]-'0') + carry; 
	    answer[k++] = '0' + sum%10;
	    carry = sum/10; 
	} 
	  
	for(int i=min; i<max; i++) 
	{ 
	    int sum = (intal1_copy[i]-'0') + carry; 
	    answer[k++] = '0' + sum%10;
	    carry = sum/10;  
	} 
	  
	 
	if(carry)
	{ 
	    answer[k++] = '0' + carry;
	} 
	answer[k] = '\0';
	  
	revstr(answer);
	free(intal1_copy);
	free(intal2_copy);
	return answer; 
}


char* intal_diff(const char* intal1, const char* intal2)
{
	char *intal1_copy = copy_string(intal1);
	char *intal2_copy = copy_string(intal2);
	
	if((intal_compare(intal1_copy,intal2_copy))==0)
	{
		char *answer = malloc(sizeof(char)*2);
		answer[0] = '0';
		answer[1] = '\0';
		return answer;
	}
	if((intal_compare(intal1_copy,intal2_copy))==-1)
	{
		char *temp = intal1_copy;
		intal1_copy = intal2_copy;
		intal2_copy = temp;
	}
	int len1 = strlen(intal1_copy);
	int len2 = strlen(intal2_copy);
	char *answer;
	
	int max = (len1>len2) ? len1:len2;
	int min = (len1>len2) ? len2:len1;
	answer = (char *)malloc(sizeof(char)*(max+2));
	
	revstr(intal1_copy);
	revstr(intal2_copy);
	
	int borrow = 0;
	int k = 0;
	
	for (int i=0; i<min; i++) 
	{ 
	    int diff = (intal1_copy[i]-'0')-(intal2_copy[i]-'0') - borrow;
		
		if(diff<0)
		{
			diff+=10; 
			borrow=1;
		}
		    
		else
		{
			borrow=0;
		}
		answer[k++] = '0' + diff;
	}
	  
	for (int i=min; i<max; i++) 
	{ 
		int diff = (intal1_copy[i]-'0')-borrow;
		if(diff<0)
		{
			diff+=10; 
			borrow=1;
		}
		else
		{
			borrow=0;
		}
		answer[k++]='0' + diff;  
	}
	k--;
	while(answer[k]=='0')
	{
		k--;
	}
	k++;
	answer[k]='\0';
	  
	revstr (answer);
	free(intal1_copy);
	free(intal2_copy);
	    
	return answer; 
}


char* intal_multiply(const char* intal1, const char* intal2)
{
	if(intal1[0]=='0'||intal2[0]=='0')
	{
		char *answer = (char*)malloc(sizeof(char)*2);
		answer[0]='0';
		answer[1]='\0';
		return answer;
	}
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);
	int product_len = len1 + len2;
    char *result = malloc(sizeof(char)*(product_len+2));  
    int num1 = 0;  
    int num2 = 0;  
    int i;
    for(int i=0;i<product_len+2;i++)
	{
		result[i]='0';
	}
    for (i = len1-1; i>=0; i--)  
    {  
        int carry = 0;  
        int n1 = intal1[i] - '0';
        num2 = 0;            
        for (int j = len2-1; j>=0; j--)  
        {  
            int n2 = intal2[j] - '0';  
  			int sum = n1*n2 +(result[num1 + num2]-'0') + carry;  
            carry = sum / 10;  
            result[num1 + num2] = '0' + (sum % 10);  
  			num2++;  
        }  
  
        if (carry > 0)  
            result[num1 + num2] = '0' + result[num1 + num2]-'0' + carry;  
  
        num1++;  
    }
	int k = num1 + num2;
	k--;
	while(result[k]=='0')
	{
		k--;
	}
	if(k==-1)
	{
		result[++k] = '0';
		result[++k] = '\0';
	}
	result[k+1]='\0';
	revstr(result);
	return result;
}


char* intal_mod(const char* intal1, const char* intal2)
{
    if((intal_compare(intal1,intal2)) == 0)
	{
        char *answer = (char*)malloc(sizeof(char)*2);
        answer[0] = '0';
        answer[1] = '\0';
        return answer;
    }

    char *intal1_copy = copy_mod(intal1);
    char *intal2_copy = copy_mod(intal2);
    char *temp;

   
    while(intal_compare(intal1_copy,intal2_copy)==1)
	{
        while(intal_compare(intal1_copy,intal2_copy)==1)
		{
            strcat(intal2_copy,"0");
        }
        intal2_copy[strlen(intal2_copy)-1] = '\0';
        while(intal_compare(intal1_copy,intal2_copy)==1)
		{
            temp = intal_diff(intal1_copy,intal2_copy);
            intal1_copy = copy_mod(temp);
            free(temp);
        }
        intal2_copy = copy_mod(intal2);
	}
    free(intal2_copy);
    return intal1_copy;
}


char* intal_pow(const char* intal1, unsigned int n)
{
	//If the value of n is zero, then it returns one as the answer
	if(n==0)
	{
		char *answer = (char*)malloc(sizeof(char)*2);
		answer[0] = '1';
		answer[1] = '\0';
		return answer;
	}
	//Here, we are using decrease by a constant factor and conquer approach
	else if(n%2==1)
	{
		return intal_multiply(intal_multiply(intal_pow(intal1,(n-1)/2),intal_pow(intal1,(n-1)/2)),intal1);
	}
	else
	{
		return intal_multiply(intal_pow(intal1,n/2),intal_pow(intal1,n/2));
	}
}


char* intal_gcd(const char* intal1, const char* intal2)
{
	char *intal1_copy = copy_string(intal1);
	char *intal2_copy = copy_string(intal2);
	char *remainder;
	char *temp = (char*)malloc(sizeof(char)*1000);
	//Until the second number is greater than 0,it keeps looping
	while(intal_compare(intal2_copy,"0")>0)
	{
		strcpy(temp,intal2_copy);
		remainder = intal_mod(intal1_copy,intal2_copy);
		strcpy(intal1_copy,temp);
		strcpy(intal2_copy,remainder);
		free(remainder);
	}
	free(intal2_copy);
    free(temp);
    return intal1_copy;
}


char* intal_fibonacci(unsigned int n)
{
	//Storing the value 0 in x. If n is 0, then it returns the value of x which is 0
	char *x = (char*)malloc(sizeof(char)*2);
	x[0] = '0';
	x[1] = '\0';
	if(n==0)
		return x;
	
	//Storing the value 1 in y.
	char *y = (char*)malloc(sizeof(char)*2);	
	y[0] = '1';
	y[1] = '\0';
	if(n==1)
		return y;
	
	//Performs addition of the two numbers and swapping happens	
	for(int i=1;i<n;++i)
	{
		char *z = intal_add(x,y);
		free(x);
		x = y;
		y = z;
	}
	free(x);
	return y;
}


char* intal_factorial(unsigned int n)
{
	//If n is 0, it returns answer as 1
	if(n==0)
	{
		char *answer = (char*)malloc(sizeof(char)*2);
		answer[0] = '1';
		answer[1] = '\0';
		return answer;	
	}
	//Does the operation n*(n-1)!	
	return intal_multiply(toString(n),intal_factorial(n-1));
}


char* intal_bincoeff(unsigned int n, unsigned int k)
{
	char **C = (char**)malloc(sizeof(char*)*(k+1));
  	for(int i = 0; i < k + 1; ++i) 
	{
	    C[i] = (char*)malloc(sizeof(char)*2);
	    C[i][0] = '0';
	    C[i][1] = '\0';
  	}

  	C[0][0] = '1';

  	for(int i = 1; i <=n; ++i)
	{
	    int min = (i<k) ? i:k;
	    for(int j=min;j>0;j--)
	    {
	    	char *temp = C[j];
	    	C[j] = intal_add(C[j],C[j-1]);
	    	free(temp);
		}
  	}

  	char *answer = (char*)malloc(sizeof(char)*(strlen(C[k])+1));
  	answer = copy_string(C[k]);
  
  	for(int i = 0; i < k + 1; ++i) 
	{
    	free(C[i]);
  	}
  	free(C);

  	return answer;
}


int intal_max(char **arr, int n)
{
	char *l_intal = arr[0];
	int offset = 0;
	for(int i=1;i<n;i++)
	{
		if(intal_compare(arr[i],l_intal)==1)
		{
			l_intal = arr[i];
			offset = i;
		}
	}
	return offset;
}


int intal_min(char **arr, int n)
{
	char *s_intal = arr[0];
	int offset = 0;
	for(int i=1;i<n;i++)
	{
		if(intal_compare(arr[i],s_intal)==-1)
		{
			s_intal = arr[i];
			offset = i;
		}
	}
	return offset;
}


int intal_search(char **arr, int n, const char* key)
{
	for(int i=0;i<n;i++)
	{
		if(intal_compare(arr[i],key)==0)
			return i;
	}
	return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
	int l = 0;
	int r = n-1;
	char *key_copy = copy_string(key);
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(intal_compare(arr[mid],key_copy)==0)
		{
			free(key_copy);
			return mid;
		}
		else if(intal_compare(arr[mid],key_copy)<0)
			l = mid+1;
		else
			r = mid-1;		
	}
	return -1;
}


static void merge(char **arr,int l,int mid,int r)
{
	int n = (r-l)+1;
	char **temp = create_array(n);
	int i = 0;
	int j = mid+1;
	int k = 0;
	while(i<=mid && j<=r)
	{
		temp[k++] = (intal_compare(arr[i],arr[j])<=0) ? arr[i++]:arr[j++];
	}
	while(i<=mid)
	{
		temp[k++] = arr[i++];
	}
	while(j<=r)
	{
		temp[k++] = arr[j++];
	}
	for(int i=0;i<=r;i++)
    {
        arr[i] = temp[i];
    }
    free(temp);  
}


static void mergesort(char **arr,int l,int r)
{
	int mid;
	if(l<r)
	{
		mid = l+(r-l)/2;
		mergesort(arr,l,mid);
		mergesort(arr,mid+1,r);
		merge(arr,l,mid,r);
	}
}


void intal_sort(char **arr, int n)
{
	mergesort(arr,0,n-1);
}


char* coin_row_problem(char **arr, int n)
{
    char *prev=malloc(2001);
    char *cur=malloc(2001);
	strcpy(prev,"0");	
    strcpy(cur,arr[0]);
    char *answer=malloc(2001);  
	char *next=NULL;      
    if(n==0)
    {
        strcpy(answer,prev);
        free(prev);
        free(cur);
    }
    else
    {
        for(int i=2;i<n+1;i++)
        {
            char *sum = intal_add(prev,arr[i-1]);
            if(intal_compare(sum,cur)>=0)
            {
                next=sum;
            }  
            else
            {
                next=cur;
                free(sum);
            }
            if(prev!=cur)
                free(prev);
            prev=cur;
            cur=next;
        }
        strcpy(answer,cur);
        free(cur);
    }
	return(answer);
}
