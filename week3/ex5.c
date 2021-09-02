#include <stdio.h>

struct node{
	int data;
	struct node* next;
	struct node* prev;
};

void print_list(struct node *head) {
	printf("[");
	while (head != NULL){
		printf("%d%c",head->data,(head->next)?'-':']');
		head = head->next;
	}
}

void connect_nodes(struct node *prevnode, struct node *newnode){
	if(prevnode == NULL || newnode == NULL) return;
	newnode->next  = prevnode->next;
	newnode->prev  = prevnode;
	prevnode->next = newnode;
	if(newnode->next == NULL) return;
	newnode->next->prev = newnode;
}

char is_belong(struct node *head, struct node *N){
	while (head != NULL && head != N)
		head = head->next;
	return head != NULL;
}

void insert_node(struct node *head, struct node *newnode, struct node *prevnode){
	if(is_belong(head, prevnode))
		connect_nodes(prevnode, newnode);
}

void delete_node(struct node *head, struct node *delnode){
	while(head != NULL && head->next != delnode)
		head = head->next;
	if(head == NULL)return;
	head->next = delnode->next;
	if(delnode->next == NULL) return;
	head->next->prev = head;
}

int main(){
	struct node head = {0, NULL, NULL}, n1 = {1, NULL, NULL}, n2 = {2, NULL, NULL}, n3 = {3, NULL, NULL};
	printf("Initial list:\n  ");
	print_list(&head);

	connect_nodes(&head, &n2); 
	printf("\nList after connecting head and 2:\n  ");
	print_list(&head);
	insert_node(&head, &n3, &head);
	printf("\nList after inserting 3 after head:\n  ");
	print_list(&head);

	insert_node(&head, &n1, &n2);
	printf("\nList after inserting 1 after 2:\n  ");
	print_list(&head);

	delete_node(&head, &n2);
	printf("\nList after deleting 2:\n  ");
	print_list(&head);

	delete_node(&head, &n1);
	insert_node(&head, &n1, &head);
	printf("\nList after deleting 1 and inseting it after head:\n  ");
	print_list(&head);

	return 0;
}
