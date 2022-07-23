#include"Lc_str.h"
namespace Lc_name{



	Lc_str::Lc_str(){		
		leng=0;
		//malloc_st(strs,leng);
		MALL;
		S_NLL;
	}

	Lc_str::Lc_str(char ch, ulong le){		
		if(le==0){
			leng=1;
			//malloc_st(strs,leng);
			MALL;
			char_str(strs,ch);
			S_NLL;			
		}else{
			leng=le;
			MALL;
			for(ulong ua=0; ua<leng;++ua){
			strs[ua]=ch;
			}
			S_NLL;
		}
	}

	Lc_str::Lc_str(const char* cs, ulong le){
		if(le!=0)leng=le;
		else leng=strnlen_s(cs, cs_len);
		
		//strs=new char[leng+1];
		MALL;
		str_cpy(strs,cs,leng);
		S_NLL;
	}

	Lc_str::Lc_str(const char* first, const char* last){	
		if(first==last) Lc_str(); 
		else{
			leng=last-first;
			if(leng>(cs_len*2))exit(-1);
			//strs=new char[leng+1];
			MALL;
			ulong ua=0;
			for(const char* ap=first; ap<last; ++ap){
				strs[ua]=*ap;
				++ua;
			}
			S_NLL;
		}
	}

	Lc_str::Lc_str(const string& st){
		
		leng=st.length();
		//strs=new char[leng+1];
		MALL;
		const char* cs=st.c_str();
		str_cpy(strs,cs,leng);
		S_NLL;
	}


	Lc_str::Lc_str(const Lc_str& lc){
		
		leng=lc.leng;		
		//strs=new char[leng+1];
		MALL;
		const char* cp=lc.strs;
		str_cpy(strs,cp,leng);
		S_NLL;
	}

	Lc_str::Lc_str(Lc_str&& lc){	
		
		leng=lc.leng;
		strs=lc.strs;
		lc.leng=0;
		lc.strs=nullptr;	
	}
		
	Lc_str& Lc_str::operator=(const char* cs){
		if(*this==cs)return *this;
		free_st(strs);
		leng=strnlen_s(cs,cs_len);
		//strs=new char[leng+1];
		MALL;
		str_cpy(strs,cs,leng);
		S_NLL;
		return *this;
	}

	Lc_str& Lc_str::operator=(const Lc_str& lc){
		if(this==&lc)return *this;
		//delete[] strs;
		free_st(strs);
		leng=lc.leng;
		//strs=new char[leng+1];
		MALL;
		const char* cp=lc.strs;
		str_cpy(strs,cp,leng);
		S_NLL;
		return *this;
	}

	Lc_str& Lc_str::operator=(Lc_str&& lc){
		if(&lc==this)return *this;
		free_st(strs);
		strs=lc.strs;
		leng=lc.leng;
		lc.strs=nullptr;
		lc.leng=0;
		return *this;
	}

	bool Lc_str::operator==(const Lc_str& lc) const{
		if(lc.leng!=leng)return false;
		return strncmp(strs,lc.strs,leng)==0;
	}

	bool Lc_str::operator==(const char* cs) const{
		if(leng!=strnlen_s(cs,cs_len))return false;
		return strncmp(cs,strs,leng)==0;
	}

	bool Lc_str::operator!=(const Lc_str& lc) const{
		if(leng!=lc.leng)return true;
		return strncmp(strs,lc.strs,leng)!=0;
	}

	bool Lc_str::operator!=(const char* cs) const{
		if(leng!=strnlen_s(cs,cs_len))return true;
		return strncmp(cs,strs,leng)!=0;
	}

	bool Lc_str::operator>(const Lc_str& lc) const{
		if(leng<lc.leng)return false;
		return strncmp(strs, lc.strs,leng)>0;
	}

	bool Lc_str::operator<(const Lc_str& lc) const{
		if(leng>lc.leng)return false;
		return strncmp(strs,lc.strs,leng)<0;
	}

	Lc_str Lc_str::operator+(char ch) const{
		if(ch==' '||ch=='\0')return Lc_str(*this);
		ulong len=leng+1;
		char* cs=new char[len+1];
		char* cm=new char[2];		
		char_str(cm,ch);		
		str_cpy(cs,strs,leng);		
		set_null(cs,leng);
		str_cat(cs,cm);
		set_null(cs,len);
		Lc_str lc(cs);		
		delete[] cs;
		delete[] cm;
		return lc;		
	}

	Lc_str Lc_str::operator+(const char* cs) const{
		if(strnlen_s(cs,cs_len)==0)return Lc_str(*this);
		ulong len=leng+strnlen_s(cs,cs_len);
		char* csp=new char[len+1];		
		str_cpy(csp,strs,leng);
		set_null(csp,leng);
		str_cat(csp,cs);
		set_null(csp,len);
		Lc_str lc(csp);
		delete[] csp;
		return lc;
	}

