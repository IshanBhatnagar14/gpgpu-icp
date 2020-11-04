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

.PHONY: cow1 cow2 horse1 horse2 bun45 bun180 bun270 bun315
.SILENT: cow1 cow2

cow1: cpu-all all
	./gpu_src/build/gpu-icp data/data_students/cow_tr1.txt data/data_students/cow_ref.txt
	echo -ne "\n\033[0;33mCPU Implementation: \033[0m"
	bash -c "(time ./cpu_src/build/cpu-icp data/data_students/cow_tr1.txt data/data_students/cow_ref.txt) 1>/dev/null"
	echo -ne "\n\033[0;33mGPU Implementation: \033[0m"
	bash -c "(time ./gpu_src/build/gpu-icp data/data_students/cow_tr1.txt data/data_students/cow_ref.txt) 1>/dev/null"

cow2: cpu-all all
	./gpu_src/build/gpu-icp data/data_students/cow_tr2.txt data/data_students/cow_ref.txt
	echo -ne "\n\033[0;33mCPU Implementation: \033[0m"
	bash -c "(time ./cpu_src/build/cpu-icp data/data_students/cow_tr2.txt data/data_students/cow_ref.txt) 1>/dev/null"
	echo -ne "\n\033[0;33mGPU Implementation: \033[0m"
	bash -c "(time ./gpu_src/build/gpu-icp data/data_students/cow_tr2.txt data/data_students/cow_ref.txt) 1>/dev/null"

horse1: all
	./gpu_src/build/gpu-icp data/data_students/horse_tr1.txt data/data_students/horse_ref.txt

horse2: all
	./gpu_src/build/gpu-icp data/data_students/horse_tr2.txt data/data_students/horse_ref.txt

bun45: all
	./gpu_src/build/gpu-icp data/data_students/bun045.txt data/data_students/bun000.txt

bun180: all
	./gpu_src/build/gpu-icp data/data_students/bun180.txt data/data_students/bun000.txt

bun270: all
	./gpu_src/build/gpu-icp data/data_students/bun270.txt data/data_students/bun000.txt

bun315: all
	./gpu_src/build/gpu-icp data/data_students/bun315.txt data/data_students/bun000.txt
