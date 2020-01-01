#include<bits/stdc++.h>
#define mp make_pair
typedef enum{pundefined='E',plow='<',phigh='>',pequal='='}pr;
/*typedef struct{
	enum {
		vt=0,vi
	} type=vt;
	std::string content;
	int num=0;
}symbols;
std::vector<symbols>rightpart;
std::pair<int,std::string>rules;
*/
std::map<std::pair<char,char>,pr>table;
std::set<char>vt;
std::vector<std::pair<char,std::string>>rules;
std::map<char,std::set<char>>firstvt,lastvt;
std::stack<std::pair<char,char> >sfirstvt,slastvt;
void init(){
	char c;
	std::string s;
	freopen("syn.txt","r",stdin);
	while(std::cin>>c>>s) rules.push_back(make_pair(c,s));
	fclose(stdin);

}
void mark(std::pair<char,char>pair,std::stack<std::pair<char,char> >&v,std::map<char,std::set<char> >&m){
	char p=pair.first;
	char a=pair.second;
	//printf("%c %c$\n",p,a);
	if(!m[p].count(a)){
		m[p].insert(a);
		v.push(pair);
	}
}
void getfirstvt(){
	//P->a and P->Qa
	for(auto r:rules)
		if(!isupper(r.second[0])) mark(std::mp(r.first,r.second[0]),sfirstvt,firstvt);
			else if(r.second[1]&&!islower(r.second[1])) mark(std::mp(r.first,r.second[1]),sfirstvt,firstvt);
	while(!sfirstvt.empty()){
		std::pair<char,char>pr;
		pr=sfirstvt.top();//(Q,a)
		sfirstvt.pop();
		for(auto i:rules) if(i.second[0]==pr.first) mark(std::make_pair(i.first,pr.second),sfirstvt,firstvt);
	}
}
void getlastvt(){//OK
	for(auto r:rules){
		auto p=r.first;
		auto a=r.second;
		int l=a.length();
		if(!isupper(a[l-1])) mark(std::mp(p,a[l-1]),slastvt,lastvt);
			else if((l>1) && (!isupper(a[l-2]))) mark(std::mp(p,a[l-2]),slastvt,lastvt);
	}
	while(!slastvt.empty()){
		std::pair<char,char>pr;
		pr=slastvt.top();
		slastvt.pop();
		for(auto i:rules) if(i.second.back()==pr.first) mark(std::mp(i.first,pr.second),slastvt,lastvt);
	}
}
void maketable(){//OK
	for(auto r:rules){
		auto s=r.second;
		for(int i=0;i<s.length()-1;++i){
			if( (!isupper(s[i])) && (!isupper(s[i+1])) ) table[std::make_pair(s[i],s[i+1])]=pequal;
			if(!isupper(s[i])&&s[i+2]&&!isupper(s[i+2])&&isupper(s[i+1])) table[std::make_pair(s[i],s[i+2])]=pequal;
			if(!isupper(s[i])&&isupper(s[i+1])) for(auto j:firstvt[s[i+1]]) table[std::make_pair(s[i],j)]=plow;
			if(isupper(s[i])&&!isupper(s[i+1])) for(auto j:lastvt[s[i]]) table[std::make_pair(j,s[i+1])]=phigh;
		}
	}
}
void getvt(){
	for(auto r:rules)
		for(int j=0;j<r.second.size();++j) if(!isupper(r.second[j])) vt.insert(r.second[j]);
}
int main(){
	init();
	for(auto i:rules) std::cout<<i.first<<" "<<i.second<<std::endl;
	getvt();
	for(auto i:vt)
		for(auto j:vt) table[std::make_pair(i,j)]=pundefined;
	getfirstvt();
	getlastvt();
	maketable();
	printf("---firstvt---\n");
	for(auto i:firstvt){
		std::cout<<i.first<<" ";
		for(auto j:i.second) std::cout<<j;
		printf("\n");
	}
	printf("---lastvt----\n");
	for(auto i:lastvt){
		std::cout<<i.first<<" ";
		for(auto j:i.second) std::cout<<j;
		printf("\n");
	}
	printf("----table----\n ");
	for(auto i:vt) printf("%c",i);
	printf("\n");
	for(auto i:vt){
		printf("%c",i);
		for(auto j:vt) printf("%c",table[std::make_pair(i,j)]);
		printf("\n");
	}
}