	Lc_str Lc_str::operator+(const Lc_str& lc) const{
		if(lc.leng==0)return Lc_str(*this);
		ulong len=leng+lc.leng;
		char* csp=new char[len+1];
		
		str_cpy(csp,strs,leng);
		set_null(csp,leng);
		str_cat(csp,lc.strs,lc.leng);
		set_null(csp,len);
		Lc_str lcc(csp);
		delete[] csp;
		return lcc;
	}

	Lc_str Lc_str::operator-(char ch) const{
		if(leng<=0||find_char(ch)==false)return Lc_str(*this);
		const char* index=re_index_con(ch);
		Lc_str la(begin_con(),index);
		Lc_str lb(index+1,end_con());
		return Lc_str(la+lb);		
	}

	Lc_str Lc_str::operator-(const char* cs) const{
		if(leng==0||find_str(cs)==false)return Lc_str(*this);
		Pack pk=re_find_str(cs);
		Lc_str la(begin_con(),pk.first);		
		Lc_str lb(pk.last,end_con());
		return Lc_str(la+lb);
	}

	Lc_str Lc_str::operator-(const Lc_str& lc) const{
		if(leng==0||lc.leng>leng||find_str(lc)==false)return Lc_str(*this);
		return operator-(lc.strs);
	}

	Lc_str Lc_str::operator*(ulong la) const{
		if(leng==0||la==0)return Lc_str(*this);
		if(la==1)return Lc_str(*this);
		ulong len=leng*la;
		char* csp=nullptr;
		malloc_st(csp,len);
		str_cpy(csp,strs,leng+1);
		for(ulong ua=1; ua<la;++ua){
			str_cat(csp,strs);
			ulong ule=leng*(ua+1);
			set_null(csp,ule);
		}
		Lc_str lcc(csp);
		free_st(csp);
		return lcc;
	}

	Lc_str Lc_str::operator/(char ch) const{
		if(leng==0||ch=='\0'||find_char(ch)==false)return Lc_str(*this);
		char* cms=nullptr;
		malloc_st(cms, leng);
		str_cpy(cms,strs,(leng+1));
		ulong la=0;
		for(ulong ua=0; ua<leng;++ua){
			if(cms[ua]==ch){
				++la;
				for(ulong ue=ua; ue<leng-1;++ue){
					cms[ue]=cms[ue+1];
				}
				--ua;
			}		
		}
		set_null(cms,(leng-la));
		Lc_str lc(cms);
		free_st(cms);
		return lc;
	}

	Lc_str Lc_str::operator/(const char* cs) const{
		if(leng<1||!find_str(cs)||leng<strnlen_s(cs,cs_len))return Lc_str(*this);
		return remove_str(cs);
	}

	Lc_str Lc_str::operator/(const Lc_str& lc) const{
		if(leng<1||!find_str(lc)||leng<lc.leng)return Lc_str(*this);
		return remove_str(lc);
	}

	char* Lc_str::re_index(char ch, ulong le){
		if(leng<1||le>leng)return nullptr;		
		for(ulong ua=le; ua<leng;++ua){
			if(strs[ua]==ch)return strs+ua;
		}
		return nullptr;
	}

	const char* Lc_str::re_index_con(char ch, ulong le) const{
		if(leng<1||le>leng)return nullptr;
		for(ulong ua=le; ua<leng;++ua){
			if(strs[ua]==ch)return strs+ua;
		}
		return nullptr;
	}

	bool Lc_str::find_char(char ch, ulong le) const{
		if(leng<1||le>leng)return false;
		for(ulong ua=le; ua!=leng;++ua){
			if(strs[ua]==ch)return true;
		}
		return false;
	}

	bool Lc_str::find_str(const char* cs, ulong le) const{
		if(!leng!=0||le>leng||strnlen_s(cs, cs_len)>leng)return false;
		ulong lee=strnlen_s(cs, cs_len);
		ulong ue=0;
		for(ulong ua=le; ua<leng; ++ua){
			if(cs[0]==strs[ua]){
				ue=0;
				for(ulong i=0; i<lee; ++i){
					if(cs[i]!=strs[ua+i])goto find_str_rta;
				}
				return true;
			}
			find_str_rta:;
		}
		return false;		
	}

	bool Lc_str::find_str(const Lc_str& lc, ulong le) const{
		if(leng==0||le>leng||lc.leng>leng)return false;
		for(ulong ua=0;ua<leng;++ua){
			if(lc.strs[0]==strs[ua]){
				for(ulong i=0; i<lc.leng;++i){
					if(strs[ua+i]!=lc.strs[i])goto rtb;
				}
				return true;
			}
			rtb:;
		}
		return false;
	}

