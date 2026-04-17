extern "C" void ort_init();
extern "C" void ort_done();
extern "C" void ort_preprocess_args(int argc, const char** argv, int* pargc, const char*** pargv);
extern "C" void ort_debug_memory();
extern "C" void ort_print_memory_leaks();
extern "C" int fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3(int argc, const char** argv); 

int main(int argc, const char** argv)
{
    ort_init();
    ort_debug_memory();
    int pargc;
    const char** pargv;
    ort_preprocess_args(argc, argv, &pargc, &pargv);
    int retVal = fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3(pargc, pargv);
    ort_done();
    ort_print_memory_leaks();
    return retVal;
}
