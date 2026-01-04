
// Mock test case to verify SVF noalias logic

void* malloc(unsigned long size);
void free(void* ptr);

// Mocking the unsafe attribute for the checker
__attribute__((annotate("unsafe_inst")))
void unsafe_access(int* p) {
    if (p) *p = 42;
}

void safe_access(int* p) { // Arg implicitly noalias in C? No, but we can add restrict manually in IR or mock
    if (p) *p = 100;
}

void test_noalias(int* __restrict__ p1, int* __restrict__ p2) {
    // p1 and p2 should be noalias
    unsafe_access(p1); // Should create points-to to p1's object.
    
    // Check if p1 aliases p2? No.
    // However, our tool checks: "Does this unsafe access touch ANY heap object?"
    // If we pass a heap object to p1.
}

int main() {
    int* h1 = (int*)malloc(sizeof(int));
    int* h2 = (int*)malloc(sizeof(int));
    
    test_noalias(h1, h2);
    
    free(h1);
    free(h2);
    return 0;
}
