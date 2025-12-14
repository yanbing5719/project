 /*printf("%c",T);
  authority(dp->d_name,st.st_mode);
 printf(" %ld %s %s %ld",st.st_nlink,pw->pw_name,gr->gr_name,st.st_size);
 printf(" %.24s ",ctime(&st.st_mtime));  
 printf(" %s%s%s\n",p,dp->d_name,RESET);
  }else if(l==0&&a==1){
       printf("%-s%-10s%s     ",p,dp->d_name,RESET);
  if(count%4==0){
    printf("\n");
  }
        }
  1. 解析参数
2. 读取目录（递归 -R）
3. 过滤文件（-a）
4. 为每个文件收集信息（stat）
5. 排序（-t / -r）
6. 打印（-l -i -s 控制格式）
*/
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
//时间戳比较
int time_cmp(F *file1,F*file2);
//文件大小比较
int size_cmp(F *file1,F*file2);
//字母顺序比较
int character_cmp(char*file1,char*file2);
//文件权限
void authority(char *filename,mode_t mode);
//文件类型
char type(char *filename,mode_t mode);
//-R的递归
void list_R(char *path);
int main(int argc,char *argv[]){
  int a=0;
  int l=0;
  int R=0;
  int t=0;
  int r=0;
  int i_1=0;
  int s=0;
  //文件信息结构体
  /*struct stat {
    dev_t     st_dev;       // 文件所在设备 ID
    ino_t     st_ino;       // inode 编号（硬链接共享同一个 ino）
    mode_t    st_mode;      // 文件类型 + 权限（最重要！）
    nlink_t   st_nlink;     // 硬链接数量
    uid_t     st_uid;       // 文件拥有者 UID
    gid_t     st_gid;       // 文件所属组 GID
    dev_t     st_rdev;      // 设备文件的主/次设备号（仅对特殊文件有效）
    off_t     st_size;      // 文件大小（字节），普通文件最常用
    blksize_t st_blksize;   // 文件系统 I/O 最佳块大小（用于优化读写）
    blkcnt_t  st_blocks;    // 实际占用 512B 块的数量（不是 st_size！）
    struct timespec st_atim;   // 最后访问时间（access time）
    struct timespec st_mtim;   // 最后修改时间（modify time，内容变）
    struct timespec st_ctim;   // 最后状态改变时间（change time，权限/属主变）
    /* 下面三个是为了 POSIX 兼容性提供的别名 
    #define st_atime st_atim.tv_sec
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
};*/
  //struct stat st;
   F file[1024];
  // mode_t mode[1000];
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
  }
}
     //定义目录条目结构体
     /*struct dirent {
    ino64_t        d_ino;           // 64位 inode 号
    off64_t        d_off;           // 下个条目的偏移
    unsigned short d_reclen;        // 当前记录长度
    unsigned char  d_type;          // 文件类型
    char           d_name[NAME_MAX+1]; // NAME_MAX 通常是 255
};
*/
 struct dirent *dp; 
  int count=0;
 char *l1=".";
  char *l2="..";
  if(R==1){
    list_R(".");
    return 0;
  }
     DIR *dir=opendir(".");
     if(dir==NULL){
      perror("opendir");
      return 1;
     }
      const char*p;
   char T;
  //获取用户名
 struct passwd *pw;
//获取用户组名
struct group *gr;
  while((dp=readdir(dir))!=NULL){
  if(a==0&&(strcmp(dp->d_name,l1)==0||strcmp(dp->d_name,l2)==0)){
  continue;
}   
  //将当前文件名写入st里面，readdir不断读取下一个文件名，新文件会覆盖旧文件
  lstat(dp->d_name,&file[count].st);
  strcpy(file[count].name,dp->d_name);
  p=color(dp->d_name,file[count].st.st_mode);
   T=type(dp->d_name,file[count].st.st_mode);
  //获取用户名
 pw=getpwuid(file[count].st.st_uid);
//获取用户组名
gr=getgrgid(file[count].st.st_gid);
  count++;
  closedir(dir);
}
     if(l){
  printf("%c",T);
  authority(dp->d_name,st.st_mode);
 printf(" %ld %s %s %ld",st.st_nlink,pw->pw_name,gr->gr_name,st.st_size);
 printf(" %.24s ",ctime(&st.st_mtime));  
 printf(" %s%s%s\n",p,dp->d_name,RESET);
  }else if(l==0&&a==1){
       printf("%-s%-10s%s     ",p,dp->d_name,RESET);
  if(count%4==0){
    printf("\n");
  }
        }
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
         if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
        return GREEN;   // 可执行文件
    }
        if (S_ISREG(mode)) return RESET;  //普通文件默认色
        if (S_ISBLK(mode)) return YELLOW BG_BLUE BOLD;
        if (S_ISCHR(mode)) return YELLOW BG_BLUE BOLD;
        //if (mode & S_IXUSR) return COLOR_EXEC;
       if(S_ISFIFO(mode)) return YELLOW BOLD;
       if(S_ISSOCK(mode)) return MAGENTA BOLD;
       if(compress_file(filename)) return RED BOLD;
       if(document_file(filename))  return CYAN;
       if(code_file(filename)) return GREEN;
    }
//时间戳比较
int time_cmp(F *file1,F*file2){
  if(file1->st.st_mtime<file2->st.st_mtime){
  return -1;
  }else if(file1->st.st_mtime>file2->st.st_mtime){
    return 1;
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
  if(S_ISCHR(mode)) return 'c';
  if(S_ISBLK(mode)) return 'b';
  if(S_ISFIFO(mode)) return 'p';
  if(S_ISSOCK(mode)) return 's';
  if(S_ISLNK(mode)) return 'l';
}
//-R的递归
void list_R(char *path){
  DIR*dir=opendir(path);
struct dirent *contents;
char path_name[1024];
struct stat st_c;
printf("%s",path);
while((contents=readdir(dir))!=NULL){
sprintf(path_name,"%s/%s",path,contents->d_name);
lstat(path_name,&st_c);
if(S_ISDIR(st_c.st_mode)){
if(strcmp(contents->d_name,".")==0||strcmp(contents->d_name,"..")==0){
  continue;
}
printf("%s\n",contents->d_name);
list_R(path_name);
}
}
closedir(dir);
}

