#include "main.h"


int main(int argc,char** argv){
    //default option
    data_cnt=(int)1e4;
    query_cnt=(int)1e3;

    //read the command line input
    for(int i=1;i<argc;i++){
        //printf("%s\n",argv[i]);
        if(!strcmp(argv[i],"-d")){
            if(!strcmp(argv[i+1],"1e4"))
                data_cnt=(int)1e4;
            if(!strcmp(argv[i+1],"1e5"))
                data_cnt=(int)1e5;
            if(!strcmp(argv[i+1],"1e6"))
                data_cnt=(int)1e6;
            i++;continue;
        }
        else if(!strcmp(argv[i],"-q")){
            if(!strcmp(argv[i+1],"1e3"))
                query_cnt=(int)1e3;
            if(!strcmp(argv[i+1],"1e4"))
                query_cnt=(int)1e4;
            if(!strcmp(argv[i+1],"1e5"))
                query_cnt=(int)1e5;
            i++;continue;
        }
        else if(!strcmp(argv[i],"-ll")){
            opt[ll]=TRUE;
            opt_cnt++;continue;
        }
        else if(!strcmp(argv[i],"-arr")){
            opt[arr]=TRUE;
            opt_cnt++;continue;
        }
        else if(!strcmp(argv[i],"-bs")){
            opt[bs]=TRUE;
            opt_cnt++;continue;
        }
        else if(!strcmp(argv[i],"-bst")){
            opt[bst]=TRUE;
            opt_cnt++;continue;
        }
        else if(!strcmp(argv[i],"-hash")){
            opt[hash]=TRUE;
            opt_cnt++;continue;
        }
    }
    

    printf("datacnt  %d\n",data_cnt);
    printf("querycnt %d\n",query_cnt);
    printf("optcnt   %d\n",opt_cnt);

    create();

    struct  timeval start;
    struct  timeval end;
    unsigned long timediff;

    for(int i=0;i<5;i++){
        if(!opt[i])continue;

        printf("\n%s:\n",opt_name[i]);
        gettimeofday(&start, NULL);
            build_func[i]();
        gettimeofday(&end, NULL);
        timediff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("building time = %f sec\n",timediff/1000000.0);

        gettimeofday(&start, NULL);
            query_func[i]();
        gettimeofday(&end, NULL);
        timediff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("query time = %f sec\n",timediff/1000000.0);

        free_func(i);
    }

    //query_const的字串存的是來自data_const的指標 所以不用free
    for(int i=0;i<data_cnt;i++) free(data_const[i]);
    free(data_const);
    free(query_const);

    return 0;
}

void create(){
    FILE* fd=fopen("data.txt","w+t");
    FILE* fq=fopen("query.txt","w+t");

    data_const=(char**)malloc(sizeof(char*)*data_cnt);
    query_const=(char**)malloc(sizeof(char*)*query_cnt);

    char temp[7];
    int r,idx;
    for(int i=0;i<data_cnt;i++){
        //產生唯一測資
        while(1){
            for(int j=0;j<5;j++){
                r=rand()%52;
                if(r<26) temp[j]='a'+r;
                else temp[j]='A'+r%26;
            }
            temp[5] = '\0';
            //確認是否唯一
            idx = hash_func(33,temp)%(int)1e6;
            if(data_hash[idx]==0){
                data_hash[idx]=1;
                break;
                //沒有同樣的hash值->認定是唯一
            }
        }
        fprintf(fd,"%s\n",temp);
        data_const[i]=strdup(temp);
    }
    for(int i=0;i<query_cnt;i++){
        int r=rand()%data_cnt;
        query_const[i]=data_const[r];
        fprintf(fq,"%s\n",query_const[i]);
    }
    fclose(fq);
    fclose(fd);
    
    puts("create finish");
}

unsigned int hash_func(int k,char* str){
    char* ptr=str;
    unsigned int hv=0;
    while(*ptr){
        if(isalpha(*ptr))hv=hv*k+*ptr++;
    }
    return hv;
}

void arr_build(){
    data_arr=(char**)malloc(sizeof(char*)*data_cnt);
    for(int i=0;i<data_cnt;i++){
        data_arr[i]=data_const[i];
    }
}

