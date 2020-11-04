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

cow1: all cpu-all
	time ./cpu_src/cpu-icp data/data_students/cow_tr1.txt data/data_students/cow_ref.txt
	time ./gpu_src/gpu-icp data/data_students/cow_tr1.txt data/data_students/cow_ref.txt

cow2: all cpu-all
	time ./cpu_src/cpu-icp data/data_students/cow_tr2.txt data/data_students/cow_ref.txt
	time ./gpu_src/gpu-icp data/data_students/cow_tr2.txt data/data_students/cow_ref.txt

horse1: all
	./gpu_src/gpu-icp data/data_students/horse_tr1.txt data/data_students/horse_ref.txt

horse2: all
	./gpu_src/gpu-icp data/data_students/horse_tr2.txt data/data_students/horse_ref.txt

bun45: all
	./gpu_src/gpu-icp data/data_students/bun045.txt data/data_students/bun000.txt

bun180: all
	./gpu_src/gpu-icp data/data_students/bun180.txt data/data_students/bun000.txt

bun270: all
	./gpu_src/gpu-icp data/data_students/bun270.txt data/data_students/bun000.txt

bun315: all
	./gpu_src/gpu-icp data/data_students/bun315.txt data/data_students/bun000.txt
