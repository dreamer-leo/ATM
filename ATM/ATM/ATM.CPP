#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
int find;
int find1;//用于转账查找对方账号
int xiao;//用于注销函数
//声明指针变量
FILE *fp;
//定义全局的结构体
struct bank
	{
	    char name[20],password1[10];//姓名，密码
		int account;//账号
		double money;//余额
	}user,t;
//密码函数                                  
void inputPassword(char pass[])
{
	int a=0;
	char pa;
	while(1)
	{
		pa=getch();
		if(pa!='\r')
		{
			if(pa!='\b')
			{
				pass[a]=pa;
				a++;
				printf("*");
			}
			else
			{
				if(a>0)
				{
					a--;
					printf("\b \b");
				}
			}
		}
		else
		{
			break;
		}
		pass[a]='\0';		
	}
	printf("\n");
}
                    
//注册函数
void regist()
{	
	printf("\n\n\n\t\t\t您正在执行的是用户注册服务\n");
	char password2[10];//确认密码字符数组
	fp=fopen("atm.txt","ab+");
	if(fp==NULL)
	{
		printf("\t\t\t打开文件失败");
		return;
	}
	printf("\t\t\t欢迎使用ATM系统\n");
	printf("\t\t\t请输入您的姓名：");
	fflush(stdin);//清除键盘缓冲区的回车符
    gets(user.name);
	printf("\t\t\t该用户名是：%s\n",user.name);
	while(1)
	{
		while(1)
		{
			int length;
	        printf("\t\t\t请输入密码：");
	        fflush(stdin);//清除键盘缓冲区的回车符
	        inputPassword(user.password1);            
	    	length=strlen(user.password1);
	        if(length==6)break;
	    	else
			    printf("\n\n\t\t\t密码格式必须为6位数，请重新输入\n");
		}
	    printf("\n\n\t\t\t请输入确认密码");
     	fflush(stdin);
    	inputPassword(password2);
 	    if(strcmp(user.password1,password2)==0)break;
		else
			printf("\n\n\t\t\t两次输入的密码不一致，请重新输入\n");
	}
	rewind(fp);//将文件指针定位到文件开头 
	if(fread(&t,sizeof(t),1,fp)==1)
	{
		fseek(fp,0-sizeof(user),2);		
		fread(&t,sizeof(t),1,fp);//读取最后一条记录
		user.account=t.account+1;
	}
	else
	{
		user.account=2018001;
	}
	fseek(fp,0,2);
	fwrite(&user,sizeof(struct bank),1,fp);
	fclose(fp);
	printf("\n\n\t\t\t注册成功");
	double money=0;
	printf("\n\n\t\t\t您的账户余额为%lf",user.money);
	printf("\n\n\t\t\t您的账号为:%d",user.account);
    return;
}

