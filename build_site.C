// build_site.C
void build_site()
{
    system("pkill -f \"python3 -m http.server\" || true");           // This line is cool, kills any running http server
    system("cd Root_to_web && nohup python3 -m http.server 8000 &"); // Just like in the root_to_web_OLD.C fine line (97,98,99) to be exact hhaha
    sleep(1);
    system("/mnt/c/Windows/System32/cmd.exe /C start http://127.0.0.1:5501/Root_to_web/super_website_justforfun_.html");
}

// For linux pc, change last line to: system("firefox http://127.0.0.1:5501/Root_to_web/super_website_justforfun_.html ");
// Really cool detail her, when you run make , it will run the build_site() function, so the website just pops up , BUT !
// When you run root -q build_site.C in the terminal it does not work ? hmm
// The reason for this( from internet ) is that the system command runs restricted or in minimal shell
// Lacking acces to cmd.exe, so system() does not get WSL'S properly
// To fix this we include th full cmd.exe path : C:\Windows\System32\cmd.exe
// Now you can do make or root -q build_site.C if you want