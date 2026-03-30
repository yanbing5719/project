#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//颜色
#define COLOR_RESET   "\033[0m"     //重置样式
#define COLOR_RED     "\033[31m"    //红色
#define COLOR_GREEN   "\033[32m"    //绿色
#define COLOR_YELLOW  "\033[33m"    //黄色
#define COLOR_BLUE    "\033[34m"    //蓝色
#define COLOR_MAGENTA "\033[35m"    //紫色
#define COLOR_CYAN    "\033[36m"    //青色
#define COLOR_WHITE   "\033[37m"    //白色

// 加粗样式
#define BOLD          "\033[1m"     //加粗
#define UNDERLINE     "\033[4m"     //下划线

//图书信息用结构体来储存
typedef struct book {
    int id;                 // 图书编号（唯一）
    char name[100];         // 书名
    char author[50];        // 作者
    char publisher[100];    // 出版社
    char isbn[20];          // ISBN编号
    float price;            // 价格
    int total;              // 总库存
    int available;          // 可借数量
    struct book* next;      //指向下一个节点
}b;

//清空缓冲区
void clearbuffer();
//fgets读取函数
int fgets1(char str[], int size);
//设置登陆密码
int secret();
//录入数据
b* init();
//构建链表（每一个节点里面储存一本书的信息）
b* creatlist(b* head);
//打印单本内容
void print(b* cur);
//显示所有图书
void show(b* head);
//写入文件函数
void writefile(char* filename, b* head);
//读取文件里面的内容
b* readfile(char* filename);
//图书信息按照id排序(插入排序)
b* sort(b* head);
//添加图书
b* add(b* head, int n);
//查找图书
b* find(b* head);
//删除图书
b* deletebook(b* head);
//修改单个数据
b* change1(b* head, b* node, int c, int* num, float* num2, char str[]);
//修改图书
b* changebook(b* head);
//借书
b* borrowbook(b* head);
//还书
b* returnbook(b* head);
//打印菜单
void printmenu();

//主函数
int main() {
    b* head = NULL;
    char filename[] = "books.txt";
    int a = secret();
    if (a == 0) {
        return 0;
    }
    head = readfile(filename);
    if (head == NULL) {
        printf("该文件为空，请先录入数据：\n");
        int n;
        printf("输入添加书籍的数目：\n");
        scanf("%d", &n);
        getchar();
        head = add(head, n);
    }
    int c;
    char point;
    while (1) {
        head = sort(head);
        printf("显示菜单请按*\n");
        scanf("%c", &point);
        if (point == '*') {
            printmenu();
            scanf("%d", &c);
            getchar();
        }
        else {
            continue;
        }
        switch (c) {
        case 1:
            show(head);
            break;
        case 2: {
            int n;
            printf("输入添加书籍的数目：\n");
            scanf("%d", &n);
            getchar();
            head = add(head, n);
            break;
        }
        case 3: {
            b* node;
            node = find(head);
            if (node == NULL) {
                break;
            }
            print(node);
            break;
        }
        case 4:
            head = deletebook(head);
            break;
        case 5:
            head = changebook(head);
            break;
        case 6:
            head = borrowbook(head);
            break;
        case 7:
            head = returnbook(head);
            break;
        case 8: {
            writefile(filename, head);
            printf("保存成功，退出系统！！！\n");
            return 0;
        }
        default:
            printf("输入错误，请重新输入：\n");
            break;
        }
    }
    return 0;
}