	Lc_str::Pack Lc_str::re_find_str(const char* cs, ulong le){
		Pack pk{nullptr,nullptr};
		if(!leng!=0||le>leng||strnlen_s(cs,cs_len)>leng||!find_str(cs,le))
			return pk;		

		ulong first=0, last=0;
		ulong lee=strnlen_s(cs, cs_len);
		for(ulong ua=le; ua<leng; ++ua){
			if(cs[0]==strs[ua]){
				ulong i=0;
				for(i=0; i<lee; ++i){
					if(cs[i]!=strs[ua+i])goto rta;
				}
				first=ua;
				last=ua+i;
				break;
			}
			rta:;
		}		
		if(last!=0){
			pk.first=strs+first;
			pk.last=strs+last;
		}
		return pk;
	}

	const Lc_str::Pack Lc_str::re_find_str(const char* cs, ulong le) const{
		Pack pk{nullptr,nullptr};
		if(!leng!=0||strnlen_s(cs, cs_len)>leng||!find_str(cs, le)||le>leng)
			return pk;
		ulong first=0, last=0;
		ulong ue=0;
		for(ulong ua=le; ua!=leng; ++ua){
			if(cs[0]==strs[ua]){
				for(ue=0; ue<strnlen_s(cs, cs_len); ++ue){
					if(cs[ue]!=strs[ua+ue]) goto re_find_str_con;
				}
				first=ua;
				last=ua+ue;
				break;
			}
		re_find_str_con:;
		}
		if(last!=0){
			pk.first=strs+first;
			pk.last=strs+last;
		}
		return pk;
	}

	Lc_str::Pack Lc_str::re_find_str(const Lc_str& lc, ulong le){
		Pack pk{nullptr,nullptr};
		if(!leng!=0||lc.leng>leng||!find_str(lc, le))return pk;
		ulong first=0,last=0;
		ulong ue=0;
		for(ulong ua=le; ua<leng;++ua){
			if(lc.strs[0]==strs[ua]){
				for(ue=0; ue<lc.leng;++ue){
					if(lc.strs[ue]!=strs[ua+ue])goto re_find_str_rta;
				}
				first=ua;
				last=ua+ue;
				break;			
			}
			re_find_str_rta:;		
		}
		if(last!=0){
			pk.first=strs+first;
			pk.last=strs+last;
		}
		return pk;
	}

	const Lc_str::Pack Lc_str::re_find_str(const Lc_str& lc, ulong le) const{
		return re_find_str(lc.strs,le);
	}

	Lc_str Lc_str::remove_char(char ch, ulong le) const{
		if(leng==0||le>leng||ch=='\0'||!find_char(ch,le))return Lc_str(*this);
		char* csm=nullptr;
		malloc_st(csm,leng);
		ulong lee=0;
		str_cpy(csm,strs,(leng+1));
		for(ulong ua=le; ua<leng;++ua){
			if(csm[ua]==ch){ 
				++lee;
				for(ulong ue=ua; ue<leng-1;++ue){
					csm[ue]=csm[ue+1];
				}
				--ua;
			}		
		}
		set_null(csm,(leng-lee));
		Lc_str lc(csm);
		free_st(csm);
		return lc;
	}

	Lc_str Lc_str::remove_str(const char* cs, ulong le) const{
		if(leng==0||!find_str(cs, le)||le>leng||strnlen_s(cs, cs_len)>leng)		
			return Lc_str(*this);		

		Pack pk=re_find_str(cs,le);
	
		if(pk.last==end_con())return Lc_str(begin_con(),pk.first);
		Lc_str head(begin_con(),pk.first);
		Lc_str tail(pk.last,end_con());
		
		while(tail.find_str(cs)){			
			pk=tail.re_find_str(cs);
			head=head+Lc_str(tail.begin_con(),pk.first);
			tail=Lc_str(pk.last,tail.end_con());			

		}		
		head=head+tail;		
		return head;		
	}

	Lc_str Lc_str::remove_str(const Lc_str& lc, ulong le) const{
		if(leng==0||le>leng||!find_str(lc, le))return Lc_str(*this);
		Pack pk=re_find_str(lc, le);		
		if(pk.last==end_con())return Lc_str(begin_con(), pk.first);
		Lc_str head(begin_con(), pk.first);
		Lc_str tail(pk.last, end_con());		
		while(tail.find_str(lc)){
			pk=tail.re_find_str(lc);
			head=head+Lc_str(tail.begin_con(),pk.first);
			tail=Lc_str(pk.last,tail.end_con());
		}
		head=head+tail;
		return head;		
	}

	void Lc_str::show()const{
		cout<<this->strs<<"\n";
	}



}