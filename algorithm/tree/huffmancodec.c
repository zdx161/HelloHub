#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;

typedef char ** HuffmanCode;

void Select(HuffmanTree ht, int size, int *index1, int *index2)
{
    if(ht == NULL || size <= 1)
        return;

    int i;
    int w[2] = {0};
    *index1 = 0;
    *index2 = 0;
    for(i = 1; i <= size; i ++){
       if (ht[i].parent == 0) {
            if (w[0] == 0) {
                w[0] = ht[i].weight;
                *index1 = i;
            } else if (w[1] == 0) {
                w[1] = ht[i].weight;
                *index2 = i;
            } else if (w[0] > ht[i].weight && w[0] >= w[1]) {
                w[0] = ht[i].weight;
                *index1 = i;
            } else if (w[1] > ht[i].weight) {
                w[1] = ht[i].weight;
                *index2 = i;
            }
       }
    }
}

void HuffmanCoding(HuffmanTree * HT, HuffmanCode * HC, int *w, int n)
{
   if(n <= 1)
       return;

   int m, i;
   int s1, s2;
   char *cd;
   int start, c, f;
   HTNode *p;
   HuffmanTree ht;

   m = 2 * n - 1;
   ht = (HuffmanTree)calloc((m + 1), sizeof(HTNode));
   for ( i = 1, p = ht; i <= n; ++i, ++w) {
       //*p = {*w, 0, 0, 0};
       ++p;
       p->weight = *w;
   }
   for (; i <= m; ++i, ++p) {
       //*p = {0, 0, 0, 0};
   }
   for (i = n + 1; i <= m; ++i) {
        Select(ht, i - 1, &s1, &s2);
        ht[s1].parent = i;
        ht[s2].parent = i;
        if (s1 > s2) {
            ht[i].lchild = s2;
            ht[i].rchild = s1;
        } else {
            ht[i].lchild = s1;
            ht[i].rchild = s2;
        }

        ht[i].weight = ht[s1].weight + ht[s2].weight;
   }

   //HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
   cd = (char *) malloc(n * sizeof(char));
   cd[n - 1] = '\0';

   for (i = 1; i <= n; ++i) {
       start = n - 1;
       for (c = i, f = ht[i].parent; f != 0; c = f, f = ht[f].parent) {
           if(ht[f].lchild == c)
               cd[--start] = '0';
           else
               cd[--start] = '1';
       }

       //HC[i] = (char *)malloc((n - start) * sizeof(char));
       printf("%s\n", &cd[start]);
       //strcpy(HC[i], &cd[start]);
   }

   //*HC = ht;
   free(cd);
}

int main()
{
    int w[] = {5, 29, 7, 8, 14, 23, 3, 11};
    int n = 8;
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanCoding(&HT, &HC, w, n);
    int i;
#if 0
    for( i = 1; i <=n; i++){
        printf("%s\n", HC[i]);
        free(HC[i]);
    }
#endif
    //free(HT);

    return 0;
}
