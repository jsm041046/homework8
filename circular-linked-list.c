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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
	printf("[----- 2021041046 전설민 -----]\n"); //학번 이름 출력
	do{
		printf("----------------------------------------------------------------\n"); //안내
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력

		switch(command) { //명령어에 따른 분기
		case 'z': case 'Z':
			initialize(&headnode); //연결리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //연결리스트 중간에 원소 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //연결리스트에 지정된 원소 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //연결리스트 마지막에 원소 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); //연결리스트 마지막 원소 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //연결리스트 첫번째 원소 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //연결리스트 첫번째 원소 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //연결리스트 순서 역순으로 변경
			break;
		case 'q': case 'Q':
			freeList(headnode); //연결리스트 할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //Q를 입력받았을 경우 반복 종료

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* temp;
	while (p != NULL && p != h) { //p가 끝이 나올때 까지 반복
		temp = p->rlink; //p가 free가 되면 p의 우측링크도 사라지므로 임시로 주소를 temp에 저장해 놓는다.
		free(p); //p할당 해제
		p = temp; //p는 저장된 다음 주소로 이동
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode *node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    //노드 메모리 할당 및 원소 대입

    node->rlink = h;
    node->llink = h->llink;
	h->llink->rlink = node;
    h->llink = node;
    //원형 연결리스트이므로 마지막 노드의 우측은 첫번째 노드, 좌측은 마지막 노드를 가르키고, 마지막 노드의 우측 링크와 h의 좌측링크는 이번에 추가된 마지막 원소를 가르킨다

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h->llink == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//h가 가르키는 노드가 없을 경우 예외처리

	h->llink = h->llink->llink;
	free(h->llink->rlink);
	h->llink->rlink = h;
	//마지막 노드를 가르키는 h의 좌측링크를 한칸 좌측으로 이동시키고, 마지막 원소가 될 노드의 우측링크를 할당 해제한 다음, 첫번째 원소로 옮긴다

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	//노드 메모리 할당 및 원소 대입

	node->rlink = h->rlink;
	node->rlink->llink = node;
	h->rlink = node;
	node->llink = h;
	//노드의 우측링크를 첫번재 원소로, 첫번째 원소의 좌측링크를 노드로, 첫번째 원소를 node로, node의 좌측링크를 헤드로 바꾼다
	

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if (h->rlink == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//h가 가르키는 노드가 없을 경우 예외처리

	h->rlink = h->rlink->rlink;
	free(h->rlink->llink);
	h->rlink->llink = h;
	//h가 가르키는 우측노드를 한칸 오른쪽으로 옮기고, 해당 노드의 왼쪽 노드를 삭제한 후, 왼쪽 노드를 h를 가르키게 함

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
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
	//p가 끝날때 까지 p의 좌우 링크를 교환하고, 다음 노드로 이동함

	temp = h->rlink;
	h->rlink = h->llink;
	h->llink = temp;
	//h의 좌우 링크 교환
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	//노드 메모리 할당 및 원소 대입

	listNode* p = h;
	while (p->rlink != h && key >= p->rlink->key) //p의 다음값이 없거나 node의 원소값보다 p의 다음 원소값이 클때 while을 빠져나감
	{
		//p를 우측으로 한칸 이동
		p = p->rlink;
	}

	p->rlink->llink = node;
	node->rlink = p->rlink;
	p->rlink = node;
	node->llink = p;
	//p의 다음 위치에 node 대입

	return 1;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* p = h->rlink;
	while (p != h && key != p->key) //p의 다음값이 없거나 제거할 원소값이 해당 노드의 값과 같을때 while을 빠져나감
	{
		//p를 우측으로 한칸 이동
		p = p->rlink;
	}

	if (p == h)
	{
		printf("list is not exist\n");
		return 0;
	}
	//해당 노드가 없을 경우

	p->llink->rlink = p->rlink;
	p->rlink->llink = p->llink;
	free(p);
	//해당 노드가 있을경우 해당 노드 삭제
	return 1;
}


