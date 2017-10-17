#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct STree{
    char ele;
    struct STree ** children;
    int n_children;
    int* tale;
    int* tale_index;
    int n_tale;
};
struct rank{
    int* tale;
    int* occurences;
    int n;
};
struct STree* createSTree(struct STree* root,char input[],int tale){
    struct STree* masterroot=root;
    int i,j,k;
    int n=strlen(input);
    for(i=1;i<=n;i++){
        //Get the suffix
        char suffix[i+1];
        suffix[i]='\0';
        strncpy(suffix,input+n-i,i);
        //Insert this suffix into STree
        for(j=0;j<strlen(suffix);j++){
            if(root->children==NULL){
                if(suffix[j]=='$'){
                    root->n_children++;
                    root->children=(struct STree**)realloc(root->children,sizeof(struct STree*)*root->n_children);
                    struct STree* dol=malloc(sizeof(struct STree));
                    dol->ele='$';
                    dol->children=NULL;
                    dol->n_tale=0;
                    dol->n_children=0;
                    root->children[root->n_children-1]=dol;
                }
                else{
                    //Create a $ node
                    root->n_children++;
                    root->children=(struct STree**)realloc(root->children,sizeof(struct STree*)*root->n_children);
                    struct STree* dol=malloc(sizeof(struct STree));
                    dol->ele='$';
                    dol->children=NULL;
                    dol->n_tale=0;
                    dol->n_children=0;
                    root->children[root->n_children-1]=dol;
                    //Create a node suffix[j]
                    root->n_children++;
                    root->children=(struct STree**)realloc(root->children,sizeof(struct STree*)*root->n_children);
                    struct STree* new=malloc(sizeof(struct STree));
                    new->ele=suffix[j];
                    new->children=NULL;
                    new->n_tale=1;
                    new->n_children=0;
                    root->children[root->n_children-1]=new;
                    new->tale=malloc(sizeof(int));
                    new->tale[new->n_tale-1]=tale;
                    new->tale_index=malloc(sizeof(int));
                    new->tale_index[new->n_tale-1]=n-i+j;
                    root=new;
                }
            }
            else{
                int present=0;
                for(k=1;k<root->n_children;k++){
                    //Check for character in children
                    if(root->children[k]->ele==suffix[j]){
                        present=1;
                        if(suffix[j]!='$'){ 
                            root=root->children[k];
                            root->n_tale++;
                            root->tale=realloc(root->tale,sizeof(int)*root->n_tale);
                            root->tale_index=realloc(root->tale_index,sizeof(int)*root->n_tale);
                            root->tale_index[root->n_tale-1]=n-i+j;
                            root->tale[root->n_tale-1]=tale;
                            break;
                        }
                    }
                }
                if(present==0){
                    root->n_children++;
                    root->children=(struct STree**)realloc(root->children,sizeof(struct STree*)*root->n_children);
                    struct STree* new=malloc(sizeof(struct STree));
                    new->ele=suffix[j];
                    new->children=NULL;
                    new->n_tale=1;
                    new->n_children=0;
                    root->children[root->n_children-1]=new;
                    new->tale=malloc(sizeof(int));
                    new->tale[new->n_tale-1]=tale;
                    new->tale_index=malloc(sizeof(int));
                    new->tale_index[new->n_tale-1]=n-i+j;
                    root=new;
                }
            }
        }
        root=masterroot;
    }
    root=masterroot;
    return root;
}
void findContext(char string[],int index){
    int i,j;
    int length=strlen(string);
    char buffer[length];
    i=index;
    while(i-1>=0 && !(string[i-1]==' ' && string[i-2]==' ')){
        i--;
    }
    for (j=i;j<length;j++){
        if(string[j]==' ' && string[j+1]==' '){
            break;
        }
        printf("%c",string[j]);
    }
    printf("\n");
}
void findSentence(struct STree* root,int tree_tale,int tree_tale_index){
    FILE* fptr;
    int tale=0,ptr=0;
    int title_flag=0;
    char ch;
    char input[1000];
    fptr=fopen("AesopTales.txt","r");
    if (fptr == NULL){
        printf("Cannot open file. Terminating program.\n");
        exit(0);
    }
    while(1){
        ch=fgetc(fptr);
        if(ch==EOF) break;
        if(ch=='\n'){
            ch=fgetc(fptr);
            if(ch==EOF) break;
            if(ch=='\n'){
                ch=fgetc(fptr);
                if(ch==EOF){
                    tale++;
                    input[ptr]='\0';
                    if(tale==tree_tale){
                        //Do Q1 stuff
                        findContext(input,tree_tale_index);
                        return;
                    }
                    break;
                }
                if(ch=='\n'){
                    tale++;
                    input[ptr]='\0';
                    if(tale==tree_tale){
                        //Do Q1 stuff
                        findContext(input,tree_tale_index);
                        return;
                    }
                    ptr=0;
                    ch=fgetc(fptr);
                    title_flag=0;
                    input[ptr]=ch;
                    ptr++;
                }
                else if(ch==' '){
                    tale++;
                    input[ptr]='\0';
                    if(tale==tree_tale){
                        //Do Q1 stuff
                        findContext(input,tree_tale_index);
                        return;
                    }
                    ptr=0;
                    ch=fgetc(fptr);
                    ch=fgetc(fptr);
                    title_flag=0;
                    input[ptr]=ch;
                    ptr++;
                }
                else{
                    if(title_flag==0){
                        if(tale==tree_tale-1){
                            input[ptr]='\0';
                            printf("%s\n",input);
                        }
                        ch=fgetc(fptr);
                        ptr=0;
                        input[ptr]=ch;
                        ptr++;
                        title_flag=1;
                    }
                    else{
                        input[ptr]=' ';
                        ptr++;
                        input[ptr]=ch;
                        ptr++;
                    }
                }
            }
            else if(ch==' '){
                ch=fgetc(fptr);
                if(ch==EOF) break;
                if(ch=='\n'){
                    ch=fgetc(fptr);
                    if(ch==EOF){
                        tale++;
                        input[ptr]='\0';
                        if(tale==tree_tale){
                            //Do Q1 stuff
                            findContext(input,tree_tale_index);
                            return;
                        }
                        break;
                    }
                    if(ch=='\n'){
                        tale++;
                        input[ptr]='\0';
                        if(tale==tree_tale){
                            //Do Q1 stuff
                            findContext(input,tree_tale_index);
                            return;
                        }
                        ptr=0;
                        title_flag=0;
                        ch=fgetc(fptr);
                        input[ptr]=ch;
                        ptr++;
                    }
                    else{
                        if(title_flag==0){
                            if(tale==tree_tale-1){
                                input[ptr]='\0';
                                printf("%s\n",input);
                            }
                            ptr=0;
                            input[ptr]=ch;
                            ptr++;
                            title_flag=1;
                        }
                        else{
                            input[ptr]=' ';
                            ptr++;
                            input[ptr]=ch;
                            ptr++;
                        }
                    }
                }
            }
            else{
                input[ptr]=' ';
                ptr++;
                input[ptr]=ch;
                ptr++;
            }
        }
        else{
            input[ptr]=ch;
            ptr++;
        }
    }
}
void traverse_q1(struct STree* root,char query[],int query_char){
    int i;
    if(query[query_char]=='\0'){
        for (i=0;i<root->n_tale;i++){
            findSentence(root,root->tale[i],root->tale_index[i]);
        }
    }
    else{
        int flag=0;
        for (i=1;i<root->n_children;i++){
            if(root->children[i]->ele==query[query_char]){
                root=root->children[i];
                query_char=query_char+1;
                flag=1;
                break;
            }
        }
        if(flag){
            //Continue traversal
            traverse_q1(root,query,query_char);
        }
        else{
            //Traversal has fallen off the STree
            printf("No results found\n");
        }
    }
}
void traverse_q2(struct STree* root,char query[],int query_char,short int atleast_1){
    int i;
    if(query[query_char]=='\0'){
        int* buff=calloc(500,sizeof(int));
        for (i=0;i<root->n_tale;i++){
            if(buff[root->tale[i]]==0){
                findSentence(root,root->tale[i],root->tale_index[i]);
                buff[root->tale[i]]=1;
            }
        }
        free(buff);
    }
    else{
        int flag=0;
        for (i=1;i<root->n_children;i++){
            if(root->children[i]->ele==query[query_char]){
                root=root->children[i];
                query_char=query_char+1;
                atleast_1=1;
                flag=1;
                break;
            }
        }
        if(flag){
            //Continue traversal
            traverse_q2(root,query,query_char,atleast_1);
        }
        else{
            //Traversal has fallen off the STree
            if(atleast_1){
                int* buff=calloc(500,sizeof(int));
                for (i=0;i<root->n_tale;i++){
                    if(buff[root->tale[i]]==0){
                        findSentence(root,root->tale[i],root->tale_index[i]);
                        buff[root->tale[i]]=1;
                    }
                }
                free(buff);
            }
            else{
                printf("Result not found\n");
            }
        }
    }
}
struct STree* traverse_q3(struct STree* root,char query[],int query_char){
    int i;
    if(query[query_char]=='\0'){
        return root;
    }
    else{
        int flag=0;
        for (i=1;i<root->n_children;i++){
            if(root->children[i]->ele==query[query_char]){
                root=root->children[i];
                query_char=query_char+1;
                flag=1;
                break;
            }
        }
        if(flag){
            //Continue traversal
            return traverse_q3(root,query,query_char);
        }
        //Traversal has fallen off the STree
        return NULL;
    }
}
short int in_tales(int ele,struct rank var){
    int i;
    int present=0;
    for (i=0;i<var.n;i++){
        if(ele==var.tale[i]){
            present=1;
            break;
        }
    }
    return present;
}
struct rank assign_rank(int tales[],struct rank var,int n){
    int n_tales=n;
    int i;
    int index=0,j;
    for (i=0;i<n_tales;i++){
        if(!in_tales(tales[i],var)){
            if(var.n==0){
                var.tale=(int*)malloc(sizeof(int)*(var.n+1));
                var.occurences=(int*)malloc(sizeof(int)*(var.n+1));
            }
            else{
                var.tale=(int*)realloc(var.tale,sizeof(int)*(var.n+1));
                var.occurences=(int*)realloc(var.occurences,sizeof(int)*(var.n+1));
            }
            var.tale[var.n]=tales[i];
            var.occurences[var.n]=1;
            var.n++;
        }
        else{
            for(j=0;j<var.n;j++){
                if(var.tale[j]==tales[i]){
                    index=j;
                    break;
                }
            }
            var.occurences[index]++;
        }
    }
    return var;
}
void swap(int* a, int* b){
    int t=*a;
    *a=*b;
    *b=t;
}
int partition(int tale[],int occurences[], int low, int high){
    int pivot=occurences[high];
    int i=low-1;
    int j;
    for(j=low;j<=high-1;j++){
        if(occurences[j]<=pivot){
            i++;
            swap(&tale[i],&tale[j]);
            swap(&occurences[i],&occurences[j]);
        }
    }
    swap(&tale[i+1],&tale[high]);
    swap(&occurences[i+1],&occurences[high]);
    return (i+1);
}
void quickSort(int tale[],int occurences[], int low, int high){
    if (low<high){
        int pi=partition(tale,occurences,low,high);
        quickSort(tale,occurences,low,pi-1);
        quickSort(tale,occurences,pi+1,high);
    }
}
void traverse_q3_wrapper(struct STree* root,char query[]){
    struct STree* main=root;
    short int mode_status=1;
    //Mode 1
    if(mode_status==1){
        main=traverse_q3(main,query,0);
        if(main==NULL){
            mode_status=2;
        }
        else{
            int result[main->n_tale];
            int i;
            for(i=0;i<main->n_tale;i++){
                result[i]=main->tale[i];
            }
            int n_result=sizeof(result)/sizeof(result[0]);
            struct rank var;
            var.n=0;
            var=assign_rank(result,var,n_result);
            //Sort by rank
            quickSort(var.tale,var.occurences,0,var.n-1);
            //Print by rank
            printf("Tale number of most relevant tales\n");
            for(i=var.n-1;i>=0;i--){
                printf("Tale %d with occurences %d\n",var.tale[i],var.occurences[i]);
            }
        }
    }
    //Mode 2
    if(mode_status==2){
        struct rank var;
        var.n=0;
        char* word = strtok(query," ");
        int i;
        main=root;
        while (word != NULL){
            main=traverse_q3(main,word,0);
            int result[main->n_tale];
            result[0]=-1;
            for (i=0;i<main->n_tale;i++){
                result[i]=main->tale[i];
            }
            if(result[0]!=-1){
                int n_result=sizeof(result)/sizeof(result[0]);
                var=assign_rank(result,var,n_result);
            }
            word = strtok(NULL, " ");
            main=root;
        }
        //Sort by rank
        quickSort(var.tale,var.occurences,0,var.n-1);
        //Print by rank
        printf("Tale number of most relevant tales\n");
        for(i=var.n-1;i>=0;i--){
            printf("Tale %d with occurences %d\n",var.tale[i],var.occurences[i]);
        }
    }
}
int main(void){
    char input[1000];
    char query[1000];
    int tale=0,ptr=0;
    int title_flag=0,i;
    char ch;
    struct STree* root=malloc(sizeof(struct STree));
    root->children=NULL;
    root->tale=NULL;
    root->tale_index=NULL;
    root->ele='#';
    root->n_children=0;
    root->n_tale=0;
    FILE* fptr;
    fptr=fopen("AesopTales.txt","r");
    if (fptr == NULL){
        printf("Cannot open file. Terminating program.\n");
        exit(0);
    }
    while(1){
        ch=fgetc(fptr);
        if(ch==EOF) break;
        if(ch=='\n'){
            ch=fgetc(fptr);
            if(ch==EOF) break;
            if(ch=='\n'){
                ch=fgetc(fptr);
                if(ch==EOF){
                    tale++;
                    input[ptr]='$';
                    ptr++;
                    input[ptr]='\0';
                    root=createSTree(root,input,tale);
                    break;
                }
                if(ch=='\n'){
                    tale++;
                    input[ptr]='$';
                    ptr++;
                    input[ptr]='\0';
                    root=createSTree(root,input,tale);
                    ptr=0;
                    ch=fgetc(fptr);
                    title_flag=0;
                    input[ptr]=ch;
                    ptr++;
                }
                else if(ch==' '){
                    tale++;
                    input[ptr]='$';
                    ptr++;
                    input[ptr]='\0';
                    root=createSTree(root,input,tale); 
                    ptr=0;
                    ch=fgetc(fptr);
                    ch=fgetc(fptr);
                    title_flag=0;
                    input[ptr]=ch;
                    ptr++;
                }
                else{
                    if(title_flag==0){
                        ch=fgetc(fptr);
                        ptr=0;
                        input[ptr]=ch;
                        ptr++;
                        title_flag=1;
                    }
                    else{
                        input[ptr]=' ';
                        ptr++;
                        input[ptr]=ch;
                        ptr++;
                    }
                }
            }
            else if(ch==' '){
                ch=fgetc(fptr);
                if(ch==EOF) break;
                if(ch=='\n'){
                    ch=fgetc(fptr);
                    if(ch==EOF){
                        tale++;
                        input[ptr]='$';
                        ptr++;
                        input[ptr]='\0';
                        root=createSTree(root,input,tale);
                        break;
                    }
                    if(ch=='\n'){
                        tale++;
                        input[ptr]='$';
                        ptr++;
                        input[ptr]='\0';
                        root=createSTree(root,input,tale);
                        ptr=0;
                        title_flag=0;
                        ch=fgetc(fptr);
                        input[ptr]=ch;
                        ptr++;
                    }
                    else{
                        if(title_flag==0){
                            ptr=0;
                            input[ptr]=ch;
                            ptr++;
                            title_flag=1;
                        }
                        else{
                            input[ptr]=' ';
                            ptr++;
                            input[ptr]=ch;
                            ptr++;
                        }
                    }
                }
            }
            else{
                input[ptr]=' ';
                ptr++;
                input[ptr]=ch;
                ptr++;
            }
        }
        else{
            input[ptr]=ch;
            ptr++;
        }
    }
    //Problem solutions
    printf("AVOID pressing ENTER if you want to go to a new line for more visibility. Just continue typing the string instead.\n");
    printf("The algorithm is CASE SENSITIVE\n");
    printf("Please enter the query string for Q1 : ");
    gets(query);
    traverse_q1(root,query,0);
    printf("Please enter the query string for Q2 : ");
    gets(query);
    traverse_q2(root,query,0,0);
    printf("Please enter the query string for Q3 : ");
    gets(query);
    printf("Relevance Definition\n");
    printf("1. If the query EXACTLY matches a substring in a document, it gets the high relevance.\n");
    printf("2. More the number of query matches, higher is the relevance\n");
    printf("3. If query doesn't match, individual words in the query are checked.\n");
    printf("4. More number of matched words in a document, higher the relevance\n");
    printf("5. Partial word matches get zero relevance\n");
    printf("Please enter the sequence of words with space ' ' as delimiter and without any leading and trailing whitespace : ");
    gets(query);
    traverse_q3_wrapper(root,query);
    free(root);
    return 0;
}