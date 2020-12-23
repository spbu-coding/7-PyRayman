.PHONY: all clean check
include CONFIG.cfg
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/tools.o
CC = gcc
LD = gcc

TARGET = $(BUILD_DIR)/$(NAME)
TESTS_IN = $(wildcard $(TEST_DIR)/*.in)
TESTS_NAMES = $(TESTS_IN:$(TEST_DIR)/%.in=%)
TESTS_OUT = $(wildcard $(TEST_DIR)/*.out)
TESTS_RESULT = $(TESTS_OUT:$(TEST_DIR)/%=$(BUILD_DIR)/%)
LOG = $(TESTS_INPUT:$(TEST_DIR)/%.in=$(BUILD_TEST)/%.log)




all: $(TARGET)

$(OBJ): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
    $(CC) -c $< -o $@
$(TARGET): $(OBJ) | $(BUILD_DIR)
    $(LD) $^ -o $@
$(BUILD_DIR):
    @mkdir -p $@

clean: 
    $(RM) $(BUILD_DIR)/$(NAME) $(OBJ) $(LOG)

check: $(LOG) 
    @temp = 0 ; \
    for test in $(TESTS_NAMES) ; do \
        if [ "$$(cat $(BUILD_DIR)/$$test.log)" = "1" ]; then \
            echo test $$test failed; \
            temp = 1; \
        else \
            echo test $$test passed ; \
            
        fi \
    done; \ 
    exit $$temp

@(LOG): $(BUILD_DIR)/%.log : $(BUILD_DIR)/%.out $(TEST_DIR)/%.out
    @cmp -s $^ ; echo $$? > $@

$(TESTS_RESULT): $(BUILD_DIR)/%.out : $(TEST_DIR)/%.in $(BULD_DIR)/$(NAME)
    @./$(TARGET) $< > $@


