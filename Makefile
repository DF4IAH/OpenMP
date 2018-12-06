CC = g++-mp-8 -fopenmp
#CC = g++ -fopenmp

BIN  = Ex1_1_threads 
BIN += Ex2_1_pi 
BIN += Ex3_1_pi_parallel Ex3_2_pi_parallel-for 
BIN += Ex4_1_pi_parallel-for-reduction Ex4_1B_pi_parallel-for-reduction__GPU Ex4_2_barrier_wait-nowait Ex4_3_master Ex4_4_single Ex4_5_ordered Ex4_6_simple-lock Ex4_7_dynamic 
BIN += Ex5_1_pi-by-dartboard 
BIN += Ex6_1_hard_Fibonacci Ex6_2_easy_MatMul
BIN += Ex7_1_prod_cons
BIN += Test1_FIR64 Test2A_Mandelbrot Test2B_Mandelbrot_GPU

OBJ  = $(BIN:%=%.o)

all: $(BIN)

%: %.cpp 
	$(CC) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)
