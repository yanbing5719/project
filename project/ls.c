#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include<unistd.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
// ANSI 颜色代码定义
#define RESET   "\033[0m"    //默认
#define BOLD    "\033[1m"   //粗体
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"  //青色
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"    //紫色
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

// 样式
#define STYLE_BOLD      "\033[1m"
#define STYLE_UNDERLINE "\033[4m"
// 背景色
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
//文件结构体
typedef struct file{
  char *name;
  char *pathname;
  struct stat st;
}F;
//压缩文件
int compress_file(const char * filename);
//代码文件
int code_file(const char * filename);
//文档文件
int document_file(const char * filename);
//根据不同类型决定不同颜色
const char *color(const char *filename,mode_t mode);
//时间戳比较小到大
int time_cmp(F *file1,F*file2);
//时间戳比较大到小
int time_cmp_dao(F *file1,F*file2);
//文件大小比较
int size_cmp(F *file1,F*file2);
//字母顺序比较
int character_cmp(char*file1,char*file2);
//文件权限
void authority(char *filename,mode_t mode);
//文件类型
char type(char *filename,mode_t mode);
void ls(int a,int l,int s,int i_1,int t,int r,F file[],int count);
void list_R(char *path,int a,int l,int s,int i_1,int t,int r);
int main(int argc,char *argv[]){
  int a=0;
  int l=0;
  int R=0;
  int t=0;
  int r=0;
  int i_1=0;
  int s=0;
   char *paths[256];
   int k=0;
  for(int i=1;i<argc;i++){
    if(argv[i][0]=='-'){
      for(int j=1;argv[i][j]!='\0';j++){
        switch(argv[i][j]){
        case 'a': a=1;break;
      case 'l': l=1;break;
      case 'R': R=1;break;
      case 't': t=1;break;
      case 'r': r=1;break;
      case 'i': i_1=1;break;
      case 's': s=1;break;
      }
    }
  }else{
   paths[k]=argv[i];
     k++;
}
  }
  if(k==0){
  paths[0]=".";
  k=1;
}
 for(int i=0;i<k;i++){
if(R==0){
 struct dirent *dp; 
  int count=0;
  char*path;
    F *file;
     char fullpath[4096];
     int place=4096;
file=(F*)malloc(sizeof(F)*place);

if(file==NULL){
   perror("malloc");
   exit(1);
}
    path=paths[i];
     DIR *dir=opendir(path);
     if(dir==NULL){
      perror("opendir");
     continue;
     }
 while((dp=readdir(dir))!=NULL){
  if(count>=place){
    place*=2;
   F*temp=realloc(file,sizeof(F)*place);
    if(temp==NULL){
   perror("realloc");
   exit(1);
}
file=temp;
  }
   sprintf(fullpath,"%s/%s",path,dp->d_name);
  lstat(fullpath,&file[count].st);
  file[count].name=(char*)malloc(256*sizeof(char));
  strcpy(file[count].name,dp->d_name);
  file[count].pathname=(char*)malloc((strlen(fullpath)+1)*sizeof(char));
  strcpy(file[count].pathname,fullpath);
  count++;
 }closedir(dir);
 qsort(file,count,sizeof(F),(int(*)(const void*,const void*))character_cmp);
  ls(a,l,s,i_1,t,r,file,count);

for(int i=0;i<count;i++){
free( file[i].name);
free(file[i].pathname);
}
free(file);
}
else{
  char*path;
   path=paths[i];
  list_R(path,a,l,s,i_1,t,r);
}
}
 

return 0;

}
//压缩文件
int compress_file(const char * filename){
  const char *compress_type[]={
     ".zip", ".tar", ".gz", ".bz2", ".xz", ".7z", ".rar", 
        ".tgz", ".tbz2", ".txz", ".lz", ".lzma", ".z", 
        ".Z", ".jar", ".war", ".ear", ".cab", ".deb", 
        ".rpm", ".apk", ".dmg", ".iso", NULL
    };
    int file_len=strlen(filename);
  for(int i=0;compress_type[i]!=NULL;i++){
    int extlen=strlen(compress_type[i]);
    if(file_len>extlen&&strncmp(compress_type[i],filename+(file_len-extlen),extlen)==0){
      return 1;
    }
  }
  return 0;
}
//代码文件
int code_file(const char * filename){
  const char*code_type[]={
      ".c", ".h", ".cpp", ".hpp", ".java", ".py", 
        ".js", ".ts", ".html", ".css", ".php", ".cs",
        ".go", ".rs", ".swift", ".rb", ".sh", ".pl",
        ".yml", ".yaml", ".json", ".xml", ".sql",
        ".lua", ".r", ".m", ".dart", ".scala",
        ".asm", ".s", ".mk", ".cmake",
        NULL
        
    };
    int file_len=strlen(filename);
  for(int i=0;code_type[i]!=NULL;i++){
    int extlen=strlen(code_type[i]);
    if(file_len>extlen&&strncmp(code_type[i],filename+(file_len-extlen),extlen)==0){
      return 1;
    }
  }

  return 0;
}
//文档文件
int document_file(const char * filename){
  const char*document_type[]={
       ".pdf", ".doc", ".docx", ".txt", ".rtf", ".md",
        ".xls", ".xlsx", ".ppt", ".pptx", ".odt", ".ods", ".odp",
        ".epub", ".mobi", ".pages", ".numbers", ".key",
        ".ini", ".cfg", ".conf", ".yml", ".yaml", ".json", ".xml",
        ".csv", ".tex",
        NULL
        
    };
   int file_len=strlen(filename);
  for(int i=0;document_type[i]!=NULL;i++){
    int extlen=strlen(document_type[i]);
    if(file_len>extlen&&strncmp(document_type[i],filename+(file_len-extlen),extlen)==0){
      return 1;
    }
  }
  return 0;
}
//根据不同类型决定不同颜色
const char *color(const char *filename,mode_t mode){ //mode_t 文件类型和权限
        if(S_ISDIR(mode))  return BOLD BLUE;  //目录
        if (S_ISLNK(mode)) return CYAN;   //符号连接
        if (S_ISLNK(mode)) return MAGENTA BOLD;

         if (S_ISCHR(mode)) return YELLOW BG_BLUE BOLD;
          if (S_ISBLK(mode)) return YELLOW BG_BLUE BOLD;
        //if (mode & S_IXUSR) return COLOR_EXEC;
       if(S_ISFIFO(mode)) return YELLOW BOLD;
       if(S_ISSOCK(mode)) return MAGENTA BOLD;
         if (S_ISREG(mode)) {
         if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
        return GREEN;   // 可执行文件
    }
       if(compress_file(filename)) return RED BOLD;
       if(document_file(filename))  return RESET;
       if(code_file(filename)) return GREEN;
  }
       return RESET;
    }
