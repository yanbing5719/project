```c
void amountInit(lock_t* account){

  

account->amount=0;

  

pthread_mutex_init(&account->mutex,NULL);

  

}

  

  

void Income(lock_t* account, int amount){

  

pthread_mutex_lock(&account->mutex);

  

account->amount+=amount;

  

pthread_mutex_unlock(&account->mutex);

  

}

  

  

void Expend(lock_t* account, int amount) {

  

pthread_mutex_lock(&account->mutex);

  

account->amount-=amount;

  

pthread_mutex_unlock(&account->mutex);

  

}
```


```c
  

void listInit(list_lock_t* list) {

  

list->head=NULL;

  

  

pthread_mutex_init(&list->mutex,NULL);

  

  

pthread_cond_init(&list->cond,NULL);

  

}

  

  

void producer(list_lock_t* list, DataType value) {

  

LNode *newnode=(LNode*)malloc(sizeof(LNode));

  

  

pthread_mutex_lock(&list->mutex);

  

  

newnode->value=value;

  

  

newnode->next=list->head;

  

  

list->head=newnode;

  

  

pthread_cond_signal(&list->cond);

  

  

pthread_mutex_unlock(&list->mutex);

  

  

}

  

  

void consumer(list_lock_t* list) {

  

pthread_mutex_lock(&list->mutex);

  

  

//没钱的时候进入休眠

  

  

while(list->head==NULL){

  

  

pthread_cond_wait(&list->cond,&list->mutex);

  

  

}

  

  

LNode*t=list->head;

  

  

list->head=list->head->next;

  

  

free(t);

  

  

pthread_mutex_unlock(&list->mutex);

  

  

}

  

  

int getListSize(list_lock_t* list) {

  

int cnt=0;

  

  

pthread_mutex_lock(&list->mutex);

  

  

LNode *p=list->head;

  

  

while(p!=NULL){

  

  

p=p->next;

  

  

cnt++;

  

  

}

  

  

pthread_mutex_unlock(&list->mutex);

  

  

return cnt;

  

}
```

```c
void hashInit(hash_lock_t* bucket) {

  

for(int i=0;i<HASHNUM;i++){

  

bucket->table[i].head=NULL;

  

pthread_mutex_init(&bucket->table[i].mutex,NULL);

  

}

  

}

  

  

int getValue(hash_lock_t* bucket, int key) {

  

int hash_key=HASH(key);

  

pthread_mutex_lock(&bucket->table[hash_key].mutex);

  

Hlist p=bucket->table[hash_key].head;

  

while(p!=NULL){

  

if(p->key==key){

  

int value=p->value;

  

pthread_mutex_unlock(&bucket->table[hash_key].mutex);

  

return value;

  

}

  

p=p->next;

  

}

  

pthread_mutex_unlock(&bucket->table[hash_key].mutex);

  

return -1;

  

}

  

  

void insert(hash_lock_t* bucket, int key, int value) {

  

int hash_key=HASH(key);

  

pthread_mutex_lock(&bucket->table[hash_key].mutex);

  

Hlist p=bucket->table[hash_key].head;

  

while(p!=NULL){

  

if(p->key==key){

  

p->value=value;

  

pthread_mutex_unlock(&bucket->table[hash_key].mutex);

  

return;

  

}

  

p=p->next;

  

}

  

Hnode* newnode=(Hnode*)malloc(sizeof(Hnode));

  

newnode->key=key;

  

newnode->value=value;

  

newnode->next=bucket->table[hash_key].head;

  

bucket->table[hash_key].head=newnode;

  

pthread_mutex_unlock(&bucket->table[hash_key].mutex);

  

}

  

  

int setKey(hash_lock_t* bucket, int key, int new_key) {

  

int old_key=HASH(key);

  

int hash_key=HASH(new_key);

  

if(key==new_key){

  

return 0;

  

}

  

if(old_key==hash_key){

  

pthread_mutex_lock(&bucket->table[old_key].mutex);

  

Hlist p=bucket->table[old_key].head;

  

while(p){

  

if(p->key==key){

  

p->key=new_key;

  

pthread_mutex_unlock(&bucket->table[old_key].mutex);

  

return 0;

  

}

  

p=p->next;

  

}

  

pthread_mutex_unlock(&bucket->table[old_key].mutex);

  

return -1;

  

}

  

int first=(old_key<hash_key)?old_key:hash_key;

  

int second=(old_key<hash_key)?hash_key:old_key;

  

pthread_mutex_lock(&bucket->table[first].mutex);

  

pthread_mutex_lock(&bucket->table[second].mutex);

  

Hlist p=bucket->table[old_key].head;

  

Hlist prev=NULL;

  

while(p){

  

if(p->key==key){

  

Hnode *newnode=(Hnode*)malloc(sizeof(Hnode));

  

newnode->key=new_key;

  

newnode->value=p->value;

  

newnode->next=bucket->table[hash_key].head;

  

bucket->table[hash_key].head=newnode;

  

if(prev==NULL){

  

bucket->table[old_key].head=p->next;

  

}else{

  

prev->next=p->next;

  

}

  

free(p);

  

pthread_mutex_unlock(&bucket->table[second].mutex);

  

pthread_mutex_unlock(&bucket->table[first].mutex);

  

return 0;

  

}

  

prev=p;

  

p=p->next;

  

}

  

pthread_mutex_unlock(&bucket->table[second].mutex);

  

pthread_mutex_unlock(&bucket->table[first].mutex);

  

return -1;

  

}
```