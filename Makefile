CC         = clang

# Directories and versions
CAC_DIR    = .cache
OBJ_DIR    = $(CAC_DIR)/obj
LFT_DIR    = libft
MLX_DIR    = $(CAC_DIR)/minilibx
INC_DIR    = include/
SRC_DIR    = src/
BUILD_DIR  = build
VERSION    = 1.0.1
LFT_VER    = ef18a848e7ff89229ed47ebb177cbaee5b91e0be

# ANSI Color Variables
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
MAG    = \033[0;35m
CYAN   = \033[0;36m
RESET  = \033[0m

# Compiler and flags
CCFLAGS  = -Wall -Wextra -Werror -Wpedantic -g -O3 -MMD -MP -I$(INC_DIR) -I$(LFT_DIR) -I$(MLX_DIR) \
		   -Wno-strict-prototypes -fPIC
LDFLAGS  = -L$(LFT_DIR) -L$(MLX_DIR) -lft -lmlx -lXext -lX11 -lm -fPIC \
		   -Wl,-rpath,$(LFT_DIR) -Wl,-rpath,$(MLX_DIR) -Wl,-rpath,$(BUILD_DIR)

LFT      = $(LFT_DIR)/libft.a
MLX      = $(MLX_DIR)/libmlx.a

NAME     = libcrust

# Allow user override for parallelism.
NPROC ?= $(shell nproc)

# Source files
SRC = \
	$(SRC_DIR)imgs/img/crust_img_from_xpm.c \
	$(SRC_DIR)imgs/img/crust_img_put_pixel.c \
	$(SRC_DIR)imgs/img/crust_img_get_pixel.c \
	$(SRC_DIR)imgs/img/crust_img_drop.c \
	$(SRC_DIR)imgs/img/crust_img_crop.c \
	$(SRC_DIR)imgs/img/crust_img_cpy.c \
	$(SRC_DIR)imgs/img/crust_img_new.c \
	$(SRC_DIR)imgs/img/crust_img_draw.c \
	\
	$(SRC_DIR)imgs/scale/crust_img_scale.c \
	$(SRC_DIR)imgs/scale/crust_img_scale_nearest.c \
	$(SRC_DIR)imgs/scale/crust_img_scale_bilinear.c \
	$(SRC_DIR)imgs/scale/crust_img_scale_lanczos.c \
	\
	$(SRC_DIR)imgs/set/crust_set_from_xpm.c \
	$(SRC_DIR)imgs/set/crust_set_drop.c \
	$(SRC_DIR)imgs/set/crust_set_get_img.c \
	$(SRC_DIR)imgs/set/crust_set_get_img_by_pos.c \
	$(SRC_DIR)imgs/set/crust_set_get_imgs.c \
	$(SRC_DIR)imgs/set/crust_set_get_imgs_by_pos.c \
	$(SRC_DIR)imgs/set/crust_set_get_img_offgrid.c \
	\
	$(SRC_DIR)map/camera/camera_free.c \
	$(SRC_DIR)map/camera/camera_init.c \
	$(SRC_DIR)map/camera/camera_move.c \
	$(SRC_DIR)map/camera/camera_render.c \
	$(SRC_DIR)map/camera/camera_resize.c \
	\
	$(SRC_DIR)utils/math/clamp.c \
	$(SRC_DIR)utils/math/lanczos.c \
	$(SRC_DIR)utils/math/sinc.c

OBJ = $(addprefix $(OBJ_DIR)/crust/, $(SRC:.c=.o))

# Default target to build both static and shared libraries.
all: static shared
	@echo -e "$(GREEN)====================================\n        Build complete!\n====================================$(RESET)"

static: $(BUILD_DIR)/$(NAME)-$(VERSION).a incl
	@echo -e "$(CYAN)====================================\n      Static library created.\n====================================$(RESET)"

shared: $(BUILD_DIR)/$(NAME)-$(VERSION).so incl
	@echo -e "$(CYAN)====================================\n      Shared library created.\n====================================$(RESET)"

incl: $(BUILD_DIR)/include

$(BUILD_DIR)/include: $(shell find $(INC_DIR) -type f)
	@mkdir -p $(BUILD_DIR)/include/Crust
	@cp -a $(INC_DIR)/. $(BUILD_DIR)/include/Crust/
	@echo -e "$(BLUE)====================================\n  Include files copied to $(BUILD_DIR)/include\n====================================$(RESET)"

$(BUILD_DIR)/$(NAME)-$(VERSION).a: $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $(OBJ)
	@ln -sf $(NAME)-$(VERSION).a $(BUILD_DIR)/$(NAME).a
	@echo -e "$(BLUE)====================================\n   Static archive built: $@\n====================================$(RESET)"

$(BUILD_DIR)/$(NAME)-$(VERSION).so: $(LFT) $(MLX) $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(LDFLAGS) -shared -o $@ $(OBJ) $(LFT) $(MLX)
	@ln -sf $(NAME)-$(VERSION).so $(BUILD_DIR)/$(NAME).so
	@echo -e "$(BLUE)====================================\n   Shared object built: $@\n====================================$(RESET)"

# Compile source files (dependency files generated alongside)
$(OBJ_DIR)/crust/%.o: %.c $(LFT) $(MLX)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c $< -o $@
	@echo -e "$(MAG)Compiled: $<$(RESET)"

$(LFT):
	@if [ ! -d "$(LFT_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n      Cloning libft...\n====================================$(RESET)"; \
		git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); \
	fi
	@cd $(LFT_DIR) && current_commit=$$(git rev-parse HEAD); \
		if [ "$$current_commit" != "$(LFT_VER)" ]; then \
			git fetch origin; \
		fi
	@cd $(LFT_DIR) && git checkout $(LFT_VER) &>/dev/null
	@$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft CFLAGS+=" -fPIC" -j$(NPROC)
	@echo -e "$(GREEN)====================================\n       libft ready.\n====================================$(RESET)"

$(MLX):
	@mkdir -p $(CAC_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n    Cloning minilibx...\n====================================$(RESET)"; \
		git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR) CFLAGS+=" -fPIC -I$(abspath $(MLX_DIR))" -j$(NPROC)
	@echo -e "$(GREEN)====================================\n    minilibx ready.\n====================================$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(RED)====================================\n   Cleaned object files.\n====================================$(RESET)"

nclean: clean
	@rm -rf $(BUILD_DIR)
	@echo -e "$(RED)====================================\nCleaned objects and build directory.\n====================================$(RESET)"

fclean: nclean
	@rm -rf $(LFT_DIR) $(CAC_DIR)
	@echo -e "$(RED)====================================\n Fully cleaned dependencies and artifacts.\n====================================$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all -j$(NPROC)

qre:
	@$(MAKE) nclean
	@$(MAKE) all -j$(NPROC)

install: all
	@echo -e "$(YELLOW)====================================\n        Installing $(NAME)...\n====================================$(RESET)"
	@sudo cp -r $(BUILD_DIR)/include/* /usr/local/include/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).a /usr/local/lib/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).so /usr/local/lib/
	@sudo ln -sf $(NAME)-$(VERSION).a /usr/local/lib/$(NAME).a
	@sudo ln -sf $(NAME)-$(VERSION).so /usr/local/lib/$(NAME).so
	@echo -e "$(GREEN)====================================\n      Installation complete.\n====================================$(RESET)"

uninstall:
	@echo -e "$(YELLOW)====================================\n      Uninstalling $(NAME)...\n====================================$(RESET)"
	@echo -e "$(BLUE)====================================\n   Deleting include files...\n====================================$(RESET)"
	@for file in $(shell ls $(BUILD_DIR)/include); do \
		sudo rm -rf /usr/local/include/$$file; \
	done
	@sudo rm -f /usr/local/lib/$(NAME).a
	@sudo rm -f /usr/local/lib/$(NAME).so
	@echo -e "$(GREEN)====================================\n    Uninstallation complete.\n====================================$(RESET)"

test: all
	@$(MAKE) -C tests OBJ_DIR=$(abspath $(OBJ_DIR))/tests CAC_DIR=$(abspath $(CAC_DIR)) \
		LFT_DIR=$(abspath $(LFT_DIR)) MLX_DIR=$(abspath $(MLX_DIR)) BUILD_DIR=$(abspath $(BUILD_DIR)) \
		INC_DIR=$(abspath $(INC_DIR)) -j$(NPROC)
	@echo -e "$(CYAN)====================================\n         Tests executed.\n====================================$(RESET)"

help:
	@echo -e "$(BLUE)Usage: make [all|static|shared|clean|nclean|fclean|re|qre|incl|install|uninstall|test|help]$(RESET)"
	@echo -e "$(GREEN)all:$(RESET) Build both static and shared libraries."
	@echo -e "$(GREEN)static:$(RESET) Build the static library."
	@echo -e "$(GREEN)shared:$(RESET) Build the shared library."
	@echo -e "$(YELLOW)clean:$(RESET) Remove object files only."
	@echo -e "$(YELLOW)nclean:$(RESET) Remove object files and the build directory."
	@echo -e "$(RED)fclean:$(RESET) Remove object files, build directory, and dependencies."
	@echo -e "$(MAG)re:$(RESET) Run fclean then build static and shared libraries."
	@echo -e "$(MAG)qre:$(RESET) Remove object files and build directory, then rebuild."

.PHONY: all static shared clean nclean fclean re qre install uninstall test help
