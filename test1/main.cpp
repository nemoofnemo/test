//#include<stdio.h>
//#include <iostream>
//#include<stdlib.h>
//#include <map>
//#include <WinSock2.h>
//#include <string>
//#include <boost\lexical_cast.hpp>
//#include <boost\regex.hpp>
//#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
//
//using namespace std;
//
//class SQLServerADO {
//private:
//	_ConnectionPtr pConnection;
//
//public:
//	SQLServerADO() {
//		HRESULT hr = CoInitialize(NULL);
//		assert(SUCCEEDED(hr));
//	}
//
//	virtual ~SQLServerADO() {
//		if (NULL != pConnection) {
//			pConnection->Close();
//		}
//	}
//
//	//Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=Indexer;Data Source=127.0.0.1
//	bool init(const string & connStr) {
//		try
//		{    //Connecting
//			if (!FAILED(pConnection.CreateInstance(_uuidof(Connection)))) {
//				pConnection->CommandTimeout = 5;// 设置连接超时值，单位为秒
//				if (!FAILED(pConnection->Open((_bstr_t)(connStr.c_str()), "", "", adModeUnknown)))
//					return true;
//			}
//		}
//		catch (_com_error e) {
//			return false;
//		}
//		return false;
//	}
//
//	bool ExecuteSQL(const string & sql, long * nRefreshNum) {
//		bool bResult = false;
//		const char * szSQLStr = sql.c_str();
//
//		if (sql.size() == 0) {
//			return false;
//		}
//
//		try {
//			_variant_t RefreshNum;
//			pConnection->Execute(_bstr_t(szSQLStr), &RefreshNum, adCmdText);
//			bResult = true;
//			*nRefreshNum = RefreshNum.lVal;
//
//		}
//		catch (_com_error e) {
//			puts("fuck");
//		}
//
//		return bResult;
//
//	}
//};
//
//int main(void)
//{
//	SQLServerADO sa;
//	sa.init("Provider=SQLOLEDB.1;Password=123456;Persist Security Info=True;User ID=program;Initial Catalog=Indexer;Data Source=127.0.0.1");
//	long num = 0;
//	sa.ExecuteSQL("insert into bangumi values ('3461','http://i0.hdslb.com/bfs/bangumi/7c1f3ca60da441ffbc2425409ee2a5c379264568.jpg','2732340','2','25','1459699200','3461','2','Re：从零开始的异世界生活','25','1474218310','http://bangumi.bilibili.com/anime/3461','1')", &num);
//	return 0;
//}
//
//