//时间戳比较大到小(比较精度应该为纳秒级但是该系统不支持)
int time_cmp_dao(F *file1,F*file2){
  if(file1->st.st_mtime <file2->st.st_mtime){
  return 1;
  }else if(file1->st.st_mtime>file2->st.st_mtime){
    return -1;
  }else{
    return 0;
  }
}
//文件大小比较
int size_cmp(F *file1,F*file2){
  if(file1->st.st_size<file2->st.st_size){
  return -1;
  }else if(file1->st.st_size>file2->st.st_size){
    return 1;
  }else{
    return 0;
  }
}
//字母顺序比较
int character_cmp(char*file1,char*file2){
 return strcmp(file1,file2);
}
//文件权限
void authority(char *filename,mode_t mode){
  const char *str="rwxrwxrwx";
  char usestr[10];
  strcpy(usestr,str);
  if((mode&S_IRUSR)==0) usestr[0]='-';
   if((mode&S_IWUSR)==0) usestr[1]='-';
    if((mode&S_IXUSR)==0) usestr[2]='-';
     if((mode&S_IRGRP)==0) usestr[3]='-';
      if((mode&S_IWGRP)==0) usestr[4]='-';
       if((mode&S_IXGRP)==0) usestr[5]='-';
        if((mode&S_IROTH)==0) usestr[6]='-';
         if((mode&S_IWOTH)==0) usestr[7]='-';
          if((mode&S_IXOTH)==0) usestr[8]='-';
  printf("%s",usestr);
}
//文件类型
char type(char *filename,mode_t mode){
  if(S_ISREG(mode)) return '-';
  if(S_ISDIR(mode)) return 'd';
  if (S_ISLNK(mode)) return 'l';
  if(S_ISCHR(mode)) return 'c';
  if(S_ISBLK(mode)) return 'b';
  if(S_ISFIFO(mode)) return 'p';
  if(S_ISSOCK(mode)) return 's';
  if(S_ISLNK(mode)) return 'l';
}

