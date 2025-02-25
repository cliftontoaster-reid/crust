CCX = clang++
CC  = clang

# Existing directories
CAC_DIR ?= .cache
OBJ_DIR ?= $(CAC_DIR)/obj
LFT_DIR ?= libft
MLX_DIR ?= $(CAC_DIR)/minilibx
INC_DIR ?= include
SRC_DIR ?= src
EXT_INC ?= $(INC_DIR) $(LFT_DIR) $(MLX_DIR)
EXT_OBJ ?= $(LFT) $(MLX)
BUILD_DIR ?= ../build

# Version information
VERSION = 0.1.0

# CUnit configuration
CUNIT_VER     = 2.1-3
CUNIT_TAR     = CUnit-$(CUNIT_VER).tar.bz2
CACHE_DIR     = $(CAC_DIR)/cache
CUNIT_DIR     = $(OBJ_DIR)/CUnit-$(CUNIT_VER)
CUNIT_INSTALL_DIR = $(OBJ_DIR)/cunit
CUNIT_LIB     = $(CUNIT_INSTALL_DIR)/lib/libcunit.a

# Compiler and linker flags
CCFLAGS = -Wall -Wextra -Werror -Wpedantic -g -O3 -MMD -MP $(addprefix -I, $(EXT_INC)) -I$(CUNIT_INSTALL_DIR)/include -Wno-strict-prototypes -fPIC -std=c++17 -I$(BUILD_DIR)/include \
	-flto -march=native -funroll-loops -D_GNU_SOURCE -pthread -ffast-math -fno-finite-math-only -fno-signed-zeros -fno-trapping-math
LDFLAGS = -L$(LFT_DIR) -L$(MLX_DIR) -fPIC -L$(CUNIT_INSTALL_DIR)/lib -Wl,-rpath,$(CUNIT_INSTALL_DIR)/lib 

LFT = $(LFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

NAME = tests

SRC = \
	$(SRC_DIR)/test_main.cpp \
	$(SRC_DIR)/imgs/img.cpp \
	$(SRC_DIR)/imgs/scale.cpp \
	$(SRC_DIR)/imgs/set.cpp \
	$(SRC_DIR)/map/camera.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(CUNIT_LIB) $(CAC_DIR)/$(NAME)
	@echo EEE: $(shell pwd)
	$(abspath $(CAC_DIR)/$(NAME))

$(CAC_DIR)/$(NAME): $(OBJ) $(CUNIT_LIB)
	@mkdir -p $(BUILD_DIR)
	$(CCX) $(CCFLAGS) $(LDFLAGS) -o $@ $^ $(BUILD_DIR)/libcrust.a -lft -lmlx -lXext -lX11 -lm -lcunit 

$(OBJ_DIR)/%.o: %.cpp $(CUNIT_LIB)
	@mkdir -p $(@D)
	$(CCX) $(CCFLAGS) -c -o $@ $<

$(CUNIT_LIB):
	@mkdir -p $(OBJ_DIR) $(CACHE_DIR)
	@echo "Downloading CUnit..."
	@if [ ! -f $(CACHE_DIR)/$(CUNIT_TAR) ]; then \
	wget -q https://downloads.sourceforge.net/project/cunit/CUnit/$(CUNIT_VER)/$(CUNIT_TAR) -O $(CACHE_DIR)/$(CUNIT_TAR); \
	else \
	echo "Using cached CUnit archive"; \
	fi
	@cp $(CACHE_DIR)/$(CUNIT_TAR) $(OBJ_DIR)/
	@echo "Extracting CUnit..."
	@cd $(OBJ_DIR) && tar -xjf $(CUNIT_TAR)
	@echo "Configuring CUnit..."
	@cd $(CUNIT_DIR) && autoreconf -fi > /dev/null && ./configure --prefix=$(abspath $(CUNIT_INSTALL_DIR)) > /dev/null
	@echo "Building CUnit..."
	@$(MAKE) -C $(CUNIT_DIR) > /dev/null
	@echo "Installing CUnit..."
	@$(MAKE) -C $(CUNIT_DIR) install > /dev/null

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(CAC_DIR)/$(NAME)

re: fclean all