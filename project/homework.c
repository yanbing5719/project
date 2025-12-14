/*#include <stdio.h>

// ANSI 颜色代码定义
#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// 背景色
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

// 样式
#define STYLE_BOLD      "\033[1m"
#define STYLE_UNDERLINE "\033[4m"

int main() {
    printf("=== 前景色测试 ===\n");
    printf("%s■ 黑色 (30)%s\n", COLOR_BLACK, COLOR_RESET);
    printf("%s■ 红色 (31)%s\n", COLOR_RED, COLOR_RESET);
    printf("%s■ 绿色 (32)%s\n", COLOR_GREEN, COLOR_RESET);
    printf("%s■ 黄色 (33)%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("%s■ 蓝色 (34)%s\n", COLOR_BLUE, COLOR_RESET);
    printf("%s■ 紫色 (35)%s\n", COLOR_MAGENTA, COLOR_RESET);
    printf("%s■ 青色 (36)%s\n", COLOR_CYAN, COLOR_RESET);
    printf("%s■ 白色 (37)%s\n", COLOR_WHITE, COLOR_RESET);
    
    printf("\n=== 背景色测试 ===\n");
    printf("%s 黑色背景 (40) %s\n", BG_BLACK, COLOR_RESET);
    printf("%s 红色背景 (41) %s\n", BG_RED, COLOR_RESET);
    printf("%s 绿色背景 (42) %s\n", BG_GREEN, COLOR_RESET);
    printf("%s 黄色背景 (43) %s\n", BG_YELLOW, COLOR_RESET);
    printf("%s 蓝色背景 (44) %s\n", BG_BLUE, COLOR_RESET);
    printf("%s 紫色背景 (45) %s\n", BG_MAGENTA, COLOR_RESET);
    printf("%s 青色背景 (46) %s\n", BG_CYAN, COLOR_RESET);
    printf("%s 白色背景 (47) %s\n", BG_WHITE, COLOR_RESET);
    
    printf("\n=== 样式测试 ===\n");
    printf("%s粗体文字 (1)%s\n", STYLE_BOLD, COLOR_RESET);
    printf("%s下划线文字 (4)%s\n", STYLE_UNDERLINE, COLOR_RESET);
    printf("%s%s粗体红色文字%s\n", STYLE_BOLD, COLOR_RED, COLOR_RESET);
    
    printf("\n=== 组合测试 ===\n");
    printf("%s%s粗体红色在黑背景上%s\n", STYLE_BOLD, COLOR_RED, BG_BLACK, COLOR_RESET);
    printf("%s%s绿色在黄背景上%s\n", COLOR_GREEN, BG_YELLOW, COLOR_RESET);
    printf("%s%s%s粗体青色在红背景上%s\n", STYLE_BOLD, COLOR_CYAN, BG_RED, COLOR_RESET);
    
    return 0;
}
    */
  /* #include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(){
    int fd=open("ls.c",O_WRONLY|O_APPEND);
    if(fd==-1){
        printf("%d",errno);
        printf("%s",strerror(errno));
        perror("open");
        return 1;
    }
    lseek(fd,0,SEEK_SET);
    char data[]="hello";
    ssize_t n=write(fd,data,sizeof(data)-1);
    return 0;
}
    */
   #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
