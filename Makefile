CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -O2
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/Utils.cpp \
       $(SRC_DIR)/Note.cpp \
       $(SRC_DIR)/FileManager.cpp \
       $(SRC_DIR)/InputValidator.cpp \
       $(SRC_DIR)/SearchEngine.cpp \
       $(SRC_DIR)/NoteSorter.cpp \
       $(SRC_DIR)/BackupManager.cpp \
       $(SRC_DIR)/NoteManager.cpp \
       $(SRC_DIR)/UI.cpp \
       $(SRC_DIR)/main.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = notes_saver

TEST_SRCS = $(SRC_DIR)/Utils.cpp \
            $(SRC_DIR)/Note.cpp \
            $(SRC_DIR)/FileManager.cpp \
            $(SRC_DIR)/InputValidator.cpp \
            $(SRC_DIR)/SearchEngine.cpp \
            $(SRC_DIR)/NoteSorter.cpp \
            $(SRC_DIR)/BackupManager.cpp \
            $(SRC_DIR)/NoteManager.cpp \
            tests/test_runner.cpp

TEST_OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
TEST_TARGET = run_tests

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: tests/%.cpp
	@mkdir -p $(OBJ_DIR)/tests
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(OBJ_DIR)/tests/test_runner.o
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TARGET) $(TEST_TARGET) test_notes.txt test_backup.txt