//fgets读取函数
int fgets1(char str[], int size) {
    fgets(str, size, stdin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    return len;
}

//清空缓冲区
void clearbuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//设置登陆密码
int secret() {
    const char* username = "yanbing";
    const char* str = "zxcvbnm";
    char str1[20];
    char str2[20];
    //利用point判断是否登陆成功
    int point = 0;
    for (int i = 0; i < 3; i++) {
        printf("请输入用户名：\n");
        int len2 = fgets1(str2, sizeof(str2));
        if (strcmp(username, str2) != 0) {
            if (2 - i > 0) {
                printf("用户名错误，请重新输入：\n");
                continue;
            }
        }
        else {
            printf("请输入密码：\n");
            int len1 = fgets1(str1, sizeof(str1));
            if (!strcmp(str, str1) && !strcmp(username, str2)) {
                printf("登陆成功！\n");
                point = 1;
                return point;
            }
        }
        if (2 - i > 0)
            printf("密码错误，还剩%d次机会\n", 2 - i);
    }
    printf("登陆失败!\n");
    return point;
}

//录入数据
b* init() {
    b* books = (b*)malloc(sizeof(b));
    printf("输入编号：");
    //判断字段输入的准确性
    if (scanf("%d", &books->id) == 0) {
        printf("格式错误\n");
        clearbuffer();
        free(books);
        return NULL;
    }
    getchar();
    printf("输入书名：");
    int len2 = fgets1(books->name, sizeof(books->name));
    printf("输入作者：");
    int len3 = fgets1(books->author, sizeof(books->author));
    printf("输入出版社：");
    int len4 = fgets1(books->publisher, sizeof(books->publisher));
    printf("输入ISBN：");
    int len1 = fgets1(books->isbn, sizeof(books->isbn));
    printf("输入价格：");
    scanf("%f", &books->price);
    getchar();
    //判断字段输入的准确性
    printf("输入总数：");
    if (scanf("%d", &books->total) == 0) {
        printf("格式错误\n");
        clearbuffer();
        free(books);
        return NULL;
    }
    getchar();
    books->available = books->total;
    books->next = NULL;
    return books;
}

//构建链表（每一个节点里面储存一本书的信息）<头插法>
b* creatlist(b* head) {
    b* books = init();
    if (books == NULL) {
        return NULL;
    }
    books->next = head;
    head = books;
    return head;
}

//打印单本内容
void print(b* cur) {
    printf(COLOR_BLUE "────────────────────────\n" COLOR_RESET);
    printf(" 编号: %d\n", cur->id);
    printf(" 书名: %s\n", cur->name);
    printf(" 作者: %s\n", cur->author);
    printf(" 出版社: %s\n", cur->publisher);
    printf(" ISBN: %s\n", cur->isbn);
    printf(" 价格: %.2f\n", cur->price);
    printf(" 总库存: %d\n", cur->total);
    printf(" 可借: %d\n", cur->available);
    printf(COLOR_BLUE "────────────────────────\n\n" COLOR_RESET);
}
//显示所有图书
void show(b* head) {
    if (head == NULL) {
        printf(COLOR_RED " 当前没有图书数据\n" COLOR_RESET);
        return;
    }

    printf(COLOR_CYAN " 图书列表\n" COLOR_RESET);

    b* cur = head;
    int total = 0, remain = 0;

    while (cur != NULL) {
        printf(COLOR_BLUE "══════════════════════════════\n" COLOR_RESET);

        printf(" 编号: %d\n", cur->id);
        printf(" 书名: %s\n", cur->name);
        printf(" 作者: %s\n", cur->author);
        printf(" 出版社: %s\n", cur->publisher);
        printf(" 价格: %.2f\n", cur->price);
        printf(" 库存: %d / 可借: %d\n", cur->total, cur->available);

        total += cur->total;
        remain += cur->available;

        cur = cur->next;
    }

    printf(COLOR_BLUE "══════════════════════════════\n" COLOR_RESET);

    printf(COLOR_GREEN "总库存: %d  " COLOR_RESET, total);
    printf(COLOR_BLUE  "剩余: %d  " COLOR_RESET, remain);
    printf(COLOR_RED   "借出: %d\n" COLOR_RESET, total - remain);
}
//写入文件函数
void writefile(char* filename, b* head) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        return;
    }
    b* p = head;
    while (p != NULL) {
        fprintf(fp, "%d|%s|%s|%s|%s|%.2f|%d|%d\n",
            p->id, p->name, p->author, p->publisher,
            p->isbn, p->price, p->total, p->available);
        p = p->next;
    }
    fclose(fp);
}

