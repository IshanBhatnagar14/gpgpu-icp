MAKEFLAGS += --no-print-directory
EXEC = gpu-icp
DIR = build

.PHONY: all clean check

all: $(DIR)
	make -C $(DIR);

$(DIR):
	mkdir $(DIR)
	cd $(DIR); cmake ..; cd ..

check: all
	./$(DIR)/$(EXEC)

clean:
	rm -rf $(DIR)
	$(RM) result*.txt
