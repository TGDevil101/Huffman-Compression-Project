#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 256
#define MAX_CODE_LENGTH 256

typedef struct TreeNode
{
    unsigned char character;
    unsigned int  timesAppeared;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TreeNode;

typedef struct
{
    char codeString[MAX_CODE_LENGTH + 1];
    int  codeLength;
} HuffmanCode;

typedef struct
{
    TreeNode **items;
    int count;
    int maxSize;
} PriorityQueue;


TreeNode *createNode(unsigned char character, unsigned int timesAppeared)
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        printf("not enough memory\n");
        return NULL;
    }
    newNode->character = character;
    newNode->timesAppeared = timesAppeared;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}


void swapItems(PriorityQueue *queue, int indexA, int indexB)
{
    TreeNode *temporary = queue->items[indexA];
    queue->items[indexA] = queue->items[indexB];
    queue->items[indexB] = temporary;
}

void bubbleUp(PriorityQueue *queue, int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (queue->items[parentIndex]->timesAppeared > queue->items[index]->timesAppeared)
        {
            swapItems(queue, parentIndex, index);
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
}

void pushDown(PriorityQueue *queue, int index)
{
    while (1)
    {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < queue->count && queue->items[leftChild]->timesAppeared < queue->items[smallest]->timesAppeared)
        {
            smallest = leftChild;
        }
        if (rightChild < queue->count && queue->items[rightChild]->timesAppeared < queue->items[smallest]->timesAppeared)
        {
            smallest = rightChild;
        }
        if (smallest == index)
        {
            break;
        }
        swapItems(queue, index, smallest);
        index = smallest;
    }
}

PriorityQueue *createQueue(int maxSize)
{
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    queue->items = malloc(sizeof(TreeNode *) * maxSize);
    queue->count = 0;
    queue->maxSize = maxSize;
    return queue;
}

void deleteQueue(PriorityQueue *queue)
{
    free(queue->items);
    free(queue);
}

void addToQueue(PriorityQueue *queue, TreeNode *node)
{
    if (queue->count >= queue->maxSize)
    {
        return;
    }
    queue->items[queue->count] = node;
    queue->count++;
    bubbleUp(queue, queue->count - 1);
}

TreeNode *removeSmallest(PriorityQueue *queue)
{
    if (queue->count == 0)
    {
        return NULL;
    }
    TreeNode *smallest = queue->items[0];
    queue->items[0] = queue->items[queue->count - 1];
    queue->count--;
    if (queue->count > 0)
    {
        pushDown(queue, 0);
    }
    return smallest;
}


TreeNode *buildHuffmanTree(unsigned int frequency[])
{
    PriorityQueue *queue = createQueue(MAX_CHARACTERS);
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        if (frequency[i] == 0)
        {
            continue;
        }
        TreeNode *node = createNode((unsigned char)i, frequency[i]);
        addToQueue(queue, node);
    }
    if (queue->count == 0)
    {
        deleteQueue(queue);
        return NULL;
    }
    if (queue->count == 1)
    {
        TreeNode *onlyNode = removeSmallest(queue);
        TreeNode *root = createNode(0, onlyNode->timesAppeared);
        root->leftChild = onlyNode;
        deleteQueue(queue);
        return root;
    }
    while (queue->count > 1)
    {
        TreeNode *leftNode  = removeSmallest(queue);
        TreeNode *rightNode = removeSmallest(queue);
        TreeNode *parentNode = createNode(0, leftNode->timesAppeared + rightNode->timesAppeared);
        parentNode->leftChild  = leftNode;
        parentNode->rightChild = rightNode;
        addToQueue(queue, parentNode);
    }
    TreeNode *treeRoot = removeSmallest(queue);
    deleteQueue(queue);
    return treeRoot;
}
