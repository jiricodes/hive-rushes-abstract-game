.PHONY: all run clean fclean re

all:
	@make -C client

run:
	@make run -C client

test:
	@make test -C client

clean:
	@make clean -C client

fclean:
	@make fclean -C client

re:
	@make re -C client