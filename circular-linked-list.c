/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- 2021041046 ������ -----]\n"); //�й� �̸� ���
	do{
		printf("----------------------------------------------------------------\n"); //�ȳ�
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ� �Է�

		switch(command) { //��ɾ ���� �б�
		case 'z': case 'Z':
			initialize(&headnode); //���Ḯ��Ʈ �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); //���Ḯ��Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //���Ḯ��Ʈ �߰��� ���� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //���Ḯ��Ʈ�� ������ ���� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //���Ḯ��Ʈ �������� ���� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); //���Ḯ��Ʈ ������ ���� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //���Ḯ��Ʈ ù��° ���� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); //���Ḯ��Ʈ ù��° ���� ����
			break;
		case 'r': case 'R':
			invertList(headnode); //���Ḯ��Ʈ ���� �������� ����
			break;
		case 'q': case 'Q':
			freeList(headnode); //���Ḯ��Ʈ �Ҵ� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //Q�� �Է¹޾��� ��� �ݺ� ����

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* temp;
	while (p != NULL && p != h) { //p�� ���� ���ö� ���� �ݺ�
		temp = p->rlink; //p�� free�� �Ǹ� p�� ������ũ�� ������Ƿ� �ӽ÷� �ּҸ� temp�� ������ ���´�.
		free(p); //p�Ҵ� ����
		p = temp; //p�� ����� ���� �ּҷ� �̵�
	}
	free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
    listNode *node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    //��� �޸� �Ҵ� �� ���� ����

    node->rlink = h;
    node->llink = h->llink;
	h->llink->rlink = node;
    h->llink = node;
    //���� ���Ḯ��Ʈ�̹Ƿ� ������ ����� ������ ù��° ���, ������ ������ ��带 ����Ű��, ������ ����� ���� ��ũ�� h�� ������ũ�� �̹��� �߰��� ������ ���Ҹ� ����Ų��

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	if (h->llink == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//h�� ����Ű�� ��尡 ���� ��� ����ó��

	h->llink = h->llink->llink;
	free(h->llink->rlink);
	h->llink->rlink = h;
	//������ ��带 ����Ű�� h�� ������ũ�� ��ĭ �������� �̵���Ű��, ������ ���Ұ� �� ����� ������ũ�� �Ҵ� ������ ����, ù��° ���ҷ� �ű��

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	//��� �޸� �Ҵ� �� ���� ����

	node->rlink = h->rlink;
	node->rlink->llink = node;
	h->rlink = node;
	node->llink = h;
	//����� ������ũ�� ù���� ���ҷ�, ù��° ������ ������ũ�� ����, ù��° ���Ҹ� node��, node�� ������ũ�� ���� �ٲ۴�
	

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	if (h->rlink == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//h�� ����Ű�� ��尡 ���� ��� ����ó��

	h->rlink = h->rlink->rlink;
	free(h->rlink->llink);
	h->rlink->llink = h;
	//h�� ����Ű�� ������带 ��ĭ ���������� �ű��, �ش� ����� ���� ��带 ������ ��, ���� ��带 h�� ����Ű�� ��

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode* p = h->rlink;
	listNode* temp;

	while (p != h && p != NULL)
	{
		temp = p->rlink;
		p->rlink = p->llink;
		p->llink = temp;
		p = p->llink;
	}
	//p�� ������ ���� p�� �¿� ��ũ�� ��ȯ�ϰ�, ���� ���� �̵���

	temp = h->rlink;
	h->rlink = h->llink;
	h->llink = temp;
	//h�� �¿� ��ũ ��ȯ
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	//��� �޸� �Ҵ� �� ���� ����

	listNode* p = h;
	while (p->rlink != h && key >= p->rlink->key) //p�� �������� ���ų� node�� ���Ұ����� p�� ���� ���Ұ��� Ŭ�� while�� ��������
	{
		//p�� �������� ��ĭ �̵�
		p = p->rlink;
	}

	p->rlink->llink = node;
	node->rlink = p->rlink;
	p->rlink = node;
	node->llink = p;
	//p�� ���� ��ġ�� node ����

	return 1;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode* p = h->rlink;
	while (p != h && key != p->key) //p�� �������� ���ų� ������ ���Ұ��� �ش� ����� ���� ������ while�� ��������
	{
		//p�� �������� ��ĭ �̵�
		p = p->rlink;
	}

	if (p == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//�ش� ��尡 ���� ���

	p->llink->rlink = p->rlink;
	p->rlink->llink = p->llink;
	free(p);
	//�ش� ��尡 ������� �ش� ��� ����
	return 1;
}


