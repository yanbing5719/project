```c
// 向 sb 追加长度为 len 的数据 data

void strbuf_add(struct strbuf *sb, const void *data, size_t len){

if(data==NULL||sb==NULL||len==0) return;

strbuf_grow(sb,len);

/*for(size_t i=0;i<len;i++){

sb->buf[sb->len+i]=((char*)data)[i];

}*/

memcpy(sb->buf+sb->len,data,len);

sb->len+=len;

sb->buf[sb->len]='\0';

}

  

// 向 sb 追加一个字符 c

void strbuf_addch(struct strbuf *sb, int c){

if(sb==NULL) return ;

size_t len=1;

strbuf_grow(sb,len);

sb->buf[sb->len]=(char)c;

sb->len+=1;

sb->buf[sb->len]='\0';

}

// 向 sb 追加一个字符串 s

void strbuf_addstr(struct strbuf *sb, const char *s){

size_t len=strlen(s);

strbuf_grow(sb,len);

memcpy(sb->buf+sb->len,s,len);

sb->len+=len;

sb->buf[sb->len]='\0';

}

  

// 向一个 sb 追加另一个 strbuf 的数据

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){

if(sb==NULL||sb2==NULL){

return;

}

strbuf_grow(sb,sb2->len);

// strbuf_addstr(sb,sb2->buf);如果sb2->buf里面有NULL（\0)则会截断数据

memcpy(sb->buf+sb->len,sb2->buf,sb2->len);

sb->len+=sb2->len;

sb->buf[sb->len]='\0';

}
```