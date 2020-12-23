
include CONFIG.cfg

CC = gcc
LD = gcc

TARGET = $(BUILD_DIR)/$(NAME)
OBJ = $(TARGET).o
TESTS_IN = $(wildcard $(TEST_DIR)/*.in)
TESTS_NAMES = $(TESTS_IN:$(TEST_DIR)/%.in=%)
TESTS_OUT = $(wildcard $(TEST_DIR)/*.out)
TESTS_RESULT = $(TESTS_OUT:$(TEST_DIR)/%=$(BUILD_DIR)/%)
LOG = $(TESTS_INPUT:$(TEST_DIR)/%.in=$(BUILD_TEST)/%.log)


.PHONY: all clean check
.INTERMEDIATE: $(OBJ) $(TESTS_RESULT)
.SECONDARY: $(TARGET) $(LOG)


all: $(TARGET)

$(OBJ): $(SOURCE_DIR)/$(NAME).c | $(BUILD_DIR)
	$(CC) -c -o $@ $<

$(TARGET): $(OBJ)
	$(LD) -o $@ $<

$(BUILD_DIR): $(SOURCE_DIR)/$(NAME).c
	@mkdir -p $@

clean:
	$(RM) -r $(BUILD_DIR)/

check: $(LOG)
	@temp=0 ; \
	for test in $(TESTS_NAMES) ; do \
		if [ "$$(cat $(BUILD_DIR)/$$test.log)" = "1" ] ; then \
			echo test $$test failed ; \
			temp=1 ; \
		else \
			echo test $$test passed ; \
		fi \
	done ; \
    exit $$temp

@(LOG): $(BUILD_DIR)/%.log : $(BUILD_DIR)/%.out $(TEST_DIR)/%.out
    @cmp -s $^ ; echo $$? > $@

$(TESTS_RESULT): $(BUILD_DIR)/%.out : $(TEST_DIR)/%.in $(BULD_DIR)/$(NAME)
    @./$(TARGET) $< > $@



