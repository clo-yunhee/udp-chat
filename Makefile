### Directory

COMMON_SRC_DIR = src/common
CLIENT_SRC_DIR = src/client
SERVER_SRC_DIR = src/server

CLIENT_OBJ_DIR = obj/client
SERVER_OBJ_DIR = obj/server

BIN_DIR = bin

### Source files

CLIENT_C := $(wildcard $(CLIENT_SRC_DIR)/*.c)
SERVER_C := $(wildcard $(SERVER_SRC_DIR)/*.c)

CLIENT_OBJ := $(CLIENT_C:$(CLIENT_SRC_DIR)/%.c=$(CLIENT_OBJ_DIR)/%.o)
SERVER_OBJ := $(SERVER_C:$(SERVER_SRC_DIR)/%.c=$(SERVER_OBJ_DIR)/%.o)

CLIENT_DEP := $(CLIENT_OBJ:%.o=%.d)
SERVER_DEP := $(SERVER_OBJ:%.o=%.d)

### Flag strings

C_FLAGS  += -std=c11 -D_XOPEN_SOURCE=700 -g -Wall -Wextra -Werror -I$(COMMON_SRC_DIR) -pthread
LD_FLAGS += -pthread

CLIENT_FLAGS := 
SERVER_FLAGS :=

### Targets

.PHONY: all
all: client server

# Client

client: $(CLIENT_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(LD_FLAGS) $(CLIENT_FLAGS) $^ -o $(BIN_DIR)/client

-include $(CLIENT_DEP)

$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(CLIENT_FLAGS) -MMD -c $< -o $@

.PHONY: clean-client
clean-client:
	-rm $(BIN_DIR)/client $(CLIENT_OBJ) $(CLIENT_DEP)

# Server

server: $(SERVER_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(LD_FLAGS) $(SERVER_FLAGS) $^ -o $(BIN_DIR)/server

-include $(SERVER_DEP)

$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(SERVER_FLAGS) -MMD -c $< -o $@

.PHONY: clean-server
clean-server:
	-rm $(BIN_DIR)/server $(SERVER_OBJ) $(SERVER_DEP)

# Common

.PHONY: clean
clean: clean-client clean-server

.PHONY: re
re: clean all