//余额查询函数
void selectMoney()
{
	system("cls");
	printf("\n\n\t\t\t您正在使用余额查询服务");
	printf("\n\n\t\t\t您的账户余额为：%lf",t.money);
}
//存款函数
void depositMoney()
{
	system("cls");
	int cun;
	printf("\n\n\t\t\t您正在使用存款服务");
	printf("\n\n\t\t\t请输入存款金额");
	scanf("%d",&cun);
	t.money=t.money+cun;
	fp=fopen("atm.txt","r+");
	fseek(fp,0-sizeof(t),1);
	fwrite(&t,sizeof(t),1,fp);
	fclose(fp);
	printf("\n\n\t\t\t存款成功");
}
//取款函数
void getMoney()
{
	system("cls");
	int qu;
	printf("\n\n\t\t\t您正在使用取款服务");
	printf("\n\n\t\t\t请输入取款金额：");
	scanf("%d",&qu);
	if(t.money>=qu)
	{
		t.money=t.money-qu;//修改内存
		fp=fopen("atm.txt","r+");
	
		fseek(fp,0-sizeof(t),1);
		fwrite(&t,sizeof(t),1,fp);
		fclose(fp);
		printf("\n\n\t\t\t取款成功");
	}
	else
	{
		printf("\n\n\t\t\t余额不足");
	}
}
//转账函数 
void zhuanzhang()
{
    system("cls");
	printf("\n\n\t\t\t您正在使用转账服务");
	int account3,f=0,zhu;
    struct bank temp;
    int n=ftell(fp);//保存指针当前位置 
	printf("\n\n\t\t\t请输入对方的账号");
	scanf("%d",&account3);
	fp=fopen("atm.txt","r");
    rewind(fp);
	while(fread(&temp,sizeof(temp),1,fp)==1)
	{
		if(account3==temp.account)
		{
			f=1;
			break;
		}
	}
	fclose(fp);
	if(f==1)
	{
		printf("\n\n\t\t\t请输入转账金额");
		scanf("%d",&zhu);
		if(t.money>=zhu)
		{
			t.money=t.money-zhu;
			temp.money=temp.money+zhu; 
			//修改文件数据
			fp=fopen("atm.txt","r+");
                    fseek(fp,0-sizeof(temp),1);
                    fwrite(&temp,sizeof(temp),1,fp);
                    fseek(fp,n-sizeof(t),0);
                    fwrite(&t,sizeof(t),1,fp);
					fclose(fp);
			printf("\n\n\t\t\t转账成功");
		}
		else
		{
			printf("\n\n\t\t\t余额不足");
		}
	}
	else
	{
		printf("\n\n\t\t\t不存在此账号");
	}
}
//修改密码函数
void revise()
{
	system("cls");
	int i;
	char password1[10],password2[10],password3[10];
	printf("\n\n\t\t\t您正在使用修改密码服务");
	for(i=0;i<3;i++)
	{
		printf("\n\n\t\t\t请输入旧密码：");
		inputPassword(password1);
		if(strcmp(password1,t.password1)==0)
		{
			break;
		}
		else
		{
			printf("\n\n\t\t\t旧密码输入错误，请重新输入");
		}
	}
	if(i<3)
	{
		while(1)
		{
			printf("\n\n\t\t\t请输入新密码");
			inputPassword(password2);
			printf("\n\n\t\t\t请确认密码");
			inputPassword(password3);
			fp=fopen("atm.txt","r+");
			if(strcmp(password2,password3)==0)
			{
				strcpy(t.password1,password3);
                        fseek(fp,0-sizeof(t),1);
                        fwrite(&t,sizeof(t),1,fp);
						fclose(fp);
				printf("\n\n\t\t\t修改成功");
				break;
			}
			else
			{
				printf("\n\n\t\t\t两次密码输入不一致，请重新输入");
			}
		}
	}
	else
	{
		printf("\n\n\t\t\t三次密码输入都错误，吞卡中……");
	}
}
//注销函数
int cancel()
{
	system("cls");
	char x;
	printf("\n\n\t\t\t您正在使用注销服务");
	printf("\n\n\t\t\t您要注销的账号是：%d\n",t.account);
	printf("\n\n\t\t\t您是否真的要注销此账号？注销【y】,不注销【n】:");
	fflush(stdin);
	scanf("%c",&x);
	if(x=='y'||x=='Y')
	{
		printf("\n\n\t\t\t正在对账号%d注销",t.account);
		xiao=1;
	}
	else
	{
		printf("\n\n\t\t\t不对此账号注销，返回服务界面",t.account);
	}
	return xiao;
}
//退出系统函数
void quit();
//服务界面函数
void service()
{   char choice;
    while(1)
   {
    system("cls");
	printf("\n\n\n\t\t\t您正在使用服务功能界面");
	printf("\n\n\t\t\ta、余额查询");
	printf("\n\n\t\t\tb、存款");
	printf("\n\n\t\t\tc、取款");
	printf("\n\n\t\t\td、转账");
	printf("\n\n\t\t\te、修改密码");
	printf("\n\n\t\t\tf、注销");
	printf("\n\n\t\t\tg、退出系统");
	printf("\n\n\t\t\t请选择服务种类");
	fflush(stdin);
	scanf("%c",&choice);
	int xiao;
	switch(choice)
	{
	case'a':
	case'A':selectMoney();break;
	case'b':
	case'B':depositMoney();break;
	case'c':
	case'C':getMoney();break;
	case'd':
	case'D':zhuanzhang();break;
	case'e':
	case'E':revise();break;
	case'f':
	case'F':xiao=cancel();if(xiao==1) return;break;
	case'g':
	case'G':quit();break;
	}
	printf("\n\n\t\t\t按任意键继续……");
	getch();
  }
}
//登录函数
void login()
{
	fp=fopen("atm.txt","rb+");                        
	if(fp==NULL)
	{
		printf("\n\n\t\t\t打开失败\n");
		return;
	}
	printf("\n\n\n\t\t\tATM系统为您服务");
	int account,z=0;
	char password[10];
	
	printf("\n\n\n\t\t\t请输入您的账号：");
	scanf("%d",&account);
	while(fread(&t,sizeof(t),1,fp)==1)
	{
		if(account==t.account)
		{
			z=1;
			break;
		}
	}
	if(z==1)
	{
		int j;
		for(j=0;j<3;j++)
		{
			printf("\n\n\n\t\t\t请输入您的密码：");
			inputPassword(password);
			if(strcmp(password,t.password1)==0)
			{
				printf("\n\n\t\t\t登陆成功");
				service();
				break;
			}
		}
		if(j==3)
		{
			printf("\n\n\n\t\t\t三次密码都不成功,吞卡中……");
		}
	}
	else
	{
		printf("\n\n\t\t\t没有此账号");
	}
	fclose(fp);
}
//退出系统函数
void quit()
{
	system("cls");
	printf("\n\n\n\t\t\tATM系统为您服务");
	printf("\n\n\n\t\t\t正在退出，请稍等\n");
	exit(0);//退出系统函数，包含在头文件stdlib中
	return;
}
//主函数
int main()
{
	int m;
	for(m=0;m<=100;m++)
	{
		printf("\n\n\n\t\t\t欢迎使用ATM系统\n");          
		printf("\t\t\t正在进入界面，请稍等\n");           
		int i,t;
	    for(i=1;i<=t;i++)
		{
		    printf(".");/*loading*/
		}
		t++;
		if(t==10)t=1;
		printf("%d%%",m);
		int b;
		for(b=0;b<10000;b++);//延迟
	    system("cls"); 
	}
	while (1)
	 {
	     char choice;
		 system("cls");
	     printf("\n\n\n\t\t\tATM系统正在为您服务\n");
	     printf("\t\t\t服务【a】：用户注册\n");
	     printf("\t\t\t服务【b】：用户登陆\n");
	     printf("\t\t\t服务【c】：退出系统\n");
	     printf("\t\t\t请在三个服务中选择您需要的服务");
		 fflush(stdin);//清楚键盘缓冲区的回车符
		 scanf("%c",&choice);
		 if(choice=='a'||choice=='A')
		 {
			 regist();           
		 }
		 else if(choice=='b'||choice=='B')
		 {
			 login();
		 }
		 else if(choice=='c'||choice=='C')
		 {
			 quit();
		 }
		 else
		 {
			 printf("\t\t\t您选择的服务类型错误，请重新选择");
		 }
		 printf("\n\t\t\t按任意键继续");
		 getch();//不经过键盘缓冲区的字符函数
	}
}
