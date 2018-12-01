CC = g++-mp-8 -fopenmp

BIN = Ex1_1_threads Ex2_1_pi Ex3_1_pi_parallel Ex3_2_pi_parallel-for Ex4_1_pi_parallel-for-reduction Ex4_2_barrier_wait-nowait Ex4_3_master Ex4_4_single Ex4_5_ordered Ex4_6_simple-lock Ex4_7_dynamic
OBJ = $(BIN:%=%.o)

all: $(BIN)

%: %.cpp 
	$(CC) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)
