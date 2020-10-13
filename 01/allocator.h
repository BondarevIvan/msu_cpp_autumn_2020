namespace NAllocator
{
    using size_t = unsigned long long;
    class Allocator
    {
    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        ~Allocator();
    private:
        size_t offset = 0;
        size_t currentSize = 0;
        char* memory = nullptr;
    };
}