char *dir_path;
struct store {
    char name[1024];
    long time;
    int index;
};
int cmpe(const void *a, const void *b) {
    struct store *file_a = (struct store *)a;
    struct store *file_b = (struct store *)b;
    if (file_a->time > file_b->time)
        return -1;
    if (file_a->time < file_b->time)
        return 1;
    return 0;
}
int yasuofile(const char *filename);
int image(const char *filename);
void print(int mark, char *dir_path);
void listpanduan(int mark, char *dir, int depth, int max);
int main(int argc, char *argv[]) {
    char *ext = NULL;
    char *optstring = "alRtris";
    int ch, mark = 1;
    const char *a = "/";
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '/' && i != argc - 1) {
            int cnt;
            ext = argv[i];
            cnt = strlen(ext);
            char diir[1024];
            strcpy(diir, ext);
            if (argv[i][cnt - 1] != '/') {   
                strncat(diir, a, 1);
            }
           dir_path = strdup(diir);
           dir_path=diir;
        } else if (argv[i][0] == '.') {
            char *extl = malloc(sizeof(char) * 1024);
            if (extl == NULL) {
                perror("malloc failed");
                return 1;
            }
            getcwd(extl, 1024);
            char *path = malloc(sizeof(char) * 1024);
            if (path == NULL) {
                perror("malloc failed");
                free(extl);
                return 1;
            }
            strncpy(path, argv[i], 1024);
            memmove(path, path + 1, strlen(path));
            strncat(extl, path, 1024 - strlen(extl) - 1);
            strncat(extl, a, 1);
            dir_path = strdup(extl);
            free(extl);
            free(path);
        }
    }
    if (dir_path == NULL) {
        if (argc == 1 || argv[argc - 1][0] != '/') {
            ext = malloc(sizeof(char) * 1024);
            getcwd(ext, 1024);
            if (ext[strlen(ext) - 1] != '/') {   
                char diir[1024];
                strcpy(diir, ext);
                const char *a = "/";
                strncat(diir, a, 1);
                dir_path = strdup(diir);
            } else dir_path = strdup(ext);
            free(ext);
        } else if (argv[argc - 1][0] != '.') {
            int cnt;
            ext = argv[argc - 1];
            cnt = strlen(ext);
            char diir[1024];
            strcpy(diir, ext);
            if (argv[argc - 1][cnt - 1] != '/') {   
                const char *a = "/";
                strncat(diir, a, 1);
            }
            dir_path = strdup(diir);
        }
    }
    while ((ch = getopt(argc, argv, optstring)) != -1) {
        switch (ch) {
            case 'a':
                mark *= 2;
                break;
            case 'l':
                mark *= 3;
                break;
            case 'R':
                mark *= 5;
                break;
            case 't':
                mark *= 7;
                break;
            case 'r':
                mark *= 11;
                break;
            case 'i':
                mark *= 13;
                break;
            case 's':
                mark *= 17;
                break;
            default:
                break;
        }
    }
    if (mark % 5 == 0) {
        print(mark, dir_path);
        listpanduan(mark, dir_path, 0, 4);
    } else {
        print(mark, dir_path);
    }
    if (dir_path != NULL) free(dir_path);
    return 0;
}
void listpanduan(int mark, char *dir, int depth, int max) {
    if (depth > max) {
        return;
    }
    DIR *dirr = opendir(dir);
    if (dirr == NULL) {
        perror("fail open dir");
        return;
    }
    struct dirent *r;
    struct stat filestat;
    while ((r = readdir(dirr)) != NULL) {
        if (strcmp(r->d_name, ".") == 0 || strcmp(r->d_name, "..") == 0) continue;
        char path[1024];
        snprintf(path, sizeof(path), "%s%s", dir, r->d_name);
        const char *a = "/";
        strncat(path, a, 1);
        if (mark % 2 != 0 && r->d_name[0] == '.') continue;
        if (stat(path, &filestat) == -1) {
            continue;
        }
        if (S_ISDIR(filestat.st_mode)) {
            print(mark, path);
            printf("\n");
            listpanduan(mark, path, depth + 1, 4);
        }
    }
    closedir(dirr);
}
void print(int mark, char *dir_path) {
    if (mark % 5 == 0) printf("%s:\n", dir_path);
    DIR *dirr = opendir(dir_path);
    if (!dirr) {
        perror("fail open dir");
        return;
    }
    char path[10240];
    char rwx[11];
    int j = 0, filenum = 0;
    int size = 5000;
    struct dirent *r;
    struct stat *filestat = malloc(sizeof(struct stat) * size);
    struct store *s = malloc(sizeof(struct store) * size);
    if (filestat==NULL||s==NULL) {
        perror("内存分配失败");
        free(filestat);
        free(s);
        closedir(dirr);
        return;
    }
    while ((r = readdir(dirr)) != NULL) {
        if (strcmp(r->d_name, ".") == 0 || strcmp(r->d_name, "..") == 0) continue;
        if (mark % 2 != 0 && r->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "%s%s", dir_path, r->d_name);
        if (lstat(path, &filestat[filenum]) == -1) {
            perror("files fail");
            continue;
        }
        strncpy(s[filenum].name, r->d_name, sizeof(s[filenum].name) - 1);
        s[filenum].time = filestat[filenum].st_mtime;
        s[filenum].index = filenum;
        filenum++;
        if (filenum >= size) {
            size *= 2;
            filestat = realloc(filestat, sizeof(struct stat) * size);
            s = realloc(s, sizeof(struct store) * size);
            if (filestat==NULL||s==NULL) {
                perror("realloc fail");
                free(filestat);
                free(s);
                closedir(dirr);
                return;
            }
        }
    }
    if (mark % 7 == 0){
        qsort(s, filenum, sizeof(struct store), cmpe);
        struct stat *aboutfilestat = malloc(sizeof(struct stat) * filenum);
        for (int i = 0; i < filenum; i++) {
            aboutfilestat[i] = filestat[s[i].index];
        }
        free(filestat);
        filestat = aboutfilestat;
    }
    if (mark % 11 == 0) {
        int end = filenum - 1;
        for (int i = 0; i < filenum / 2; i++) {
            struct stat t = filestat[i];
            filestat[i] = filestat[end];
            filestat[end] = t;
            struct store x = s[i];
            s[i] = s[end];
            s[end] = x;
            end--;
        }
    }
    for (int i = 0; i < filenum; i++) {
        if (mark % 13 == 0) printf("%ld ", (long)filestat[i].st_ino);
        if (mark % 17 == 0) printf("%2ld ", filestat[i].st_blocks / 2);
        if (mark % 3 == 0) {
            mode_t file = filestat[i].st_mode;
            rwx[0] = S_ISDIR(file) ? 'd' : (S_ISLNK(file) ? 'l' : '-');
            rwx[1] = (file & S_IRUSR) ? 'r' : '-';
            rwx[2] = (file & S_IWUSR) ? 'w' : '-';
            rwx[3] = (file & S_IXUSR) ? 'x' : '-';
            rwx[4] = (file & S_IRGRP) ? 'r' : '-';
            rwx[5] = (file & S_IWGRP) ? 'w' : '-';
            rwx[6] = (file & S_IXGRP) ? 'x' : '-';
            rwx[7] = (file & S_IROTH) ? 'r' : '-';
            rwx[8] = (file & S_IWOTH) ? 'w' : '-';
            rwx[9] = (file & S_IXOTH) ? 'x' : '-';
            rwx[10] = '\0';
            struct passwd *user = getpwuid(filestat[i].st_uid);
            struct group *gro = getgrgid(filestat[i].st_gid);
            time_t mod_time = filestat[i].st_mtime;
            struct tm *tt = localtime(&mod_time);
            char ctime[100];
            strftime(ctime, sizeof(ctime), "%m月 %d %H:%M", tt);
            printf("%-s %2ld %-s %-s %5ld %s ", rwx, filestat[i].st_nlink, user->pw_name, gro->gr_name, filestat[i].st_size, ctime);
        }
        if (s[i].name[0]=='.'&&strcmp(s[i].name,".")!=0&&strcmp(s[i].name,"..")!=0) {
            printf("\033[90;1m %-15s\033[0m", s[i].name);
        }else if(image(s[i].name)){
            printf("\033[35;1m %-15s\033[0m", s[i].name);
        }else if(yasuofile(s[i].name)){
            printf("\033[31;1m %-15s\033[0m", s[i].name);
        }else if (S_ISLNK(filestat[i].st_mode))
        {
            printf("\033[36;1m %-15s\033[0m", s[i].name);
        }
        else if (S_ISREG(filestat[i].st_mode) && access(s[i].name, X_OK))
        {
            printf("\033[32;1m %-15s\033[0m", s[i].name);
        }
        else if (S_ISDIR(filestat[i].st_mode)){
            printf("\033[34;1m %-15s\033[0m", s[i].name);
        }
        else 
        {
            printf("%-15s", s[i].name);
        }
        if(mark%3==0) printf("\n");
        else{
            j++;
            if (j==3 )
            {
                printf("\n");
                j=0;
            }
        }
    }
    free(filestat);
    free(s);
    closedir(dirr);
}
int image(const char *filename) {
    const char *imagename[] = {".jpg", ".jpeg", ".png", ".bmp", ".gif", ".tiff", ".webp", NULL};
    int len = strlen(filename);
    for (int i = 0; imagename[i] != NULL; i++) {
        int len2 = strlen(imagename[i]);
        if (len >= len2 && strncmp(filename + len - len2, imagename[i], len2) == 0) {
            return 1;
        }
    }
    return 0;
}
int yasuofile(const char *filename) {
    const char *yasuoname[] = {".tar", ".gz", ".bz2", ".xz", ".zip", ".7z", ".rar", NULL};
    int len = strlen(filename);
    for (int i = 0; yasuoname[i] != NULL; i++) {
        int len2 = strlen(yasuoname[i]);
        if (len >= len2 && strncmp(filename + len - len2, yasuoname[i],len2) == 0) {
            return 1;
        }
    }
    return 0;
}
