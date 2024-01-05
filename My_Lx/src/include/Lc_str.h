#include<cstdio>
#include<iostream>
#include<string>
namespace Lc {
	using namespace std;
	class Lc_str {
		private char* str;
		private long  len;
		private char* begin;
		private char* end;

		public Lc_str():str(nullptr),len(0),begin(nullptr),end(nullptr) {}
		
		public Lc_str(const char* cs){
			len = strlen(cs);
			str = new char[len+2];
			strcpy(cs,str);
			begin = &str[0];
			end = &str[len+1];
		}
		public Lc_str(char ct,int let) {
			len = let;
			str = new char [len+1]; 
			for (int it = 0; it < len; ++it)str[it]=ct;
			str[len] = '\0';
			begin = &str[0];
			end = &str[len];	
		}
		public Lc_str(char* let,char* cend) {
			if ((cend - let) > 256)Lc_str();
			len = cend - let;
			str = new char[len+1];
			for (char* ct = let, int ia = 0; ct != cend; ++ct, ++ia) {
				str[ia] = *ct;
			}
			begin = &str[0];
			end = &str[len];
		}



	};




}