MAKEFLAGS += --no-print-directory
EXEC = gpgpu-icp
DIR = build

.PHONY: all, check, clean, run

all: build
	make -C $(DIR);

$(DIR):
	mkdir $(DIR)
	cd $(DIR); cmake ..; cd ..

run: all
	./$(DIR)/$(EXEC)

check: clean all
	./$(DIR)/$(EXEC)

clean:
	rm -rf $(DIR)
	$(RM) result*.txt
