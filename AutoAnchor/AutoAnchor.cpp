/*
*	author:	daoluan
*	home:	daoluan.net
*	date:	2012-09-17
*/
#include <iostream>
using namespace std;
#include <fstream>

#define TITLE_COUNT		20
#define TITLE_MAXSIZE	50

int main()
{
	fstream in("index.html",ios::in);
	fstream outtmp("tmp.html",ios::out);
	fstream out("ret.html",ios::out);

	char strsrc[2048],*strbrk = "<h3>",*pcurr,tmp,stranchor[1024],strbuff[1024],
		strtitle[TITLE_COUNT][TITLE_MAXSIZE];
	int icnt = 0,ipos;

	//	����
	for(int i=0; i<TITLE_COUNT; i++)
	{
		::memset(strtitle[i],0,TITLE_MAXSIZE);
	}//	for

	//	����html����ÿ��<h3>ǰ��ӣ�<a name="%d"></a>
	while(in.getline(strsrc,2048,'\n'),!in.eof())
	{
		pcurr = strsrc;
		while((ipos = (strstr(pcurr,strbrk)) - pcurr) >= 0)
		{	
			//	���<h3>ǰ���ı�
			tmp = pcurr[ipos];
			pcurr[ipos] = 0;
			outtmp << pcurr << endl;;
			pcurr[ipos] = tmp;

			::memset(stranchor,0,sizeof(stranchor));
			sprintf(stranchor,"<a name=\"%d\"></a>",icnt++);
			outtmp << stranchor << endl;
			
			//	���<h3>
			outtmp << strbrk;

			//	�ƶ�ָ�룬����<h3>
			pcurr = pcurr + ipos + 4;

		}//	while
		//	�ƺ���
		if(ipos < 0)	outtmp << pcurr << endl;
		::memset(strsrc,0,sizeof(strsrc));
	}//	while

	outtmp.flush();
	outtmp.close();

	outtmp.open("tmp.html",ios::in);
	out << "<h3>����Ŀ¼</h3>" << endl;

	out << "<ul>" << endl;
	for(int i=0; i<icnt; i++)
	{
		sprintf(strbuff,"<li><a href=\"#%d\">����%d</a></li>",i,i);
		out << strbuff << endl;
	}//	for
	out << "</ul>" << endl;

	while(outtmp.getline(strsrc,2048,'\n'),!outtmp.eof())
	{
		out << strsrc << endl;
	}//	while

	in.close();
	out.close();
	outtmp.close();
	return 0;
}