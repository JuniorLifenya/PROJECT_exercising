#Declares the target "all" as phony, meaning its a sort of fake file( not real ) form GNU MAKE
#Everything under are commands that will run when you type make in terminal, preatty cool actually
#Echo prints text, @ prevents Make from printing the actual echo line itself 

.PHONY: all

all:
	@echo "▶️  Regenerating plots & serving your custom index.html" 
	root -q build_site.C

