#include <bits/stdc++.h>
using namespace std;
struct User{
	int uid;
	int pass;
	long long number;
	int state=1; //删除用
};
struct food{
	string fid;
	string fname;
	string fprice;
};
struct shop{
	string type;
	long long sid;
	string name;
	string pass;
	double score;
	double avgPrice;
	string address;
	string number;
	struct food food[60];
	int foodi=0;
	string comment[30];
	int commenti=0;
	int state=1;
};
struct order{
	long long uid;
	string Sname;
	string time;
	int state=1;
};
struct distance{
	int sid1;
	string name1;
	int sid2;
	string name2;
	double distance;
};
struct distance dis;
struct User user[40];
struct order order[400];
struct shop shop[1000];
int useri,shopi,orderi,disi;
unordered_map<string,int> shopmap;
void loadorder(){
	FILE *f=fopen("order.txt","r");
	if(f==NULL) {cout<<"文件不存在"; return;}
	char tmp1[1000],tmp[1000];
	fgets(tmp,1000,f);
	while(fscanf(f,"%lld %s %s",&order[orderi].uid,tmp,tmp1)!=EOF){
		order[orderi].Sname=tmp; order[orderi].time=tmp1;
		orderi++;
	}
	cout<<"订单数据加载完成\n";
	fclose(f);
}
void loadshop(){
	shop[shopi].name="郑州轻工业大学"; shop[shopi].sid=512324;
	shopmap["郑州轻工业大学\n"]=shopi;
	shopi++;
	FILE *f=fopen("shop.txt","r+");
	if(f==NULL) {cout<<"文件不存在"; return;}
	char tmp[1000];
	while(fgets(tmp,1000,f)){
		string s=tmp;
		int d=s.find(":");
		shop[shopi].type=s.substr(d+2);
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].sid= stol(s.substr(d+2));
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].name= s.substr(d+2);
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].pass= s.substr(d+2);
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].score= stod(s.substr(d+2));
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].avgPrice= stod(s.substr(d+2));
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].address= s.substr(d+2);
		fgets(tmp,1024,f);
		s=tmp;
		d=s.find(":");
		shop[shopi].number= s.substr(d+2);
		char *b;
		char *tmp1;
		while( fgets(tmp,1024,f)!=NULL && tmp[0]=='f'){
			tmp1= strtok_s(tmp,",",&b);
			s=tmp1; d=s.find(":");
			shop[shopi].food[shop[shopi].foodi].fid=s.substr(d+2);
			tmp1= strtok_s(NULL, ",", &b);
			s=tmp1; d=s.find(":");
			shop[shopi].food[shop[shopi].foodi].fname=s.substr(d+2);
			tmp1= strtok_s(NULL, ",", &b);
			s=tmp1; d=s.find(":");
			shop[shopi].food[shop[shopi].foodi].fprice=s.substr(d+2);
			shop[shopi].foodi++;
		}
		char *end;
		int size;
		if(tmp[0]=='C'){
			s=tmp; d=s.find(":");
			shop[shopi].comment[shop[shopi].commenti]=s.substr(d+2);
			shop[shopi].commenti++;
		}else {
			for(size=0;tmp[size];size++){
				
			}
			shopi++;
			fseek(f,long(-size-1),SEEK_CUR);
			continue;
		}
		while( (end=fgets(tmp,1024,f))!=NULL && tmp[0]=='C'){
			s=tmp;
			d=s.find(":");
			shop[shopi].comment[shop[shopi].commenti]=s.substr(d+2);
			shop[shopi].commenti++;
		}
		if (end==NULL) break;
		shopmap[shop[shopi].name]=shopi;
		for(size=0;end[size];size++){
		}
		shopi++;
		fseek(f,long(-size-1),SEEK_CUR);
	}
	fclose(f);
}
void lookuser(int idx){
	cout<<"当前用户的信息："<<user[idx].uid<<' '<<user[idx].pass<<' '<<user[idx].number<<endl;
}
void changeuser(int idx){
	cout<<"请重新输入用户密码和联系方式\n";
	cin>>user[idx].pass>>user[idx].number;
}
void deluser(int idx){
	user[idx].state=0;
	cout<<"删除成功\n";
	return;
}
int hashshopbyname(string name){
	if (shopmap.count(name+'\n')==1){
		return shopmap[(name+'\n')];
	}
	else {
		return -1;
	}
}
void lookorderuser(int idx){
	cout<<"该用户的订单为\n";
	for (int i = 0; i < orderi; ++i) {
		if(order[i].uid==user[idx].uid){
			cout<<order[i].Sname<<' '<<order[i].time<<endl;
		}
	}
}
void lookordershop(string name,int idx){
	cout<<"该用户该餐馆的订单为\n";
	for (int i = 0; i < orderi; ++i) {
		if(order[i].uid==user[idx].uid && order[i].Sname==name){
			cout<<order[i].time<<endl;
		}
	}
}
void addorder(string name,int idx){
	
	if(shopmap.count(name)==1){
		cout<<"请输入预定时间xx月xx日x餐\n";
		string data;
		cin>>data;
		order[orderi].uid=user[idx].uid; order[orderi].Sname=name; order[orderi].time=data;
		orderi++;
		cout<<"添加成功\n";
	}else{
		cout<<"无此商家\n";
	}
	
}
void shopre(){
	cout<<"请输入类型、特色菜、评论关键字\n";
	typedef pair<double,double> pii;
	vector<pii> v;
	string type,sp,com; cin>>type>>sp>>com;
	for (int i = 0; i < shopi; ++i) {
		int f=0;
		if(shop[i].type==type){
			v.push_back({shop[i].score,i});
			continue;
		}
		for (int j = 0; j < shop[i].foodi; ++j) {
			if (shop[i].food[j].fname==sp ){
				v.push_back({shop[i].score,i});
				f=1;
				break;
			}
		}
		if (f==1) continue;
		for (int j = 0; j < shop[i].commenti; ++j) {
			if(shop[i].comment[j].find(com)!=-1){
				v.push_back({shop[i].score,i});
				break;
			}
		}
	}
	sort(v.begin(),v.end());
	cout<<"已排序，符合要求的商家有:\n";
	for(int i=v.size()-1;i>=0;i--){
		int idx=v[i].second;
		cout<<"名字："<<shop[idx].name<<"地址："<<shop[idx].address<<shop[idx].score<<endl;
	}
}
void loaduser(){
	FILE *f=fopen("user1.txt","r");
	if(f==NULL) {cout<<"文件不存在"; return;}
	char tmp[100];
	fscanf(f,"%s",tmp);
	getchar();
	while(fscanf(f,"%d %d %lld",&user[useri].uid,&user[useri].pass,&user[useri].number)!=EOF){
		useri++;
	}
	cout<<"用户数据加载完成\n";
	fclose(f);
}
const int N=850;
double g[N][N];
unordered_map<string,int> dismap;