//读取文件里面的内容
b* readfile(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }
    b* head = NULL;
    while (1) {
        b* node = (b*)malloc(sizeof(b));
        if (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d|%d",
            &node->id,
            node->name,
            node->author,
            node->publisher,
            node->isbn,
            &node->price,
            &node->total,
            &node->available) != 8) {
            free(node);
            break;
        }
        node->next = head;
        head = node;
    }
    fclose(fp);
    return head;
}

//图书信息按照id排序(插入排序)
b* sort(b* head) {
    b* cur = head;
    b* res = NULL;
    while (cur != NULL) {
        b* nest = cur->next;
        if (res == NULL || cur->id < res->id) {
            cur->next = res;
            res = cur;
        }
        else {
            b* p = res;
            while (p->next != NULL && p->next->id < cur->id) {
                p = p->next;
            }
            cur->next = p->next;
            p->next = cur;
        }
        cur = nest;
    }
    return res;
}

//添加图书
b* add(b* head, int n) {
    for (int i = 0; i < n; i++) {
        head = creatlist(head);
        if (head == NULL) {
            printf("添加失败\n");
            return head;
        }
    }
    return head;
}

//查找图书
b* find(b* head) {
    b* cur = head;
    printf("请选择查找方式：\n");
    printf("1. 按编号\n");
    printf("2. 按书名\n");
    printf("3. 按编号 + 书名\n");
    int choice;
    int found = 0;
    scanf("%d", &choice);
    getchar();
    if (choice == 1) {
        int fid;
        printf("请输入编号：\n");
        scanf("%d", &fid);
        getchar();//读取换行符，不影响下一次读取
        while (cur != NULL) {
            if (cur->id == fid) {
                return cur;
            }
            cur = cur->next;
        }
    }
    else if (choice == 2) {
        char bname[100];
        printf("请输入要查找的书名：");
        int m = fgets1(bname, sizeof(bname));
        int num = 0;
        while (cur != NULL) {
            if (strcmp(cur->name, bname) == 0) {
                return cur;
            }
            cur = cur->next;
        }
    }
    else if (choice == 3) {
        int fid;
        char bname[100];

        printf("请输入编号：\n");
        scanf("%d", &fid);
        getchar();

        printf("请输入书名：");
        fgets1(bname, sizeof(bname));

        while (cur != NULL) {
            if (cur->id == fid && strcmp(cur->name, bname) == 0) {
                return cur;
            }
            cur = cur->next;
        }
    }
    printf("该书不存在\n");
    return NULL;

}

//删除图书
b* deletebook(b* head) {
    if (head == NULL)return head;
    b* node = find(head);
    if (node == NULL) return head;
    print(node);
    if (node == head) {
        head = head->next;
        free(node);
        printf("删除成功\n");
        return head;
    }
    b* p = head;
    while (p->next != NULL && p->next != node) {
        p = p->next;
    }
    if (p->next == node) {
        p->next = node->next;
        free(node);
        printf("删除成功\n");
    }
    return head;
}

//修改单个数据
b* change1(b* head, b* node, int c, int* num, float* num2, char str[]) {
    printf(COLOR_GREEN "请输入要修改的内容\n");
    if (c == 1 || c == 7 || c == 8) {
        int obj;
        scanf("%d", &obj);
        getchar();
        b* p = head;
        while (p != NULL) {
            if (obj == p->id && c == 1) {
                printf(COLOR_GREEN "该编号已经存在，请重新输入\n");
                return node;
            }
            p = p->next;
        }
        *num = obj;
    }
    else if (c == 2 || c == 3 || c == 4 || c == 5) {
        char str1[100];
        int a = fgets1(str1, sizeof(str1));
        strcpy(str, str1);
    }
    else {
        float num3;
        scanf("%f", &num3);
        getchar();
        *num2 = num3;
    }
    print(node);
    return node;
}

