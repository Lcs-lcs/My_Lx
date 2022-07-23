#pragma once
#include"D:\\Lc\\Lc_str\\Lc_str.h"
#include<cstdio>
#include<cstdlib>
namespace Lc_name{
	using uint=unsigned int;
	class Lc_File{
	public:
		enum class Loc{ beg=SEEK_SET, now=SEEK_CUR, end=SEEK_END };
		enum class Buf_mode{ all=_IOFBF, lin=_IOLBF, nol=_IONBF };
	private:
		FILE* fmp;
		ulong size;
		ulong ilet;
		ulong olet;
		char* buf;
		ulong buf_size;

	public:
		Lc_File();
		Lc_File(FILE* fs);
		Lc_File(const char* fm,const char* mod);
		Lc_File(const Lc_File& lf)=delete;
		Lc_File(Lc_File&& lf);
		~Lc_File();
		Lc_File& operator=(FILE* fs);
		Lc_File& operator=(const Lc_File& lf)=delete;
		Lc_File& operator=(Lc_File&& lf);

		bool open(FILE* fs);
		bool open(const char* fm,const char* mod);
		bool close();
		bool clear();
		bool eof()const{ return feof(fmp)!=0; }
		bool error()const{ return ferror(fmp)!=0; }

		int getc();
		int geti();		
		long getl();
		float getf();
		double getd();
		int check_next();
		Lc_str getLine();
		char* getLine(char* cs,ulong let);
		Lc_str read();
		int read(char* cs,ulong let);
		int read(char* cs,size_t si,uint let);

		bool putc(int ct);
		bool puti(int it);
		bool putl(long lg);
		bool putf(float fa);
		bool putd(double de);
		bool revert(int ct);
		bool puts(const char* cs);
		bool puts(const Lc_str& ls);
		bool puts(const char* cs,ulong let);
		bool write(const Lc_str& ls);
		bool write(const char* cs,ulong let);
		bool write(const char* cs,size_t si,uint let);

		ulong get_ilet()const;
		ulong get_olet()const;
		bool set_ilet(ulong let,Lc_File::Loc lmt=Lc_File::Loc::beg);
		bool set_olet(ulong let,Lc_File::Loc lmt=Lc_File::Loc::beg);

		bool set_buf(ulong let, Lc_File::Buf_mode md);
		bool set_buf(char* cs,ulong lt,Lc_File::Buf_mode md);		
		ulong get_buf_size()const;	
	};




}

