#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class EBook{
public:
    EBook(std::ostream& out): out_(out){
        out << std::setprecision(6);
    }

    void Read(int reader_id, int page){
        if(page != 0){
            if(readers_.size() < reader_id + 1){
                readers_.resize(reader_id + 1);
            }
            int prev_page = readers_[reader_id];
            readers_[reader_id] = page;
            if(pages_.size() < page + 1){
                pages_.resize(page + 1);
            }
            //we have not page number 0. First page = 1
            for(int i = prev_page + 1; i <= page; ++i){
                ++pages_[i];
            }
        }
    }

    void Cheer(size_t reader_id){
        out_ << CalcCheer(reader_id) << endl;
    }

private:
    std::ostream& out_;
    // unordered_map<size_t,size_t> readers_;
    vector<int> readers_;
    vector<int> pages_;

    double CalcCheer(int reader_id){
        if(readers_.size() < reader_id || readers_[reader_id] == 0){
            return 0.0;
        }
        size_t page = readers_[reader_id];
        if(pages_[page] == 1){
            return 1.0;
        }
        return (double)(pages_[1] - pages_[page]) / (double)(pages_[1] - 1);
    }
};

void GetInput(EBook& ebook, std::istream& in){
    int line_num;
    in >> line_num;
    for(int i = 0; i < line_num; ++i){
        string command;
        in >> command;
        if(command == "READ"s){
            int reader_id, page;
            in >> reader_id >> page;
            ebook.Read((size_t)reader_id, (size_t)page);
        }else if(command == "CHEER"s){
            int reader_id;
            in >> reader_id;
            ebook.Cheer(reader_id);
        } else {
            cout << "Invalid command: "s << command << endl;
        }
    }
}
 
int main(){
    EBook ebook{cout};
    GetInput(ebook, cin);
    return 0;
}