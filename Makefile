CC = clang

CAC_DIR = .cache
OBJ_DIR = $(CAC_DIR)/obj
LFT_DIR = libft
MLX_DIR = $(CAC_DIR)/minilibx
INC_DIR = include/
SRC_DIR = src/
BUILD_DIR = build
VERSION = 0.1.0

# Added -MMD -MP to generate dependency files.
CCFLAGS = -Wall -Wextra -Werror -Wpedantic -g -O3 -MMD -MP -I$(INC_DIR) -I$(LFT_DIR) -I$(MLX_DIR) \
  -Wno-strict-prototypes -fPIC
LDFLAGS = -L$(LFT_DIR) -L$(MLX_DIR) -lft -lmlx -lXext -lX11 -lm -fPIC -Wl,-rpath,$(LFT_DIR) -Wl,-rpath,$(MLX_DIR) -Wl,-rpath,$(BUILD_DIR)

LFT = $(LFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

NAME = libcrust

# Allow user to override number of parallel jobs, default to number of cores.
NPROC ?= $(shell nproc)

SRC = \
	$(SRC_DIR)imgs/img/crust_img_from_xpm.c \
	$(SRC_DIR)imgs/img/crust_img_put_pixel.c \
	$(SRC_DIR)imgs/img/crust_img_get_pixel.c \
	$(SRC_DIR)imgs/img/crust_img_drop.c \
	$(SRC_DIR)imgs/img/crust_img_crop.c \
	$(SRC_DIR)imgs/img/crust_img_cpy.c \
	$(SRC_DIR)imgs/img/crust_img_new.c \
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
	\
	$(SRC_DIR)map/camera/camera_free.c \
	$(SRC_DIR)map/camera/camera_init.c \
	$(SRC_DIR)map/camera/camera_move.c \
	$(SRC_DIR)map/camera/camera_render.c \
	$(SRC_DIR)map/camera/camera_resize.c \
	\
	$(SRC_DIR)utils/math/clamp.c \
	$(SRC_DIR)utils/math/lanczos.c \
	$(SRC_DIR)utils/math/sinc.c \


OBJ = $(addprefix $(OBJ_DIR)/crust/, $(SRC:.c=.o))

all: static shared

static: $(BUILD_DIR)/$(NAME)-$(VERSION).a incl
shared: $(BUILD_DIR)/$(NAME)-$(VERSION).so incl
incl: $(BUILD_DIR)/include

$(BUILD_DIR)/include: $(shell find $(INC_DIR) -type f)
	@mkdir -p $(BUILD_DIR)
	cp -r $(INC_DIR) $(BUILD_DIR)/include

$(BUILD_DIR)/$(NAME)-$(VERSION).a: $(OBJ)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $(OBJ)
	ln -sf $(NAME)-$(VERSION).a $(BUILD_DIR)/$(NAME).a

$(BUILD_DIR)/$(NAME)-$(VERSION).so: $(LFT) $(MLX) $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJ) $(LFT) $(MLX)
	ln -sf $(NAME)-$(VERSION).so $(BUILD_DIR)/$(NAME).so

# The $*.d file is automatically generated alongside the object file.
$(OBJ_DIR)/crust/%.o: %.c $(LFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

$(LFT):
	@if [ ! -d "$(LFT_DIR)" ]; then \
		git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); \
	fi
	@cd $(LFT_DIR) && \
		current_commit=$$(git rev-parse HEAD); \
		if [ "$$current_commit" != "$(LFT_VER)" ]; then \
			git fetch origin && git checkout $(LFT_VER); \
		fi
	$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft CFLAGS+=" -fPIC" -j$(NPROC)

$(MLX):
	@mkdir -p $(CAC_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR) CFLAGS+=" -fPIC -I$(abspath $(MLX_DIR))" -j$(NPROC)

clean:
	rm -rf $(OBJ_DIR)

nclean: clean
	rm -rf $(BUILD_DIR)

fclean: nclean
	rm -rf $(LFT_DIR) $(CAC_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all -j$(NPROC)

qre:
	$(MAKE) nclean
	$(MAKE) all -j$(NPROC)

install: all
	@echo "Installing $(NAME)..."
	@sudo cp -r $(BUILD_DIR)/include/* /usr/local/include/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).a /usr/local/lib/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).so /usr/local/lib/
	@sudo ln -sf $(NAME)-$(VERSION).a /usr/local/lib/$(NAME).a
	@sudo ln -sf $(NAME)-$(VERSION).so /usr/local/lib/$(NAME).so
	@echo "Installation complete."

uninstall:
	@echo "Uninstalling $(NAME)..."
	@echo "Deleting include files..."
	@for file in $(shell ls $(BUILD_DIR)/include); do \
		sudo rm -rf /usr/local/include/$$file; \
	done
	@sudo rm -f /usr/local/lib/$(NAME).a
	@sudo rm -f /usr/local/lib/$(NAME).so
	@echo "Uninstallation complete."


test: all
	$(MAKE) -C tests OBJ_DIR=$(abspath $(OBJ_DIR))/tests CAC_DIR=$(abspath $(CAC_DIR)) \
		LFT_DIR=$(abspath $(LFT_DIR)) MLX_DIR=$(abspath $(MLX_DIR)) BUILD_DIR=$(abspath $(BUILD_DIR)) \
		INC_DIR=$(abspath $(INC_DIR)) -j$(NPROC)

help:
	@echo "Usage: make [all|static|shared|clean|nclean|fclean|re|qre|tools|incl]"
	@echo "all: Build static and shared libraries."
	@echo "static: Build static library."
	@echo "shared: Build shared library."
	@echo "clean: Remove object files."
	@echo "nclean: Remove object files and build directory."
	@echo "fclean: Remove object files, build directory, and dependencies."
	@echo "re: Remove object files, build directory, and dependencies, then build static and shared libraries."
	@echo "qre: Remove object files and build directory, then build static and shared libraries."

.PHONY: all static shared clean nclean fclean re qre
