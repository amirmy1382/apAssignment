#include <iostream>

using namespace std;

int all_perm(int arr[] , int n , int k,int &count, int index = 0){
    if(index == n){
        int sum = 0;
        for(int i = 0; i < n ; i++){
            sum = sum + arr[i];
        }
        if(sum == k){
            count++;
        }
        return count;
    }
    arr[index] = arr[index] * (-1);
    all_perm(arr, n, k , count, index + 1);
    arr[index] = arr[index] * (-1);
    all_perm(arr, n, k, count, index + 1);
    return count;
}

int main(){
    int n = 0;
    cin >> n;
    int arr[n];
    for(int i = 0 ; i < n ; i++){
        int x = 0;
        cin >> x;
        arr[i] = x;
    }
    int k = 0;
    cin >> k;
    int c = 0;
    cout << all_perm(arr, n, k, c);
}