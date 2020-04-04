#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;


list *sort(list *start) {
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL; // partition input list into left and right sublist

    left = sort(left); // list of single element is already sorted
    right = sort(right); // sorted right sublist

    // insertion until the two sublists both been traversed
    // merge is always infront of the insertion position
    for (list *merge = NULL; left || right;) {
        // right list hasn't reach the end or
        // left node has found its position for inserting
        if (right == NULL || (left && left->data < right->data)) {
            if (!merge) {
                // start points to the node with min value
                // merge starts from min value
                start = merge = left; // LL1
            }
            else {
                // insert left node between merge and right point to
                merge->next = left; // LL2
                merge = merge->next; 
            }
            left = left->next; // LL3
        }
        else {
            if (!merge) {
                start = merge = right; // LL4
            } else {
                // shift until right == NULL or
                // inset merge(=left) in front of right when min is in left sublist
                // (LL1->LL5-> shift until right == NULL)
                merge->next = right; // LL5
                merge = merge->next;
            }
            right = right->next; // LL6
        }
    }
    return start;
}

int main()
{
	list *node1 = malloc(sizeof(*node1));
	list *node2 = malloc(sizeof(*node2));
	list *node3 = malloc(sizeof(*node3));
	list *node4 = malloc(sizeof(*node4));
	
	node1->data = 7;
	node1->next = node2;
	node2->data = 2;
	node2->next = node3;
	node3->data = 3;
	node3->next = node4;
	node4->data = 5;
	node4->next = NULL;
	
	list *head = sort(node1);
	printf("After sorting:\n");
	
	while(head)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	
	return 0;
}

// another one:
struct ListNode* mergeList(struct ListNode* list1,struct ListNode* list2){
    struct ListNode* head=NULL;
    if(list1->val<list2->val){
        head=list1;
        list1=list1->next;
    }else{
        head=list2;
        list2=list2->next;
    }
    struct ListNode* q=head;
    while(list1!=NULL&&list2!=NULL){
        if(list1->val<list2->val){
            q->next=list1;
            list1=list1->next;
        }else{
            q->next=list2;
            list2=list2->next;
        }
        q=q->next;
    }
    struct ListNode* p=NULL;
    if(list1==NULL){
        p=list2;
    }else{
        p=list1;
    }
    q->next=p;
    return head;
}
struct ListNode* sortList(struct ListNode* head){
    if(head==NULL||head->next==NULL){
        return head;
    }
    if(head->next->next==NULL){
        if(head->val>head->next->val){
            struct ListNode* tmp=head->next;
            tmp->next=head;
            tmp->next->next=NULL;
            return tmp;
        }
    }
    struct ListNode* fast=head;
    struct ListNode* slow=head; 
    while(fast->next!=NULL&&fast->next->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }
    fast=slow->next;
    slow->next=NULL;
    return mergeList(sortList(head),sortList(fast));
}
