#include <io.h>
#include <iostream>
#include <fstream>
#include<Windows.h>
#include<winhttp.h>
#include<vector>
using namespace std;
const char* suffix_list[]  = {"docx","txt"};



void GetDrive(vector<string> &drive_vector)//��ȡϵͳ����Щ�����̷�
{

    DWORD len = GetLogicalDriveStrings(0, NULL);//��ȡϵͳ�̷��ַ�������
    char* drive = new char[len];//�����ַ�����
    GetLogicalDriveStrings(len, drive);//��ȡϵͳ�̷��ַ���
    int type = 0;

    while (*drive != '\0')
   
    {
        type = GetDriveType(drive);
        if (type == DRIVE_FIXED || type == DRIVE_REMOVABLE)//ֻҪ���ƶ����̺�Ӳ��
        {
            drive_vector.push_back(drive);
        }
        drive += strlen(drive) + 1;			//��λ����һ���ַ���.��һ��Ϊ������'\0'�ַ���.
        
    }


}


void GetFilePath(string folder_path, vector<string>& file_path)
{
    //�ļ����
    //ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣
    intptr_t file_handle = 0;
    //�ļ���Ϣ
    struct _finddata_t file_info;
    string p;
    if ((file_handle = _findfirst(p.assign(folder_path).append("\\*").c_str(), &file_info)) != -1)
    {
        do
        {
            //�����Ŀ¼,�ݹ����
            //�������,���ļ�����·������vector��
            if (strcmp(file_info.name, "Windows") == 0 && folder_path.length() <= 4)//�ų�ϵͳ�ļ�
            {
                continue;
            }
            else if ((file_info.attrib & _A_SUBDIR))
            {

                if(strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) 
                {
                    GetFilePath(p.assign(folder_path).append("\\").append(file_info.name), file_path);

                }
            }
            else
            {
                //file_path.push_back(p.assign(folder_path).append("\\").append(file_info.name));

                string tmp = file_info.name;
                string::size_type str_size = tmp.find_last_of('\\') + 1;
                string file_name = tmp.substr(str_size, tmp.length() - str_size);//��ȡ�ļ���


                //��ȡ������׺���ļ���
                //string name = filename.substr(0, filename.rfind("."));

                string suffix_str = file_name.substr(file_name.find_last_of('.') + 1);//��ȡ��׺��
                //cout << folder_path.c_str() << "\\" << file_info.name << endl;
      
                for (int i = 0; i < (sizeof(suffix_list) / sizeof(char*)); i++)
                {
                    if (strcmp(suffix_list[i], suffix_str.c_str()) == 0)
                    {
                        file_path.push_back(folder_path + '\\' + tmp);
                  
                    }

                }

            }
            
        } while (_findnext(file_handle, &file_info) == 0);
        _findclose(file_handle);
    }
}

int main() 
{
    vector<string> drive_vector;
    vector<string>file_path;
    GetDrive(drive_vector);
    for (unsigned int i = 0; i < drive_vector.size(); i++)
    {
        GetFilePath(drive_vector[i].c_str(), file_path);
        //GetFilePath("C:\\v2rayN", file_path);

    }
    for (unsigned int i = 0; i < file_path.size(); i++)
    {
       cout<<file_path[i].c_str()<<endl;

    }
    
    return 0;
}