void arr_query(){
    for(int i=0;i<query_cnt;i++){
        for(int j=0;j<data_cnt;j++){
            if(!strcmp(data_const[j],query_const[i])){
                break;
            }
        }
    }
}

int cmp(const void* a,const void* b){
    return strcmp(*(char**)a,*(char**)b);
}

void bs_build(){
    data_bs=(char**)malloc(sizeof(char*)*data_cnt);
    for(int i=0;i<data_cnt;i++){
        data_bs[i]=data_const[i];
    }
    qsort(data_bs,data_cnt,sizeof(char*),cmp);
}

void bs_query(){
    for(int i=0;i<query_cnt;i++){
        bs_find(0,data_cnt-1,query_const[i]);
    }
}

void bs_find(int left,int right,char *k){
    if(left>=right)return;

    int mid=(right+left)/2;

    if(strcmp(k,data_bs[mid])<0) bs_find(left,mid-1,k);
    else if(strcmp(k,data_bs[mid])>0) bs_find(mid+1,right,k);
    else return;
}

void ll_build(){
    Node* current;
    for(int i=0;i<data_cnt;i++){
        if(ll_head==NULL){
            ll_head=newnode(data_const[i]);
            current=ll_head;
        }
        else{
            current->next=newnode(data_const[i]);
            current=current->next;
        }
    }
}

Node* newnode(char* str){
    Node* new=(Node*)malloc(sizeof(Node));
    new->str=str;
    new->right=NULL;
    new->left=NULL;
    new->next=NULL;
    return new;
}

void ll_query(){
    for(int i=0;i<query_cnt;i++){
        Node* p=ll_head;

        while(p){
            if(!strcmp(p->str,query_const[i]))
                break;
            p=p->next;
        }
    }
}

void bst_build(){
    for(int i=0;i<data_cnt;i++){
        if(bst_head==NULL)
            bst_head=newnode(data_const[i]);
        else
            bst_findend(bst_head,data_const[i]);
    }
}

void bst_findend(Node* current,char* str){
    if(strcmp(str,current->str)<0){
        if(current->left==NULL)
            current->left=newnode(str);
        else
            bst_findend(current->left,str);
    }
    else if(strcmp(str,current->str)>0){
        if(current->right==NULL)
            current->right=newnode(str);
        else
            bst_findend(current->right,str);
    }
    else{
        //printf("find!!\n");
    }
    return;
}

void bst_query(){
    for(int i=0;i<query_cnt;i++){
        bst_findend(bst_head,query_const[i]);
    }
}

void hash_build(){
    hash_table=(Node**)calloc(data_cnt,sizeof(Node*));
    for(int i=0;i<data_cnt;i++){
        int idx=hash_func(65,data_const[i])%data_cnt;

        if(hash_table[idx]==NULL){
            hash_table[idx]=newnode(data_const[i]);
        }
        else{
            Node* p=hash_table[idx];
            while(p->next)p=p->next;
            p->next=newnode(data_const[i]);
        }
    }
}

void hash_query(){
    for(int i=0;i<query_cnt;i++){
        int idx=hash_func(65,query_const[i])%data_cnt;

        Node* p=hash_table[idx];
        while(p){
            if(!strcmp(p->str,query_const[i]))
                break;
            p=p->next;
        }
    }
}

void free_func(int i){
    switch(i){
        case ll:
            ll_free(ll_head);
            break;
        case arr:
            arr_free(data_arr);
            break;
        case bs:
            arr_free(data_bs);
            break;
        case bst:
            bst_free(bst_head);
            break;
        case hash:
            hash_free();
            break;
    }
    //puts("free finish");
}

void ll_free(Node* head){
    Node* current=head;
    Node* last;
    while(current){
        last=current;
        current=current->next;
        free(last);
    }
}

void arr_free(char** data){
    free(data);
}

void bst_free(Node* parent){
    if(parent==NULL)return;
    bst_free(parent->left);
    bst_free(parent->right);
    free(parent);
}

void hash_free(){
    for(int i=0;i<data_cnt;i++)
        ll_free(hash_table[i]);
    free(hash_table);
}