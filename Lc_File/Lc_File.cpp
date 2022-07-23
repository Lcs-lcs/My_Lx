#include"Lc_File.h"

namespace Lc_name{
#pragma warning(disable : 4996)

#define F_LEN(sa){fseek(fmp,0,SEEK_END);*sa=ftell(fmp);	}
//ulong le=ftell(fmp);\
//ulong let=fseek(fmp,0,SEEK_END);\
//*sa=ftell(fmp);\
//


	Lc_File::~Lc_File(){
		fclose(fmp);
		if(!buf)free(buf);
		buf=nullptr;	
	}

	Lc_File::Lc_File(){
		fmp=nullptr;
		F_LEN(&size);
		ilet=0;
		olet=0;
		buf=nullptr;
		buf_size=0;
	}

	Lc_File::Lc_File(FILE* fs){
		if(fs==nullptr)Lc_File();
		else{
			fmp=fs;
			F_LEN(&size);
			ilet=0;
			olet=0;
			buf=nullptr;
			buf_size=0;
		}
	}

	Lc_File::Lc_File(const char* fnam, const char* mod){
		Lc_str la("");
		if(la==fnam||la==mod)Lc_File();
		else{
			fmp=fopen(fnam,mod);
			if(fmp==nullptr){
				this->~Lc_File();
				exit(-1);
			}
			F_LEN(&size);
			ilet=0;
			olet=0;
			buf=nullptr;
			buf_size=0;
		}
	}

	Lc_File::Lc_File(Lc_File&& lfs){
		fmp=lfs.fmp;
		size=lfs.size;
		ilet=lfs.ilet;
		olet=lfs.olet;
		buf=lfs.buf;
		buf_size=lfs.buf_size;
		lfs.fmp=nullptr;
		lfs.size=0;
		lfs.ilet=0;
		lfs.olet=0;
		lfs.buf=nullptr;
		lfs.buf_size=0;
	}

	Lc_File& Lc_File::operator=(FILE* fs){
		if(fs==nullptr)return *this;
		if(fs==fmp)return *this;
		fclose(fmp);
		if(!buf)free(buf);
		fmp=fs;
		F_LEN(&size);
		ilet=0;
		olet=0;
		buf=nullptr;
		buf_size=0;
		return *this;
	}

	Lc_File& Lc_File::operator=(Lc_File&& lf){
		if(&lf==this)return *this;
		fclose(fmp);
		if(!buf)free(buf);
		fmp=lf.fmp;
		size=lf.size;
		ilet=lf.ilet;
		olet=lf.olet;
		buf=nullptr;
		buf_size=0;
		return *this;
	}

	bool Lc_File::open(FILE* fs){
		if(fs==nullptr)return false;
		fmp=fs;
		F_LEN(&size);
		ilet=0;
		olet=0;
		buf=nullptr;
		buf_size=0;
		return true;

	}
	bool Lc_File::open(const char* fnam, const char* mod){
		fmp=fopen(fnam, mod);
		if(fmp==nullptr)return false;
		F_LEN(&size);
		ilet=0;
		olet=0;
		buf=nullptr;
		buf_size=0;
		return true;
	}

	bool Lc_File::close(){
		return fclose(fmp)==0;
	}
	bool Lc_File::clear(){
		if(fmp==nullptr)return false;
		ilet=0;
		olet=0;
		fseek(fmp, 0, SEEK_SET);
		for(size_t sa=0; sa<buf_size; ++sa){ buf[sa]=0; }
		clearerr(fmp);
		return true;
	}

	int Lc_File::getc(){
		return fgetc(fmp);
	}
	int Lc_File::geti(){
		int it=0;
		if(fread(&it, sizeof(int), 1, fmp)==1)return it;
		else return 0;
	}

	long Lc_File::getl(){
		long la=0;
		if(fread(&la, sizeof(long), 1, fmp)==1)return la;
		else return 0;
	}

	float Lc_File::getf(){
		float fa=0;
		if(fread(&fa, sizeof(float), 1, fmp)==1)return fa;
		else return 0.0;
	}

