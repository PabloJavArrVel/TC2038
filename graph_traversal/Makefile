TEST_DIR   := test_cases
RESULTS_DIR := results
SRC        := main.cpp          
TARGET     := ./main

CXX        := g++
CXXFLAGS   := -std=c++17 -Wall

IN_FILES   := $(wildcard $(TEST_DIR)/test[0-9][0-9].txt)
TEST_NUMS  := $(patsubst $(TEST_DIR)/test%.txt,%,$(IN_FILES))

.PHONY: all test clean

all: test

$(TARGET): $(wildcard *.cpp *.h)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(wildcard *.cpp)

test: $(TARGET)
	@mkdir -p $(RESULTS_DIR)
	@for num in $(TEST_NUMS); do \
		expected=$(TEST_DIR)/out$$num.txt; \
		actual=$(RESULTS_DIR)/out$$num.txt; \
		$(TARGET) < $(TEST_DIR)/test$$num.txt 2>&1; \
		cp output.txt $$actual; \
		if [ ! -f $$expected ]; then \
			echo "⚠️  Test $$num: MISSING expected file"; \
		elif diff -u $$expected $$actual > $(RESULTS_DIR)/$$num.diff 2>&1; then \
			echo "✅ Test $$num: PASS"; \
		else \
			echo "❌ Test $$num: FAIL (see $(RESULTS_DIR)/$$num.diff)"; \
		fi; \
	done

clean:
	rm -rf $(RESULTS_DIR) $(TARGET)