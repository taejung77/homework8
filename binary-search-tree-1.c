/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
    printf("[----- [Lee Tae Jeong] [2023041062] -----]");
	return 1;
}

int initializeBST(Node** h) {
    // 트리를 초기화하는 함수
    // 만약 트리가 비어있지 않다면 모든 노드를 해제
    if(*h != NULL)
        freeBST(*h);

    // 헤드 노드를 생성하고 초기화
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL;    // 루트 노드 초기화
    (*h)->right = *h;     // 헤드 노드의 오른쪽 포인터는 자기 자신을 가리킴
    (*h)->key = -9999;    // 헤드 노드의 키 값을 특수 값으로 설정
    return 1;
}

void inorderTraversal(Node* ptr) {
    // 중위 순회 함수 (왼쪽-루트-오른쪽 순서)
    if(ptr) {
        inorderTraversal(ptr->left);
        printf("[%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr) {
    // 전위 순회 함수 (루트-왼쪽-오른쪽 순서)
    if(ptr) {
        printf("[%d] ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr) {
    // 후위 순회 함수 (왼쪽-오른쪽-루트 순서)
    if(ptr) {
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("[%d] ", ptr->key);
    }
}

int insert(Node* head, int key) {
    // 새로운 노드를 삽입하는 함수
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    // 트리가 비었다면 새로운 노드를 루트로 설정
    if(head->left == NULL) {
        head->left = newNode; // 루트 노드 설정
        return 1;
    }

    // 트리를 탐색하여 새로운 노드의 위치를 찾기
    Node* ptr = head->left; // 루트 노드부터 시작
    Node* parent = NULL;

    while(ptr != NULL) {
        if(ptr->key == key) {
            // 중복된 키가 존재하면 삽입하지 않고 종료
            printf("중복된 키가 있습니다.\n");
            return 0;
        }

        parent = ptr;

        // 새로운 키가 현재 노드의 키보다 작으면 왼쪽으로 이동
        if(ptr->key > key) {
            ptr = ptr->left; // 왼쪽 자식 노드로 이동
        }
        // 새로운 키가 현재 노드의 키보다 크면 오른쪽으로 이동
        else {
            ptr = ptr->right; // 오른쪽 자식 노드로 이동
        }
    }

    // 부모 노드의 왼쪽 또는 오른쪽에 새로운 노드를 연결
    if(parent->key > key) {
        parent->left = newNode; // 왼쪽 자식 노드로 연결
    }
    else {
        parent->right = newNode; // 오른쪽 자식 노드로 연결
    }

    return 1;
}

int deleteLeafNode(Node* head, int key) {
    // 리프 노드를 삭제하는 함수
    Node* parent = head; // 부모 노드
    Node* ptr = head->left; // 루트 노드부터 시작

    // 삭제할 노드를 찾기
    while(ptr != NULL && ptr->key != key) {
        parent = ptr; // 부모 노드를 현재 노드로 설정

        if(ptr->key > key) {
            ptr = ptr->left; // 왼쪽 자식 노드로 이동
        }
        else {
            ptr = ptr->right; // 오른쪽 자식 노드로 이동
        }
    }

    // 삭제할 노드가 없으면 메시지를 출력하고 종료
    if(ptr == NULL) {
        printf("삭제할 노드가 없습니다.\n");
        return 0;
    }

    // 삭제할 노드가 리프 노드인지 확인
    if(ptr->left == NULL && ptr->right == NULL) {
        // 부모 노드의 왼쪽 또는 오른쪽 포인터를 NULL로 설정
        if(parent->left == ptr) { // 왼쪽 자식 노드인 경우
            parent->left = NULL; // 부모 노드의 왼쪽 포인터를 NULL로 설정
        }
        else {
            parent->right = NULL; // 부모 노드의 오른쪽 포인터를 NULL로 설정
        }

        // 노드 메모리를 해제합니다.
        free(ptr);
    }

    return 1;
}

Node* searchRecursive(Node* ptr, int key) {
    // 재귀적으로 노드를 찾는 함수
    if(ptr == NULL) {
        return NULL;
    }

    if(ptr->key == key) {
        return ptr;
    }
    else if(ptr->key > key) {
        return searchRecursive(ptr->left, key); // 왼쪽 자식 노드로 이동
    }
    else {
        return searchRecursive(ptr->right, key); // 오른쪽 자식 노드로 이동
    }
}

Node* searchIterative(Node* head, int key) {
    // 반복적으로 노드를 찾는 함수
    Node* ptr = head->left; // 루트 노드부터 시작

    while(ptr != NULL) {
        if(ptr->key == key) {
            return ptr;
        }
        else if(ptr->key > key) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    return NULL;
}

int freeBST(Node* head) {
    // 트리에 할당된 메모리를 해제하는 함수
    if(head->left != NULL) {
        freeBST(head->left);
    }

    if(head->right != head) {
        freeBST(head->right);
    }

    free(head);

    return 1;
}






