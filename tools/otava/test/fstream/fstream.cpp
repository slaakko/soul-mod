import std.core;

struct StreamObjeserver
{
};

struct Stream
{
    virtual ~Stream() {}
    int64_t position;
    std::vector<StreamObjeserver*> observers;
};

struct FileStream : Stream
{
    FileStream(const std::string& filePath_) : filePath(filePath_) {}
    void Print()
    {
        std::cout << filePath << std::endl;
    }
    std::string filePath;
};

int main()
{
    FileStream* fstream = new FileStream("foo");
    fstream->Print();
    return 0;
}
