#Declares the target "all" as phony, meaning its a sort of fake file( not real ) form GNU MAKE
#Everything under are commands that will run when you type make in terminal, preatty cool actually
#Echo prints text, @ prevents Make from printing the actual echo line itself 

.PHONY: all

all:
	@echo "▶️  Regenerating plots & serving your custom index.html" 
	root -q build_site.C
# Open the URL in Windows default browser (via WSL)
	cmd.exe /C start http://127.0.0.1:5501/Root_to_web/super_website_justforfun_.html
