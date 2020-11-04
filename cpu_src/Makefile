MAKEFLAGS += --no-print-directory
EXEC = cpu-icp
DIR = build

.PHONY: cpu-all cpu-clean cpu-check

cpu-all: $(DIR)
	make -C $(DIR);

$(DIR):
	mkdir $(DIR)
	cd $(DIR); cmake ..; cd ..

cpu-check: cpu-all
	./$(DIR)/$(EXEC)

cpu-clean:
	rm -rf $(DIR)
	$(RM) result*.txt
