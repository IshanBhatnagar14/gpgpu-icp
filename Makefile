MAKEFLAGS += --no-print-directory

.PHONY: all check cpu-all cpu-check

all check:
	$(MAKE) -C gpu_src "$@";

cpu-all cpu-check:
	$(MAKE) -C cpu_src "$@";

clean:
	$(MAKE) -C gpu_src clean;
	$(MAKE) -C cpu_src cpu-clean;


# BENCHMARKS

#cow1: all
#	./$(DIR)/$(EXEC) data/data_students/cow_ref.txt data/data_students/cow_tr1.txt
#
#cow2: all
#	./$(DIR)/$(EXEC) data/data_students/cow_ref.txt data/data_students/cow_tr2.txt
