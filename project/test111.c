#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int threeSumClosest(int* nums, int numsSize, int target) {
    for(int i=0;i<numsSize-1;i++){
        for(int j=0;j<numsSize-1-i;j++){
            if(nums[j]<nums[j+1]){
              int t=nums[j];
              nums[j]=nums[j+1];
              nums[j+1]=t;
            }
        }
    }
  int sum1=0,sum=nums[0]+nums[1]+nums[2];
  int min=INT_MAX;
  for(int i=0;i<numsSize-2;i++){
    int start=i+1,end=numsSize-1;
  while(start<end){
    sum=nums[start]+nums[end]+nums[i];
      int object=abs(sum-target);
      if(object<min){
        min=object;
        sum1=sum;
      }
    }
    start++;end--;
  }
  return sum1;
}
int main() {
    int nums[]={-1,2,1,-4};
    int target=1;
    int result=threeSumClosest(nums,4,target);
    printf("%d\n",result);
    return 0;
}