void list_R(char *path,int a,int l,int s,int i_1,int t,int r){
     DIR*dir=opendir(path);
     if(dir==NULL)return ;
     struct dirent *dp; 
     struct stat st;
     char fullpath[4096];
     F *file;
    file=(F*)malloc(sizeof(F)*4096);
int place=4096;
if(file==NULL){
   perror("malloc");
   exit(1);
}
     int count=0;
     printf("%s:\n",path);
     //打印当前目录的内容
     int k=0;
     while((dp=readdir(dir))!=NULL){
       if(count>=place){
    place*=2;
  F*temp=realloc(file,sizeof(F)*place);
    if(temp==NULL){
   perror("realloc");
   exit(1);
    }
    file=temp;
}
      if(a==0){
     if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
        continue;
    }
      if(dp->d_name[0]=='.'){
        continue;
      }  
    }
        sprintf(fullpath,"%s/%s",path,dp->d_name);
  lstat(fullpath,&file[count].st);
  file[count].name=(char*)malloc(256*sizeof(char));
  strcpy(file[count].name,dp->d_name);
  file[count].pathname=(char*)malloc((strlen(fullpath)+1)*sizeof(char));
  strcpy(file[count].pathname,fullpath);
  count++;
    }
  ls(a,l,s,i_1,t,r,file,count);
  printf("\n");
    //递归子目录     
    rewinddir(dir); 
         for(int i=0;i<count;i++){
     if (strcmp(file[i].name, ".") == 0 || strcmp(file[i].name, "..") == 0) {
        continue;
    } 
      if(a==0&&file[i].name[0]=='.'){
        continue;
      }  
      if(S_ISDIR(file[i].st.st_mode)){
         if (strcmp(file[i].pathname, "/proc") == 0 ||
        strcmp(file[i].pathname, "/sys") == 0 ||
        strcmp(file[i].pathname, "/dev") == 0) {
        continue;
    }

       list_R(file[i].pathname,a,l,s,i_1,t,r);
      }
         }
  
     for(int i=0;i<count;i++){
        free(file[i].name);
        free(file[i].pathname);
    }
  free(file);
    closedir(dir);
}

void ls(int a,int l,int s,int i_1,int t,int r,F file[],int count){
  //-t
if(t==1){
  qsort(file,count,sizeof(F),(int(*)(const void*,const void*))time_cmp_dao);
//-r
if(r==1){
 for(int i=0;i<count/2;i++){
  F temp=file[i];
  file[i]=file[count-1-i];
  file[count-1-i]=temp;
 }
}
}
      for(int i=0;i<count;i++){
       if(a==0&&file[i].name[0]=='.'){
         continue;
} 
        const char*p=color(file[i].pathname,file[i].st.st_mode);
  char T=type(file[i].pathname,file[i].st.st_mode);
  //获取用户名
 struct passwd *pw=getpwuid(file[i].st.st_uid);
//获取用户组名
struct group *gr=getgrgid(file[i].st.st_gid);
if(i_1==1){
     printf("%-7ld ",file[i].st.st_ino);
}
if(s==1){
   printf("%-ld ",file[i].st.st_blocks);
}
if(l==1){
 printf("%c",T);
 authority(file[i].pathname,file[i].st.st_mode);
 printf(" %-ld %-s %-s %-ld",file[i].st.st_nlink,pw->pw_name,gr->gr_name,file[i].st.st_size);
 printf(" %-.16s ",ctime(&file[i].st.st_mtime));  
 printf(" %s%-s%s\n",p,file[i].name,RESET);
}else if(l==0){
    printf("%s%-25s%s",p,file[i].name,RESET);
      if((i+1)%3==0){
        printf("\n");
      }
        }else if(a==1&&!s&&!i&&!l){
   for(int i=0;i<count;i++){
       printf("%s%-25s%s",p,file[i].name,RESET);
  if(i%4==0){
    printf("\n");
  }
        }
        }
      }
    }
