class Box {
public:
    int w;
    Box(int width) { w = width; }  // the only constructor takes an argument
};

int main() {
    Box b;                         // needs Box(), which no longer exists
    return 0;
}
