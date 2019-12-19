int n,m;
int a[50005] = {0},c[50005]; //��Ӧԭ�������״����

int lowbit(int x){
    return x&(-x);
}

void updata(int i,int k){    //��iλ�ü���k
    while(i <= n){
        c[i] += k;
        i += lowbit(i);
    }
}

int getSum(int i){        //��D[1 - i]�ĺͣ���A[i]ֵ
    int res = 0;
    while(i > 0){
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}

int main(){
    cin>>n;27     for(int i = 1; i <= n; i++){
        cin>>a[i];
        updata(i,a[i] - a[i-1]);   //�����ֵ��ʱ��Ҳ�൱�ڸ�����ֵ
    }

    //[x,y]�����ڼ���k
    updata(x,k);    //A[x] - A[x-1]����k
    updata(y+1,-k);        //A[y+1] - A[y]����k

    //��ѯiλ�õ�ֵ
    int sum = getsum(i);

    return 0;
}
