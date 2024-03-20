override BIN := bin/cascade
override CFLAGS := -O2 -g -pipe
override CPPFLAGS :=
override LDFLAGS :=
override MKDIR_P := /sbin/mkdir -p
override CC = cc
override LD = cc

# C Compiler flags
override CFLAGS += \
	-Wall \
	-Wextra \
	-Werror \
	-pedantic \
	-std=gnu2x \
	-fsanitize=undefined,address

# C Preprocessor flags
override CPPFLAGS += \
	-Isrc \
	-MMD \
	-D__GNU__ \
	-MP

# Linker flags
override LDFLAGS += \
	-lglfw \
	-lvulkan \
	-fsanitize=undefined,address

# Glob all source files
override CFILES := $(shell cd src && find -L * -type f -name '*.c')
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d))

.PHONY: all
all: $(BIN)

$(BIN): Makefile $(OBJ)
	$(MKDIR_P) "$$(dirname $@)"
	$(LD) $(LDFLAGS) $(OBJ) -o $@

-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj/%.c.o: src/%.c Makefile
	$(MKDIR_P) "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/%.S.o: src/%.S Makefile
	$(MKDIR_P) "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf bin obj
