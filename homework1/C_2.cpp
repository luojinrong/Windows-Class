#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {//存储日期，yy、mm、dd分别为年月日
	int yy, mm, dd;
};

struct customer {//记录顾客信息
	char name[50], Phone[20];
	struct customer *next;
};

struct info {//预定信息
	struct customer *cus;//顾客信息
	struct data advan_da, bre_da;//预定房间日期，预定早餐日期
	int bre, gar, room;//是否需要早餐及车库，房间号
	float money;//所需金额
	struct info *next;
};

struct adv {//旅馆房间预定情况
	struct data d;
	int f[5];
}a[30];//只存储近一个月
int mon[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//每月的天数
struct info *i_head;
struct customer *c_head;
struct data now;//当前时间

int cal_d(struct data now, struct data ad);//计算两时间间隔天数（0<间隔<30的时候）

void pre();//预处理

void op_1();

void op_2();

void op_3();

void op_4(struct data now);

void op_5();

int main() {
	i_head = NULL;
	c_head = NULL;
	int menu;
	pre();
	while (scanf("%d", &menu), menu) {
		switch (menu)
		{
		case 1:
			op_1();
			break;
		case 2:
			op_2();
			break;
		case 3:
			op_3();
			break;
		case 4:
			op_4(now);
			break;
		case 5:
			op_5();
			break;
		default:
			printf("操作非法，请重新输入！\n");
			break;
		}
	}
}

int cal_d(struct data now, struct data ad) {
	if (now.yy * 10000 + now.mm * 100 + now.dd > ad.yy * 10000 + ad.mm * 100 + ad.dd) {//判断时间先后
		return -1;
	}
	else {
		if (now.yy != ad.yy) {
			if (now.mm != 12 && ad.mm != 1) {
				return -1;
			}
			else {
				return (31 - now.dd + ad.dd);
			}
		}
		else if (ad.mm - now.mm > 1) {
			return -1;
		}
		else if (ad.mm - now.mm == 1) {
			return (mon[now.mm] - now.dd + ad.dd);
		}
		else {
			return ad.dd - now.dd;
		}
	}
}

void pre() {
	int flag_r = 0;
	printf("请输入当前日期（年月日以空格隔开）：");
	while (!flag_r) {
		scanf("%d%d%d", &now.yy, &now.mm, &now.dd);
		if (now.yy % 400 == 0 || (now.yy % 400 != 0 && now.yy % 4 == 0)) {//计算这一年二月天数
			mon[2] = 28;
		}
		if (now.mm < 1 || now.mm>12) {//月份不合法
			;
		}
		else if (now.dd<1 || now.dd>mon[now.mm]) {//天数不合法
			;
		}
		else {//日期合法
			flag_r = 1;
		}
		if (!flag_r) {
			printf("日期非法，请重新输入：");
		}
	}
	for (int i = 0; i < 30; i++) {//对近30天房间预定情况初始化
		a[i].d.yy = now.yy;
		a[i].d.mm = now.mm;
		a[i].d.dd = now.dd + i;
		if (a[i].d.dd > mon[a[i].d.mm]) {
			a[i].d.dd -= mon[a[i].d.mm];
			a[i].d.mm++;
			if (a[i].d.mm > 12) {
				a[i].d.mm -= 12;
				a[i].d.yy++;
			}
		}
		memset(a[i].f, 0, sizeof(int));
	}
	printf("\n请选择：\n0：退出系统\n1：新建顾客信息（姓名电话相同则视为同一顾客）\n2：打印所有顾客信息\n3：预定房间（预定房间前需先登记，且同一顾客只可同时预约一次）\n4：预定早餐（需先预定房间）\n5：打印所有预定信息\n\n");
}

void op_1() {
	printf("开始建立一个新的顾客信息：\n");
	printf("请输入顾客姓名及电话（以空格隔开）：");
	struct customer *tmp_1 = (struct customer*)malloc(sizeof(struct customer));
	struct customer *tmp = c_head;
	int flag = 0;
	char n[50], P[20];
	scanf("%s%s", n, P);
	while (tmp) {//检查用户是否存在
		if (!strcmp(n, tmp->name) && !strcmp(P, tmp->Phone)) {
			printf("该用户信息已存在，请勿重复录入！\n");
			flag = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (!flag) {//不存在用户，新建
		tmp_1->next = c_head;
		c_head = tmp_1;
		strcpy(tmp_1->name, n);
		strcpy(tmp_1->Phone, P);
		printf("新建成功！\n");
	}
}

void op_2() {
	struct customer *tmp_2 = c_head;
	printf("所有已记录顾客信息如下：\n");
	while (tmp_2) {
		printf("姓名：%s 电话：%s\n", tmp_2->name, tmp_2->Phone);
		tmp_2 = tmp_2->next;
	}
	printf("打印完毕！\n");
}

void op_3() {
	printf("预定一个房间：\n");
	struct customer *ctmp = c_head;
	struct info *itmp = i_head;
	char n_3[50], P_3[20];
	int flag_3 = 0;
	printf("请输入预定人姓名及电话：");
	scanf("%s%s", n_3, P_3);
	while (itmp) {//查找该顾客是否存在预定信息
		if (!strcmp(n_3, itmp->cus->name) && !strcmp(P_3, itmp->cus->Phone)) {
			flag_3 = 1;
			break;
		}
		itmp = itmp->next;
	}
	if (!flag_3) {
		while (ctmp) {//查找是否存在该顾客信息
			if (!strcmp(n_3, ctmp->name) && !strcmp(P_3, ctmp->Phone)) {
				flag_3 = 1;
				break;
			}
			ctmp = ctmp->next;
		}
		if (flag_3) {//为该顾客创建预定信息
			itmp = (struct info*)malloc(sizeof(struct info));
			itmp->money = 0;
			itmp->next = i_head;
			i_head = itmp;
			i_head->cus = ctmp;
			/*strcpy(i_head->cus->name, ctmp->name);
			strcpy(i_head->cus->Phone, ctmp->Phone);*/
			int ri_f = 0, index;//日期是否合法
			printf("请输入预定日期：\n");
			while (scanf("%d%d%d", &itmp->advan_da.yy, &itmp->advan_da.mm, &itmp->advan_da.dd)) {
				for (int i = 0; i < 30; i++) {
					if (itmp->advan_da.yy == a[i].d.yy&&itmp->advan_da.mm == a[i].d.mm&&itmp->advan_da.dd == a[i].d.dd) {
						ri_f = 1;
						index = i;
						break;
					}
				}
				if (ri_f) {
					while (printf("请输入所需房间类型（1表示单人间，3表示双人）：")) {
						scanf("%d", &itmp->room);
						if (itmp->room != 1 && itmp->room != 3) {
							printf("输入非法！");
						}
						else {
							if (itmp->room == 1) {//判断单人房是否住满
								if (a[index].f[1] == 0) {
									a[index].f[1] = 1;
									itmp->room = 1;
									itmp->money += 49;
								}
								else if (a[index].f[2] == 0) {
									a[index].f[2] = 1;
									itmp->room = 2;
									itmp->money += 49;
								}
								else {
									printf("当日单人间住满！订单已取消！\n");
									return;
								}
							}
							else {//判断双人间是否住满
								if (a[index].f[3] == 0) {
									a[index].f[3] = 1;
									itmp->room = 3;
									itmp->money += 169;
								}
								else if (a[index].f[4] == 0) {
									a[index].f[4] = 1;
									itmp->room = 4;
									itmp->money += 169;
								}
								else {
									printf("当日双人间住满！订单已取消！\n");
									return;
								}
							}
							while (printf("订房成功！您的房间号为：%d\n是否需要车库？（1需要，否则填0）（早餐另填）：", itmp->room)) {
								scanf("%d", &itmp->gar);
								if (itmp->gar != 0 && itmp->gar != 1) {
									printf("输入非法！请重新输入（1需要，否则填0）：");
								}
								else {
									if (itmp->gar == 1) {
										itmp->money += 15;
										printf("车库已安排！\n");

									}
									printf("预定成功！\n");
									return;
								}
							}
						}
					}

				}
				else {
					printf("非法预定日期！（仅支持当前时间30天内的预约）,请重新输入日期：\n");
				}
			}
		}
		else {
			printf("未找到该顾客信息，请先创建！\n");
		}
	}
	else {
		printf("该顾客已存在预定记录，无法再次预定！\n");
	}
}

void op_4(struct data now) {
	printf("预定早餐：\n");
	printf("请输入顾客姓名及电话：");
	char n_4[50], P_4[20];
	int flag_4 = 0;
	struct data ad;
	scanf("%s%s", n_4, P_4);
	struct info *i_tmp_4 = i_head;
	while (i_tmp_4) {//检查该顾客是否存在订房记录
		if (!strcmp(n_4, i_tmp_4->cus->name) && !strcmp(P_4, i_tmp_4->cus->Phone)) {
			flag_4 = 1;
			break;
		}
		i_tmp_4 = i_tmp_4->next;
	}
	if (flag_4) {
		while (printf("请输入预定日期：")) {
			scanf("%d%d%d", &i_tmp_4->bre_da.yy, &i_tmp_4->bre_da.mm, &i_tmp_4->bre_da.dd);
			if (cal_d(now, i_tmp_4->bre_da) == -1 || cal_d(now, i_tmp_4->bre_da) > 30) {
				printf("输入日期非法，请重新输入");
			}
			else {
				i_tmp_4->money += 19.9;
				i_tmp_4->bre = 1;
				printf("预定成功！\n");
				break;
			}
		}
	}
	else {
		printf("未找到该顾客预定信息，请先预定房间！\n");
	}
}

void op_5() {
	printf("所有已预定信息如下：\n");
	struct info *i_tmp_5 = i_head;
	while (i_tmp_5) {
		printf("姓名：%s\n电话：%s\n预定日期：%d/%d/%d\n预定金额：%.2f\n房间号：%d\n是否包含早餐：%s\n是否包含车库：%s\n\n", i_tmp_5->cus->name, i_tmp_5->cus->Phone, i_tmp_5->advan_da.yy, i_tmp_5->advan_da.mm, i_tmp_5->advan_da.dd, i_tmp_5->money, i_tmp_5->room, i_tmp_5->bre==1 ? "是" : "否", i_tmp_5->gar==1 ? "是" : "否");
		i_tmp_5 = i_tmp_5->next;
	}
	printf("打印完毕！\n");
}