void lookshop(int idx){
	cout<<shop[idx].name<<shop[idx].address<<"评分："<<shop[idx].score<<endl;
}
void changeshop(int idx){
	cout<<"请重新输入类型、名称、密码、人均消费、地址、电话\n";
	cin>>shop[idx].type>>shop[idx].name>>shop[idx].pass>>shop[idx].avgPrice>>shop[idx].address>>shop[idx].number;
	cout<<"修改成功\n";
}
void delshop(int idx){
	shop[idx].state=0;
	cout<<"删除成功\n";
}
void lookshoporder(int idx){
	cout<<"该商家的订单为\n";
	for (int i = 0; i < orderi; ++i) {
		if( (order[i].Sname+'\n') == shop[idx].name && order[i].state==1 ){
			cout<<order[i].uid<<' '<<order[i].time<<endl;
		}
	}
}
void lookuserorder(int idx,int uid){
	cout<<"该用户在该商家的订单为\n";
	for (int i = 0; i < orderi; ++i) {
		if( (order[i].Sname+'\n') == shop[idx].name && uid==order[i].uid && order[i].state==1){
			cout<<order[i].time<<endl;
		}
	}
}
void delorder(int n,int idx){
	for (int i = 0; i < orderi; ++i) {
		if(n){
			if((order[i].Sname+'\n')==shop[idx].name&&order[i].state==1){
				n--;
				cout<<order[i].uid<<' '<<order[i].time<<endl;
				cout<<"订单已处理\n";
				order[i].state=0;
			}
		}else{
			break;
		}
	}
	cout<<"订单处理完成\n";
}
void saveshop(){
	FILE *f=fopen("shop.txt","wb");
	for (int i = 0; i < shopi; ++i) {
		if(shop[i].state==1)
			fwrite(&shop[i],sizeof(struct shop[0]),1,f);
	}
	cout<<"商家数据保存成功\n";
}
void saveorder(){
	FILE *f=fopen("order.txt","w+");
	fprintf(f,"%s","用户账号 \t    商家名称\t\t           预定时间\n");
	int ii=0;
	while(ii++<orderi){
		if(order[ii].state==1)
			fprintf(f,"%d %s %s\n",order[ii].uid,order[ii].Sname.c_str(),order[ii].time.c_str());
	}
	fclose(f);
	cout<<"数据已保存\n";
	cout<<"订单数据已保存\n";
}
void saveuser(){
	FILE *f=fopen("user1.txt","w+");
	fprintf(f,"%s","用户账号密码联系方式\n");
	int ii=0;
	while(ii++<useri){
		if(user[ii].state==1)
			fprintf(f,"%d %d %lld\n",user[ii].uid,user[ii].pass,user[ii].number);
	}
	fclose(f);
	cout<<"用户数据已保存\n";
}
void menu(){
	printf("*************************************\n");
	printf("**********请输入你想要的功能************\n");
	printf("*************1.用户登录***************\n");
	printf("*************2.商家登录***************\n");
	printf("*************0.退出******************\n");

	printf("************************************\n");
}
void usermenu(int idx){
	printf("*************************************\n");
	printf("**********请输入你想要的功能************\n");
	printf("*************1.查看个人信息************\n");
	printf("*************2.修改个人信息************\n");
	printf("*************3.注销个人信息************\n");
	printf("*************4.餐馆查询***************\n");
	printf("*************5.查询用户所有预订*********\n");
	printf("*************6.查询某餐馆的预订*********\n");
	printf("*************7.添加预订***************\n");
	printf("*************8.餐馆推荐***************\n");
	printf("*************0.退出******************\n");
	printf("************************************\n");
	int op;
	loadshop();
	cout<<"商家数据加载完成\n";
	loadorder();
	int t=0,tt=0;
	while(cin>>op){
		if(op==1){
			lookuser(idx);
		}else if(op==2){
			changeuser(idx);
		}else if(op==3){
			deluser(idx);
		}else if(op==4){
			cout<<"请输入餐馆的名字\n";
			string name;cin>>name;
			if(shopmap.count(name+'\n')==-1) cout<<"无此商家\n";
			else {
				int idx=shopmap[name+'\n'];
				cout<<shop[idx].type<<' '<<shop[idx].name<<' '<<shop[idx].score<<' '<<shop[idx].avgPrice<<' '<<shop[idx].address<<' '<<shop[idx].number<<endl;
			}
			
		}else if(op==5){
			lookorderuser(idx);
		}else if(op==6){
			cout<<"请输入餐馆名字\n";
			string name; cin>>name;
			lookordershop(name,idx);
		}else if(op==7){
			cout<<"请输入餐馆名字\n";
			string name; cin>>name;
			addorder(name+'\n',idx);
		}else if(op==8){
			shopre();
		}else if(op==0){

			exit(0);
		}else{
			cout<<"请重新输入";
		}
	}
}
void shopmenu(int idx){
	printf("*************************************\n");
	printf("**********请输入你想要的功能************\n");
	printf("*************1.查询餐馆信息************\n");
	printf("*************2.修改餐馆信息************\n");
	printf("*************3.注销餐馆信息************\n");
	printf("*************4.查询餐馆所有预订********\n");
	printf("*************5.查询某用户预订**********\n");
	printf("*************6.处理预订***************\n");
	printf("*************0.退出******************\n");
	printf("************************************\n");
	int op;
	loadorder();
	while(cin>>op){
		if(op==1){
			lookshop(idx);
		}else if(op==2){
			changeshop(idx);
		}else if(op==3){
			delshop(idx);
		}else if(op==4){
			lookshoporder(idx);
		}else if(op==5){
			cout<<"请输入用户的id\n";
			int uid; cin>>uid;
			lookuserorder(idx,uid);
		}else if(op==6){
			cout<<"请输入要处理的订单数:";
			int n;cin>>n;
			delorder(n,idx);
		}else if(op==0){

			exit(0);
		}else{
			cout<<"请重新输入\n";
		}
	}
}
void LoginUser(){
	loaduser();
	cout<<"**************************************\n";
	cout<<"***********输入账号和密码请按1***********\n";
	cout<<"************个人用户注册请按2************\n";

	int op; cin>>op;
	if(op==1){
		int id,f=0; int pass;
		cout<<"请输入账号和密码：\n";
		cin>>id>>pass;
		for(int i=0;i<useri;i++){
			if (user[i].uid==id && user[i].pass==pass) {
				f=1;
				id=i;
			}
		}
		if(f==1){
			cout<<"登录成功\n";
			usermenu(id);
		} else{
			cout<<"查无此人\n";
		}
	}else if (op==2){
		cout<<"请输入账号、密码、联系方式\n";
		cin>>user[useri].uid>>user[useri].pass>>user[useri].number;
		useri++;
		cout<<"注册成功,\n";
		LoginUser();
	}else{
		cout<<"输入错误,返回主页面\n";
	}
}
void LoginShop(){
	loadshop();
	cout<<"商家数据加载完成\n";
	cout<<"**************************************\n";
	cout<<"***********请输入账号和密码***********\n";

	
	long long id,f=0; long long pass; cin>>id>>pass;
	for(int i=0;i<shopi;i++){
		if (shop[i].sid==id&& stol(shop[i].pass)==pass) {
			f=1;
			id=i;
		}
	}
	if(f==1){
		cout<<"登录成功\n";
		shopmenu(id);
	}else{
		cout<<"无此商家\n";
	}
	
}
int main(){

	int op;
	do{
		menu();
		cin>>op;
		switch (op)
		{
		case 1:
			LoginUser();
			break;
		case 2:
			LoginShop();
			break;
		case 0:
			printf("退出成功!\n");
			break;
			default:
				printf("选择错误,请重新选择!\n");
				break;
		}
	}while (op!=0);
	return 0;
}
