#pragma once
#include<cstdio>
#include<string>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>

namespace Lc_name{
	using namespace std;	
	using ulong=unsigned long;

	class Lc_str{
	public:
		struct Pack{ char* first; char* last;};
	private:
		ulong leng;
		char* strs;
		const ulong cs_len=1024;

#define set_null(set_cs,set_le){set_cs[set_le]='\0';}

#define str_cpy(cpy_sa,cpy_sb,cpy_len){\
	ulong cpy_ua=0;\
	while(cpy_ua<cpy_len){cpy_sa[cpy_ua]=cpy_sb[cpy_ua++];}\
}

#define S_NLL set_null(strs,leng)

#define char_str(ch_sa,ch_sb){ch_sa[0]=ch_sb;ch_sa[1]='\0';}

#define str_cat(cat_sa,cat_sb){\
	ulong cat_len=0;\
	while(cat_sa[cat_len]!='\0'){ ++cat_len; };\
	ulong cat_lea=strnlen_s(cat_sb,cs_len);\
	for(ulong cat_ua=0; cat_ua<cat_lea; ++cat_ua)\
	{ cat_sa[cat_ua+cat_len]=cat_sb[cat_ua];}\
}

#define malloc_st(ma_cs,ma_le){ma_cs=(char*)malloc(sizeof(char)*(ma_le+1));}
#define free_st(fr_cs){free(fr_cs);}
#define MALL malloc_st(strs,leng)


	public:		
		Lc_str();
		Lc_str(char ch,ulong le=0);
		Lc_str(const char* cs, ulong le=0);
		Lc_str(const char* first,const char* last);
		Lc_str(const string& st);
		Lc_str(const Lc_str& lc);
		Lc_str(Lc_str&& lc);

		~Lc_str(){ free_st(strs); leng=0;  }
		char* begin(){ return strs; }
		char* end(){ return strs+leng; }
		const char* begin_con()const{ return strs; }
		const char* end_con()const{ return strs+leng; }
		char* re_index(ulong le){ if(le>leng)le=0; return strs+le;}		
		const char* re_index_con(ulong le)const{
			if(le>leng)le=0;
			return strs+le;	}//´Ë´¦·µ»Ø
		ulong length()const{ return leng; }
		ulong size()const{ return leng;	 }
		Lc_str& operator=(const char* cs);
		Lc_str& operator=(const Lc_str& lc);
		Lc_str& operator=(Lc_str&& lc);

		bool operator==(const Lc_str& lc)const;
		bool operator==(const char* cs)const;
		bool operator!=(const Lc_str& lc)const;
		bool operator!=(const char* cs)const;
		bool operator>(const Lc_str& lc)const;
		bool operator<(const Lc_str& lc)const;

		Lc_str operator+(char ch)const;
		Lc_str operator+(const char* cs)const;
		Lc_str operator+(const Lc_str& lc)const;
		Lc_str operator-(char ch)const;
		Lc_str operator-(const char* cs)const;
		Lc_str operator-(const Lc_str& lc)const;
		Lc_str operator*(ulong la)const;
		Lc_str operator/(char ch)const;
		Lc_str operator/(const char* cs)const;
		Lc_str operator/(const Lc_str& lc)const;
		
		char* re_index(char ch,ulong le=0);
		const char* re_index_con(char ch,ulong le=0)const;
		bool find_char(char ch,ulong le=0)const;
		bool find_str(const char* cs,ulong le=0)const;
		bool find_str(const Lc_str& lc,ulong le=0)const;

		Pack re_find_str(const char* cs,ulong le=0);
		const Pack re_find_str(const char* cs,ulong le=0)const;
		Pack re_find_str(const Lc_str& lc,ulong le=0);
		const Pack re_find_str(const Lc_str& lc,ulong le=0)const;

		Lc_str remove_char(char ch, ulong le=0)const;
		Lc_str remove_str(const char* cs,ulong le=0)const;
		Lc_str remove_str(const Lc_str& lc,ulong le=0)const;

		void show()const;


	
	
	
	
	


	public:
		friend ostream& operator<<(ostream& out,const Lc_str& ls){
			out<<ls.strs<<endl;
			return out;
		}
	};




}

