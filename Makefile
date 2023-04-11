CC = em++
CFLAGS = \
	-fsanitize=address \
	-D DEBUG_GL_ERRORS=1
LINKER_FLAGS = \
	-sFETCH \
	-sASYNCIFY \
	-sUSE_WEBGL2=1 \
	-sMIN_WEBGL_VERSION=2 \
	-sALLOW_MEMORY_GROWTH=1 \
	-sENVIRONMENT=web

SRC_DIR = ./src/cpp
FRONTEND_SRC_DIR = ./src/frontend
OUT_DIR = ./build
OBJS_DIR = ./obj
STATIC_DIR = ./static
GLSL_SRC_DIR = $(SRC_DIR)/shaders
GLSL_OUT_DIR = $(STATIC_DIR)/shaders

VPATH := $(shell find $(SRC_DIR) -type d)

INCLUDE_FLAGS = $(addprefix -I, $(VPATH))

ARTIFACT_OUT_DIR = $(OBJS_DIR)
ARTIFACT_JS = wasm.mjs
ARTIFACT_WASM = wasm.wasm
SRCS = $(wildcard *.cpp $(foreach fd, $(VPATH), $(fd)/*.cpp))
HEADERS = $(wildcard *.hpp $(foreach fd, $(VPATH), $(fd)/*.hpp))
SHADERS = $(wildcard $(GLSL_SRC_DIR)/*.vert $(GLSL_SRC_DIR)/*.frag)
OBJS = $(subst $(SRC_DIR)/,, $(addprefix $(OBJS_DIR)/, $(SRCS:cpp=o)))

PHONY := all
all: $(GLSL_OUT_DIR) $(FRONTEND_SRC_DIR)/lib/$(ARTIFACT_JS) $(STATIC_DIR)/$(ARTIFACT_WASM)

PHONY += clean
clean:
	@echo Cleaning $(OBJS_DIR)
	@rm -rf $(OBJS_DIR)/*

$(FRONTEND_SRC_DIR)/lib/$(ARTIFACT_JS): $(ARTIFACT_OUT_DIR)/$(ARTIFACT_JS)
	@echo Moving .mjs to static folder
	@mkdir -p $(@D)
	@cp $< $@

$(STATIC_DIR)/$(ARTIFACT_WASM): $(ARTIFACT_OUT_DIR)/$(ARTIFACT_WASM)
	@echo Moving .wasm to static folder
	@mkdir -p $(@D)
	@cp $< $@

# link .o, generates .mjs and .wasm
$(ARTIFACT_OUT_DIR)/$(ARTIFACT_JS): $(OBJS)
	@echo Building .wasm
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(LINKER_FLAGS) $(OBJS) -o $@ 

# compile .cpp to .o
$(OBJS_DIR)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@ 

# copy shaders to out folder
$(GLSL_OUT_DIR): $(SHADERS)
	@echo Copying shaders to out folder
	@rsync -r --mkpath --delete $(GLSL_SRC_DIR) $(STATIC_DIR)

.PHONY: $(PHONY)