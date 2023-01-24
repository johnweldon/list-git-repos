
list-git-repos: list-git-repos.o

.PHONY: clean
clean:
	-rm list-git-repos *.o

.PHONY: run
run: list-git-repos
	./$< ..
