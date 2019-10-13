#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cassert>

class CleverFile {
private:

    FILE* file_ = nullptr;
    const char* FileName_;
public:


    void FileToRead(const char* FileName) {

        file_ = fopen(FileName, "r");
        if (!file_) {
            fprintf (stderr, "Can not open file %s\n", FileName);
            assert(file_);
        }
        FileName_ = FileName;
    }

    void FileToWrite(const char* FileName) {

        file_ = fopen(FileName, "w");
        if (!file_) {
            fprintf (stderr, "Can not open file %s\n", FileName);
            assert(file_);
        }
        FileName_ = FileName;
    }


    FILE* GetFile() {

        return file_;
    }


    size_t GetFileSize() const {

        struct stat stat_buf;
        int exit = stat(FileName_, &stat_buf);
        if (exit != 0) {
            fprintf (stderr, "Can not open file %s\n", FileName_);
            assert(exit == 0);
        }

        return stat_buf.st_size;
    }

    ~CleverFile() {

        fclose(file_);
        file_ = nullptr;
    }

};
int main(int argc, char* argv[]){
    auto correct_answer = argv[1];
    auto current_answer = argv[2];
    CleverFile correct_file;
    CleverFile checked_file;
    correct_file.FileToRead(correct_answer);
    checked_file.FileToRead(current_answer);
    int correct_size = correct_file.GetFileSize();
    int checked_size = checked_file.GetFileSize();
    if (checked_size != correct_size) {
        std::cout << "error with sizes: " << correct_answer << " " <<checked_size <<"\n";
        return 0;
    }
    char *answer = new char[correct_size + 1];
    fread(answer, sizeof(char), correct_size, correct_file.GetFile());
    char *checked = new char[correct_size + 1];
    fread(checked, sizeof(char), correct_size, checked_file.GetFile());
    if (strcmp(answer, checked) != 0) {
        std::cout << "error with texts: " << correct_answer << " " <<checked_size <<"\n";
        return 0;
    }
    std::cout << "Correct for: "<< correct_answer << " " << current_answer << "\n";
    return 0;
}
