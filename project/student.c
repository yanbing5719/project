#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
struct ListNode {
     int val;
      struct ListNode *next;
  };
struct ListNode*merge(struct ListNode*list1,struct ListNode*list2){
    struct ListNode head;
    struct ListNode* tail =&head;
    head.next = NULL;
    while(list1!=NULL&&list2!=NULL){
        if(list1->val<list2->val){
            tail->next=list1;
            list1=list1->next;
        }else{
            tail->next=list2;
            list2=list2->next;
        }
        tail=tail->next;
    }
    tail->next=(list1!=NULL)?list1:list2;
    return head.next;
 }
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if(listsSize==0) return NULL; 
    if(listsSize==1)return lists[0];
      struct ListNode*res=merge(lists[0],lists[1]);
      for(int i=2;i<listsSize;i++){
      res=merge(res,lists[i]);
      }
      return res;
}

