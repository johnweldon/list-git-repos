.DEFAULT_GOAL := help

TARGET = list-git-repos

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)

.PHONY: all
all: $(TARGET) ## Build target

.PHONY: clean
clean: ## Clean artifacts
	-rm $(TARGET) $(OBJS)

.PHONY: run
run: $(TARGET) ## Run target
	./$<

.PHONY: help
help: ## Display target help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
