typedef struct
{
    float a;
    float b;
} Complex;
Complex addCpx(Complex x, Complex y) {
    Complex res;
    res.a = x.a + y.a;
    res.b = x.b + y.b;
    return res;
}

char* fmtCplx(Complex x){
    char* buffer = (char *)malloc(100); // size of char is 1
    snprintf(buffer, 100, "%f + %fi", x.a, x.b);
    return buffer;
}