//修改图书
b* changebook(b* head) {
    b* node = find(head);
    if (node == NULL) return head;
    print(node);
    printf(COLOR_RED"请输入修改内容：\n");
    char choice[9][50] = {
        "选择如下",
        "1.id",
        "2.书名",
        "3.作者",
        "4.出版社",
        "5.IBNS号",
        "6.价格",
        "7.总库存",
        "8.可借数量",
    };
    for (int i = 0; i < 9; i++) {
        printf(COLOR_YELLOW"%s\n", choice[i]);
    }
    int c;
    scanf("%d", &c);
    getchar();
    switch (c) {
    case 1: {
        printf(COLOR_BLUE "当前id: " COLOR_RESET "%d\n", node->id);
        node = change1(head, node, 1, &node->id, NULL, NULL);
        break;
    }
    case 2: {
        printf(COLOR_BLUE "当前书名: " COLOR_RESET "%s\n", node->name);
        node = change1(head, node, 2, NULL, NULL, node->name);
        break;
    }
    case 3: {
        printf(COLOR_BLUE "当前作者: " COLOR_RESET "%s\n", node->author);
        node = change1(head, node, 3, NULL, NULL, node->author);
        break;
    }
    case 4: {
        printf(COLOR_BLUE "当前出版社: " COLOR_RESET "%s\n", node->publisher);
        node = change1(head, node, 4, NULL, NULL, node->publisher);
        break;
    }
    case 5: {
        printf(COLOR_BLUE "当前ISBN: " COLOR_RESET "%s\n", node->isbn);
        node = change1(head, node, 5, NULL, NULL, node->isbn);
        break;
    }
    case 6: {
        printf(COLOR_BLUE "当前价格: " COLOR_RESET "%.2f\n", node->price);
        node = change1(head, node, 6, NULL, &node->price, NULL);
        break;
    }
    case 7: {
        printf(COLOR_BLUE "当前库存: " COLOR_RESET "%d\n", node->total);
        node = change1(head, node, 7, &node->total, NULL, NULL);
        break;
    }
    case 8: {
        printf(COLOR_BLUE "当前可借数量: " COLOR_RESET "%d\n", node->available);
        node = change1(head, node, 8, &node->available, NULL, NULL);
        break;
    }
    }
    return head;
}

//借书
b* borrowbook(b* head) {
    b* node = find(head);
    if (node == NULL) {
        return head;
    }
    print(node);
    printf("请输入借阅数目：\n");
    while (1) {
        int num;
        scanf("%d", &num);
        getchar();
        if (num < 0) {
            printf("借阅数目不得小于零，请重新输入：\n");
            continue;
        }
        if (num > node->available) {
            printf("书籍不够，最多只能借阅%d本，请重新输入借阅数目：\n", node->available);
            continue;
        }
        node->available -= num;
        printf("借阅成功\n");
        print(node);
        break;
    }
    return head;
}

//还书
b* returnbook(b* head) {
    b* node = find(head);
    if (node == NULL)return head;
    print(node);
    while (1) {
        printf("请输入还书的数目：\n");
        int num;
        scanf("%d", &num);
        getchar();
        if (num <= 0) {
            printf("归还的数量不得小于等于零，请重新输入\n");
            continue;
        }

        if (node->available + num > node->total) {
            printf("输入数目错误，请重新输入：\n");
            continue;
        }
        else {
            node->available += num;
            printf("还书成功\n");
            print(node);
            break;
        }
    }
    return head;
}
//打印菜单
void printmenu() {
    printf(COLOR_CYAN BOLD "\n");
    printf("╔══════════════════════════════╗\n");
    printf("║         图书管理系统        ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  1. 显示所有图书            ║\n");
    printf("║  2. 添加图书                ║\n");
    printf("║  3. 查找图书                ║\n");
    printf("║  4. 删除图书                ║\n");
    printf("║  5. 修改图书                ║\n");
    printf("║  6. 借书                    ║\n");
    printf("║  7. 还书                    ║\n");
    printf("║  8. 保存并退出              ║\n");
    printf("╚══════════════════════════════╝\n");
    printf(" 请输入选择: " COLOR_RESET);
}