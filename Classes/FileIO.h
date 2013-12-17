#ifndef Earth_Collapse_Main_1_FileIO_h
#define Earth_Collapse_Main_1_FileIO_h

#include "string"

class FileIO
{
private:
    static FileIO* instance;
    
public:
	void saveFile();
    void readFile();
    std::string getFilePath();
    void variableSetting(std::string temp, int dataNumber);
    
    void removeInstance();
    
    static FileIO* sharedInstance();
};

#endif