	double Lc_File::getd(){
		double fe=0;
		if(fread(&fe, sizeof(double), 1, fmp)==1)return fe;
		else return 0.0;
	}

	int Lc_File::check_next(){
		int it=0;
		it=fgetc(fmp);
		ungetc(it, fmp);
		return it;
	}

	Lc_str Lc_File::getLine(){
#define LE 1024
		char chs[LE];
		fgets(chs,LE, fmp);
		if(ferror(fmp)==0)return Lc_str(chs, LE);
		else return Lc_str();
	}

	char* Lc_File::getLine(char* cs, ulong let){
		fgets(cs, let, fmp);
		if(ferror(fmp)==0)return cs;
		else nullptr;
	}

	Lc_str Lc_File::read(){
		char chs[LE];
		ulong ua=fread(chs, sizeof(char), LE, fmp);
		if(ferror(fmp)!=0)return Lc_str();
		else return Lc_str(chs, ua);
	}

	int Lc_File::read(char* cs, ulong let){
		uint ut=fread(cs, sizeof(char), let, fmp);
		if(ferror(fmp)!=0)return ut;
		else return 0;
	}

	int Lc_File::read(char* cs, size_t si, uint let){
		uint ut=fread(cs, sizeof(char), let, fmp);
		if(ferror(fmp)!=0)return ut;
		else return 0;
	}

	bool Lc_File::putc(int ic){
		return fputc(ic, fmp)==ic;
	}

	bool Lc_File::puti(int it){
		return fwrite(&it, sizeof(int), 1, fmp)==1;
	}

	bool Lc_File::putl(long lg){
		return fwrite(&lg, sizeof(double), 1, fmp)==1;
	}

	bool Lc_File::putf(float ft){
		return fwrite(&ft, sizeof(float), 1, fmp)==1;
	}

	bool Lc_File::putd(double dp){
		return fwrite(&dp, sizeof(double), 1, fmp)==1;

	}

	bool Lc_File::revert(int ct){ return 1; }

	bool Lc_File::puts(const char* cs){
		return fwrite(cs, sizeof(char)*strnlen(cs,LE), 1, fmp)==1;
	}

	bool Lc_File::puts(const Lc_str& ls){
		return fwrite(ls.begin_con(), sizeof(char)*ls.length(), 1, fmp)==1;
	}

	bool Lc_File::puts(const char* cs, ulong let){
		return fwrite(cs, sizeof(char), let, fmp)==let;
	}

	bool Lc_File::write(const Lc_str& ls){
		return fwrite(ls.begin_con(), sizeof(char), ls.length(), fmp)==ls.length();
	}

	bool Lc_File::write(const char* cs, ulong let){
		return fwrite(cs, sizeof(char), let, fmp)==let;
	}

	bool Lc_File::write(const char* cs, size_t si, uint let){
		return fwrite(cs, si, let, fmp)==let;
	}

	ulong Lc_File::get_ilet()const{ return ilet; }

	ulong Lc_File::get_olet()const{ return olet; }

	bool Lc_File::set_ilet(ulong let, Lc_File::Loc lc){
		if(ferror(fmp)!=0)return false;
		return fseek(fmp, let, (int)lc)==0;
	}

	bool Lc_File::set_olet(ulong let, Lc_File::Loc lc){
		if(ferror(fmp)!=0)return false;
		return fseek(fmp, let, (int)lc)==0;
	}

	bool Lc_File::set_buf(char* cs, ulong let, Lc_File::Buf_mode md){
		if(ferror(fmp)!=0)return false;
		buf=cs;
		buf_size=let;
		return setvbuf(fmp, buf, (int)md, buf_size)==0;
	}
	bool Lc_File::set_buf(ulong let, Lc_File::Buf_mode md){
		if(ferror(fmp)!=0)return false;
		buf=(char*)malloc(sizeof(char)*buf_size);
		return setvbuf(fmp, buf, (int)md, buf_size)==0;
	}

	ulong Lc_File::get_buf_size()const{ return buf_size; }

}